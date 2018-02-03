%function [xNext, JxNext] = stateTransition(xNow)
import casadi.*

N = 100;
% control input
uT = casadi.interpolant('LUT','bspline',{[1,2,3,4,5]}, [1,2,3,4,5]);
uR = casadi.interpolant('LUT', 'bspline', {[1,2,3,4,5]}, [1,2,3,4,5]);

controls = MX.sym('u',2); % we have u = [uT;uR]
w = MX.sym('w',6); % process noise
v = MX.sym('v',3); % measurment noise

t = MX.sym('t', 1);
x = MX.sym('x',1);
y = MX.sym('y',1);
theta = MX.sym('theta',1);
vx = MX.sym('vx', 1);
vy = MX.sym('vy', 1);
omega = MX.sym('omega',1);

Q = 0.1 * MX.eye(6); % process noise covariance
R = 0.1 * MX.eye(6); % measurment noise covariance

opts.t0 = 0;
opts.tf = 0;
dt = 0.1;

x_post = [0;0;0;0;0;0];

transMap = casadi.interpolant('LUT','bspline',{[0,2,3,5,6,7,8,9,10]}, [0,0.2244,0.3850,0.6309,0.7839,1.022,1.1630,1.3959,1.5340]);
rotMap = casadi.interpolant('LUT','bspline',{0:10:100}, [0, 6.3632, 16.8374, 25.6822, 35.5810, 45.7588, 53.0103, 60.5996, 83.5957, 89.0708, 96.1055]);

states = [x;y;theta;vx;vy;omega];
rhs = [vx;...
    vy;...
    omega;...
    transMap(uT(t))*cos(omega);...
    transMap(uT(t))*sin(omega);...
    rotMap(uR(t))];

f = Function('f',{states},{rhs}); % fonction of the dynamics
h = Function('h',{states},{states([1,2,6])}); % measurment function

dae = struct('x', states, 't', t, 'ode', rhs);

P_post = MX.eye(6);

% The jacobian of the measurment fonction is constant
JH = MX([1,0,0,0,0,0;
        0,1,0,0,0,0;
        0,0,0,0,0,1]);

yVec=linspace(1,10,N);
% Kalman filter
for k = 1:N % eventually replace this loop by a map
    opts.t0 = opts.tf;
    opts.tf = opts.tf + dt;
    y = yVec(k);
    
    F = integrator('F', 'cvodes', dae,opts); % state transition function
    r = F('x0', x_post);
    JF = F.jacobian;

    Jx_post = JF('x0',x_post);
    Jx_post = Jx_post.jac;
    
    % prediction step
    P_prior = Jx_post * P_post * Jx_post';
    x_prior = r.xf;
    
    % correction step
    K = P_prior * JH' / (JH * P_prior * JH');
    x_post = x_prior + K * (y - x_prior([1,2,6]));
    P_post = (MX.eye(6) - K * JH) * P_prior;
end
%end

%------------QUESTIONS------------------
% 1) How to know how f() and h() depend on w and v respectively?
% 2) How to incorporate the noise w in the f function ? I think it can't be
% as a parameter since we have to find the jacobian of it. Also, it seems
% weird to stack [x;w] as the variable. What should I do?
% 2) How to evaluate the enormous expression we get for example for P_post at the end ?