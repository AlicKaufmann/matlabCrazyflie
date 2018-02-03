import casadi.*

uT = 1; % translation command
uR = 1; % rotation command

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
    transMap(uT)*cos(omega);...
    transMap(uT)*sin(omega);...
    rotMap(uR)];

f=Function('f',{states},{rhs});

dae = struct('x', states, 'ode', rhs);

opts.t0 = 0;
opts.tf = 3;

F = integrator('F', 'cvodes', dae,opts);

r = F('x0', [0;0;1;1;1;1]);

JF = F.jacobian;

A = JF('x0',[0;0;0;0;0;0]);
A = A.jac
