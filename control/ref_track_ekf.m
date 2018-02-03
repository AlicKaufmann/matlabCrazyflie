import casadi.*

% add the fake noise
rng(0);

T = 10; % time
Ns = 100; % number of steps
N = 3; % horizon of the MPC controller
dt = T/Ns; 
t_span = 0:dt:T;
noise_prefac = 0.1;


sigma_vel = 0.05; % 0.05
sigma_omega = 3.5; % 3.5
sigma_y_pos = 0.05; % 0.05
sigma_y_ori = 3; % 3
sigma_y_omega = 0.5; % 0.5
noise_prefac_pos = 0.05; % 0.05
noise_prefac_ori = deg2rad(0); % deg2rad(2)
noise_prefac_omega = deg2rad(0); % deg2rad(0.5)

Q = DM.eye(6); % process noise covariance
Q(1,1) = dt^3/3 *sigma_vel^2;
Q(2,2) = Q(1,1);
Q(1,4) = dt^2/2 *sigma_vel^2;
Q(4,1) = Q(1,4);
Q(2,5) = Q(1,4);
Q(5,2) = Q(1,4);
Q(4,4) = dt*sigma_vel^2;
Q(5,5) = Q(4,4);
Q(3,3) = dt^3/3 *sigma_omega^2;
Q(3,6) = dt^2/2 *sigma_omega^2;
Q(6,3) = Q(3,6);
Q(6,6) = dt*sigma_omega^2;
R = diag(DM([sigma_y_pos^2; sigma_y_pos^2; sigma_y_ori^2; sigma_y_omega^2])); % measurment noise covariance

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
cell_P_post = {};

% preallocate simulation variables
x_sim = DM.zeros(6, Ns+1);
x_sim(:,1) = x_post;
y_sim_ideal = DM.zeros(4, Ns);
y_sim = DM.zeros(4, Ns);

tic;
for i = 1:Ns
    u_plan = MPC_controller.planning(x_post,t);
    u = u_plan(:,1); % MPC paradigm
    
    % simulation
    [x_sim(:,i+1), P_sim] = ext_kal_filt.predict(x_sim(:, i), P_post, dt, u, 0);
    y_sim_ideal(:, i) = x_sim([1,2,3,6], i + 1);
    y_sim(1:2, i) = y_sim_ideal(1:2, i) + noise_prefac_pos * randn([2,1]);
    y_sim(3, i) = y_sim_ideal(3, i) + noise_prefac_ori * randn();
    y_sim(4, i) = y_sim_ideal(4, i) + noise_prefac_omega * randn();
    
    % EKF
    % prediction step
    x_prior = x_sim(:,i+1);
    P_prior = P_sim;
    
    % update step
    [x_post, P_post] = ext_kal_filt.update(x_prior, P_prior, y_sim(:,i));
    
    x_collect = [x_collect, full(x_post)];
    cell_P_post = [cell_P_post, {P_post}];
    
    t = t + dt;
end
computation_time = toc;


cell_P_post = cellfun(@full, cell_P_post, 'uniformOutput', false);
reference_points = ref.discrete_ref(t_span);

results = ekf_analyse([reference_points;zeros(4,size(reference_points,2))], x_collect, cell_P_post);

%plot(2*cos(linspace(0,2*pi,100)),2*sin(linspace(0,2*pi,100)))
figure(1)
plot(reference_points(1,:),reference_points(2,:),'xm');
hold on
plot(x_collect(1,:),x_collect(2,:),'og')
title('tracking a circle with MPC controller')
xlabel('px position')
ylabel('py position')

figure(2)
plot(abs(reference_points(1,:)-x_collect(1,:)));
title('x distance to reference [m]')
xlabel('point index i')
ylabel('distance to reference [m]')

figure(3)
plot(abs(reference_points(2,:)-x_collect(2,:)));
title('y distance to reference [m]')
xlabel('point index i')
ylabel('distance to reference [m]')