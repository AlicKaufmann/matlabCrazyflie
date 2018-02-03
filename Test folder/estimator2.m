%function [xNext, JxNext] = stateTransition(xNow)
import casadi.*

N = 100;
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

x_post = [0;0;0;0;0;0];

transMap = casadi.interpolant('LUT','bspline',{[0,2,3,5,6,7,8,9,10]}, [0,0.2244,0.3850,0.6309,0.7839,1.022,1.1630,1.3959,1.5340]);
rotMap = casadi.interpolant('LUT','bspline',{0:10:100}, [0, 6.3632, 16.8374, 25.6822, 35.5810, 45.7588, 53.0103, 60.5996, 83.5957, 89.0708, 96.1055]);

states = [px;py;theta;vx;vy;omega];
rhs = [vx;...
    vy;...
    omega;...
    transMap(u(1))*cos(omega);...
    transMap(u(1))*sin(omega);...
    rotMap(u(2))];

f = Function('f',{states,u},{rhs},{'x','u'},{'y'}); % fonction of the dynamics
h = Function('h',{states},{states([1,2,6])}); % measurment function

% Fixed step Runge-Kutta 4 integrator
Ts = MX.sym('Ts',1); % time step --> we do M integration for each time step
M = 4; % RK4 steps per interval
DT = Ts/M;
x0 = MX.sym('x0', 6);
x = x0;
for j=1:M
    k1 = f(x, u);
    k2 = f(x + DT/2 * k1, u);
    k3 = f(x + DT/2 * k2, u);
    k4 = f(x + DT * k3, u);
    x=x+DT/6*(k1 +2*k2 +2*k3 +k4);
end
fd = Function('fd', {x0, Ts, u}, {x}, {'x0','Ts','p'}, {'xf'});

% predict function
% Q = 0.1 * MX.eye(6); --> defined in the top
% Q = MX.sym('Q',6,6); % process noise covariance
x_post = MX.sym('x0',6);
P_post = MX.sym('P_post',6,6);
Ts = MX.sym('Ts',1);
u = MX.sym('u',2);
x1 = fd('x0',[0;0;0;0;0;0],'Ts',0.1,'p',[1;1]);

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
dt = 0.1;
P_post = eye(6);
x_post = [0;0;0;1;1;1];

yVec=[dt:dt:10;
      dt:dt:10;
      ones(1,N)];
% uVec = linspace(0,1,N);
uVec = zeros(2,N);

for k = 1:N % eventually replace this loop by a map
    t = k * dt; % current time
    
    u = uVec(:,k);
    y = yVec(:,k);
    
    % prediction step
    [x_prior, P_prior] = predict(x_post, P_post, dt, u);
    
    % correction step
    [x_post, P_post] = update(x_prior, P_prior, y);
end
%end

%------------QUESTIONS------------------
% 1) How to know how f() and h() depend on w and v respectively?
% 2) How to incorporate the noise w in the f function ? I think it can't be
% as a parameter since we have to find the jacobian of it. Also, it seems
% weird to stack [x;w] as the variable. What should I do?
% 2) How to evaluate the enormous expression we get for example for P_post at the end ?