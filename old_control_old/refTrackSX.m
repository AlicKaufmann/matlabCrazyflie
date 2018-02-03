%function [cell_x_post, cell_P_post] = estimator2(yVec)
import casadi.*

Ns = 100;
N = 3; % horizon
T = 10; % final time
dt = T/Ns; % time step

u = SX.sym('u',2); % ontrol input, u = [uT, UR],parameter for the integration
w = SX.sym('w',6); % process noise
v = SX.sym('v',3); % measurment noise

t = SX.sym('t', 1); % time
px = SX.sym('px',1);
py = SX.sym('py',1);
theta = SX.sym('theta',1);
vx = SX.sym('vx', 1);
vy = SX.sym('vy', 1);
omega = SX.sym('omega',1);

Q = 0.1 * SX.eye(6); % process noise covariance
R = 0.1 * SX.eye(3); % measurment noise covariance

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

% plot transMap and rotMap if you want to see what they look like
% figure(3)
% plot(linspace(-100,100,100),full(transMap(linspace(-100,100,100))))
% title('transMap fT')
% xlabel('control input uT (in %)')
% ylabel('linear acceleration aT in m/s-2')
% figure(4)
% plot(linspace(-100,100,100),full(rotMap(linspace(-100,100,100))))
% title('rotMap fR')
% xlabel('control input uR (in %)')
% ylabel('angular acceleration aR rad/s-2')

states = [px;py;theta;vx;vy;omega];
rhs = [vx;...
    vy;...
    omega;...
    transMap(u(1))*cos(theta + pi/2);... % +pi/2 because acceleration orthog. to HC angle 
    transMap(u(1))*sin(theta + pi/2);...
    rotMap(u(2))];
