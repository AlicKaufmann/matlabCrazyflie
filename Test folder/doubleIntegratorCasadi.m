function [xNext, JxNext] = stateTransition(xNow)

% control input
uT = casadi.interpolant('LUT','bspline',{[1,2,3,4,5]}, [1,2,3,4,5]);
uR = casadi.interpolant('LUT', 'bspline', {[1,2,3,4,5]}, [1,2,3,4,5]);

controls = MX.sym('u',2); % we have u = [uT;uR]
disturbances = MX.sym('w');

t = MX.sym('t', 1);
x = MX.sym('x',1);
y = MX.sym('y',1);
theta = MX.sym('theta',1);
vx = MX.sym('vx', 1);
vy = MX.sym('vy', 1);
omega = MX.sym('omega',1);

transMap = casadi.interpolant('LUT','bspline',{[0,2,3,5,6,7,8,9,10]}, [0,0.2244,0.3850,0.6309,0.7839,1.022,1.1630,1.3959,1.5340]);
rotMap = casadi.interpolant('LUT','bspline',{0:10:100}, [0, 6.3632, 16.8374, 25.6822, 35.5810, 45.7588, 53.0103, 60.5996, 83.5957, 89.0708, 96.1055]);

states = [x;y;theta;vx;vy;omega];
rhs = [vx;...
    vy;...
    omega;...
    transMap(uT(t))*cos(omega);...
    transMap(uT(t))*sin(omega);...
    rotMap(uR(t))];

f = Function('f',{states},{rhs});

% defining my own integrator


dae = struct('x', states, 't', t, 'ode', rhs);

opts.t0 = 0;
opts.tf = 3;

F = integrator('F', 'cvodes', dae,opts);

r = F('x0', xNow);

JF = F.jacobian;

JxNext = JF('x0',xNow);
JxNext = JxNext.jac
end