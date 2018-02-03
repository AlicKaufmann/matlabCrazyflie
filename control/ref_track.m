import casadi.*

% add the fake noise


T = 5; % time
Ns = 50; % number of steps
N = 3; % horizon of the MPC controller
dt = T/Ns; 
t_span = 0:dt:T;
noise_prefac = 0.1;

Q = 0.1 * MX.eye(6); % process noise covariance
R = 0.1 * MX.eye(4); % measurment noise covariance

% object with transition and measurement map
dynamics = hovercraft_model();

% create a rk integrator with M steps
M = 4;
fd = create_integrator.create_integrator_rk4(dynamics.f, M);

% create kalman-filter object for our model with pred. and upd. function
ext_kal_filt = kalman_filter.kalman_filter(fd, dynamics.h, Q, R);

% create reference we want to track
ref = reference();

% create cost in function of reference to track
tracking_cost = cost(ref);

% create MPC controller
MPC_controller = MPC(dynamics, tracking_cost, N, dt);

% MPC control
t = 0;
P_post = eye(6);
x_post = [2; 0; 0; 0; 0; 0]; % we follow a circle
x_collect = [x_post];
tic;
for i = 1:Ns
    u_plan = MPC_controller.planning(x_post,t);
    u = u_plan(:,1); % MPC paradigm
    [x_post, ~] = ext_kal_filt.predict(x_post, P_post, dt, u, t);
    x_collect = [x_collect, full(x_post)];
    t = t + dt;
end
computation_time = toc;

reference_points = ref.discrete_ref(t_span);
%plot(2*cos(linspace(0,2*pi,100)),2*sin(linspace(0,2*pi,100)))
figure(1)
plot(reference_points(1,:),reference_points(2,:),'xm');
hold on
plot(x_collect(1,:),x_collect(2,:),'og')