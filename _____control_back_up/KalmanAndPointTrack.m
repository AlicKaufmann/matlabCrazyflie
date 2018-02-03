%function [cell_x_post, cell_P_post] = estimator2(yVec)
import casadi.*

Ns = 100;
N = 10; % horizon

u = MX.sym('u',2); % ontrol input, u = [uT, UR],parameter for the integration
w = MX.sym('w',6); % process noise
v = MX.sym('v',3); % measurment noise

t = MX.sym('t', 1);
px = MX.sym('px',1);
py = MX.sym('py',1);
theta = MX.sym('theta',1);
vx = MX.sym('vx', 1);
vy = MX.sym('vy', 1);
omega = MX.sym('omega',1);

Q = 0.1 * MX.eye(6); % process noise covariance
R = 0.1 * MX.eye(3); % measurment noise covariance

uTp = [0,20,30,50,60,70,80,90,100];
uT = [0,0.2244,0.3850,0.6309,0.7839,1.022,1.1630,1.3959,1.5340];
uTp_ = -uTp; % eventually identify the right values 
uT_ = -uT; % eventually identify the right values
uRp = 0:10:100;
uR = [0, 6.3632, 16.8374, 25.6822, 35.5810, 45.7588, 53.0103, 60.5996, 83.5957, 89.0708, 96.1055];
uRp_ = -uRp; % eventually identify the right values
uR_ = -uR; % eventually identify the right values

transMap = casadi.interpolant('LUT','bspline',{union(uTp_, uTp)}, union(uT,uT_));
rotMap = casadi.interpolant('LUT','bspline',{union(uRp_, uRp)}, union(uR_,uR));

states = [px;py;theta;vx;vy;omega];
rhs = [vx;...
    vy;...
    omega;...
    transMap(u(1))*cos(theta + pi/2);... % +pi/2 because acceleration orthog. to HC angle 
    transMap(u(1))*sin(theta + pi/2);...
    rotMap(u(2))];

% cost function
cost = (px + 2)^2 + ...
        (py + 2)^2 + ...
        theta^2; % + ...
        % vx^2 + ...
        % vy^2  + ...
        % u(1)^2 + ...
        % u(2)^2
        
        

f = Function('f',{states,u},{rhs, cost},{'x','u'},{'y','cost'}); % fonction of the dynamics
h = Function('h',{states},{states([1,2,6])}); % measurment function

% Fixed step Runge-Kutta 4 integrator
Ts = MX.sym('Ts',1); % time step --> we do M integration for each time step
M = 4; % RK4 steps per interval
DT = Ts/M;
x0 = MX.sym('x0', 6);
x = x0;
q = 0;
for j=1:M
    [k1, k1_q] = f(x, u);
    [k2, k2_q] = f(x + DT/2 * k1, u);
    [k3, k3_q] = f(x + DT/2 * k2, u);
    [k4, k4_q] = f(x + DT * k3, u);
    x = x + DT/6 * (k1 + 2 * k2 +2 * k3 + k4);
    q = q + DT/6 * (k1_q + 2 * k2_q + 2 * k3_q + k4_q);
end
fd = Function('fd', {x0, Ts, u}, {x,q}, {'x0','Ts','p'}, {'xf','qf'});

% predict function
x_post = MX.sym('x0',6);
P_post = MX.sym('P_post',6,6);
Ts = MX.sym('Ts',1);
u = MX.sym('u',2);

Jfd = fd.jacobian_old(0,0); % jacobian of 0-th output wrt 0-th input
Jfd_x = Jfd('x0', x_post, 'Ts', Ts, 'p', u);
F = Jfd_x.jac_xf_x0;
L = MX.eye(6);
P_prior = F * P_post * F' + L * Q * L';
x_prior = fd(x_post, Ts, u);

predict = Function('predict', {x_post, P_post, Ts, u}, {x_prior, P_prior});

% update function
M = MX.eye(3); % jacobian wrt v of measMap-->identity for additive noise
H = MX([1,0,0,0,0,0 % jacobian wrt x of measMap
        0,1,0,0,0,0;
        0,0,0,0,0,1]);
y = MX.sym('y',3);
P_prior = MX.sym('P_prior',6,6);
x_prior = MX.sym('x_prior',6,1);

K = P_prior * H' / (H * P_prior * H' + M * R * M');
x_post = x_prior + K * (y - h(x_prior));
P_post = (MX.eye(6) - K * H) * P_prior;

update = Function('update', {x_prior, P_prior, y}, {x_post, P_post});

% Kalman filter
%initialisations
dt = 20/Ns;
P_post = eye(6);
x_post = [3;3;0.8;0;0;0];

noise = 0.1 * rand(3,1);
% noise = 0.1 * rand(3,Ns);
% 
% yVec=[dt:dt:dt + (Ns - 1) * dt;
%       dt:dt:dt + (Ns - 1) * dt;
%       ones(1,Ns)] + noise;
% uVec = linspace(0,1,N);
uVec = zeros(2,Ns);
u_opt = [];

cell_x_post = {};
cell_P_post = {};

for i = 1:Ns
    
    % collect the states
    cell_x_post = {cell_x_post{:}, x_post};
    cell_P_post = {cell_P_post{:}, P_post};
    
    t = i * dt; % current time
    
    w = {};
    w0 = [];
    lbw = [];
    ubw = [];
    J = 0;
    g = {};
    lbg = [];
    ubg = [];
    
    xk = x_post;
    for k = 1:N-1
        uk = MX.sym(['u',num2str(k)],2);
        w = {w{:}, uk};
        lbw = [lbw; [-100; -100]]; % input should be constrained to [0%, 100%]
        ubw = [ubw; [100; 100]];
        w0 = [w0; [0; 0]];
        
        % integration on one timestep
        fdk = fd('x0', xk, 'Ts', dt, 'p', uk);
        xk = fdk.xf;
        J = J + fdk.qf;
        
        % Add inequality constraints
        g = {g{:}, xk([1,2])}; % we constraint px and py, constraint theta in [-pi,pi]?
        lbg = [lbg; [-4; -6]]; % x and y constrained wrt size of airhockey table
        ubg = [ubg; [4; 6]];
    end
    
    nlp = struct('x',vertcat(w{:}),'f', J, 'g', vertcat(g{:}));
    solver = nlpsol('solver', 'ipopt', nlp);
    sol = solver('x0', w0, 'lbg', lbg, 'ubg', ubg, 'lbx', lbw, 'ubx', ubw);
    w_opt = full(sol.x);
    
    % MPC-->take only first input of horizon
    u = w_opt([1;2]);
    u_opt = [u_opt, u]; % collect the MPC entries
    
    % prediction step --> no correction step, x_post as "measured" value.
    [x_prior, P_prior] = predict(x_post, P_post, dt, u);
    
    % correction step
    y_ideal = x_prior([1,2,6]); % simulate the noise
    y_sim = y_ideal + 0.1 * rand(size(y_ideal));
    
    [x_post, P_post] = update(x_prior, P_prior, y_sim);

end
% end

% process the state for simulation
x = cellfun(@full,cell_x_post,'uniformOutput', false);
x = cell2mat(x);
x = x';
t = linspace(0,10,Ns);
