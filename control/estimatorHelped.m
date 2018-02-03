close all;

import casadi.*

% add the fake noise
rng(0);

T = 2 * pi; % time
Ns = 100; % number of steps
dt = T/Ns; 
sigma_vel = 0.05; % 0.05
sigma_omega = 3.5; % 3.5
sigma_y_pos = 0.05; % 0.05
sigma_y_ori = 3; % 3
sigma_y_omega = 0.5; % 0.5
noise_prefac_pos = 0.05; % 0.05
noise_prefac_ori = 0; %deg2rad(15);
noise_prefac_omega = 0;%deg2rad(5e-3);

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

% create a runge-kutta integrator
M = 4; % number of integration steps
fd = create_integrator.create_integrator_rk4(dynamics.f, M);

% create kalman-filter object for our model with pred. and upd. function
ext_kal_filt = kalman_filter.kalman_filter(fd, dynamics.h, Q, R);

% initial value for the states
P_post = 0.1 * eye(6);
x_post = [1; 0; 0 + pi/2; 0; 1; 1];

uVec = [6.88958658029 * 10 * ones(1,Ns);zeros(1,Ns)]; % u = 6.88958658029 * 10 -> acc = 1
cell_x_post = {x_post};
cell_P_post = {P_post};

P_post_nf = P_post;
x_post_nf = x_post;
cell_x_post_nf = {x_post_nf};
cell_P_post_nf = {P_post_nf};

%% ESTIMATION
x_sim = DM.zeros(6, Ns+1);
x_sim(:,1) = x_post;
y_sim_ideal = DM.zeros(4, Ns);
y_sim = DM.zeros(4, Ns);
t = 0;
for k = 1:Ns % eventually replace this loop by a mapaccum
    fprintf('Estimation Iteration %d\n', k);
    u = uVec(:,k);
    
    
    % SIMULATION
    [x_sim(:,k+1), ~] = ext_kal_filt.predict(x_sim(:, k), zeros(6), dt, u, 0);
    y_sim_ideal(:, k) = x_sim([1,2,3,6], k + 1);
    y_sim(1:2, k) = y_sim_ideal(1:2, k) + noise_prefac_pos * randn([2,1]);
    y_sim(3, k) = y_sim_ideal(3, k) + noise_prefac_ori * randn();
    y_sim(4, k) = y_sim_ideal(4, k) + noise_prefac_omega * randn();
    
    %------------what happens with the EKF---------------------
    % prediction step
    [x_prior, P_prior] = ext_kal_filt.predict(x_post, P_post, dt, u, 0);
    
    % correction step
    
    [x_post, P_post] = ext_kal_filt.update(x_prior, P_prior, y_sim(:,k));
    cell_x_post = {cell_x_post{:}, x_post};
    cell_P_post = {cell_P_post{:}, P_post};
    %-------------------------------------------------------------
    
    %---------------what I think happens with no filter (nf)------
    [x_prior_nf, P_prior_nf] = ext_kal_filt.predict(x_post_nf, P_post_nf, dt, u, 0);
    y_ideal_nf = x_prior_nf([1,2,3,6]); % simulate the noise
    
    x_post_nf = [y_sim(1:3,k); x_prior_nf(4:5); y_sim(4,k)];
    P_post_nf = P_prior_nf;
    cell_x_post_nf = {cell_x_post_nf{:}, x_post_nf};
    cell_P_post_nf = {cell_P_post_nf{:}, P_post_nf};
    %------------------------------------------------------------
    
    t = k * dt; % current time
end

% Plot position measurments
figure; grid on; hold on;
plot(full(y_sim_ideal(1,:)),full(y_sim_ideal(2,:)))
plot(full(y_sim(1,:)),full(y_sim(2,:)), 'x')
legend('Simulated', 'Measured');
xlabel('x');
ylabel('y');


x_real = kalman_filter.validate_kalman(T,Ns);
x_est = cell2mat(cellfun(@full, cell_x_post, 'uniformOutput', false));
cell_P_post = cellfun(@full, cell_P_post, 'uniformOutput', false);

x_est_nf = cell2mat(cellfun(@full, cell_x_post_nf, 'uniformOutput', false));
cell_P_post_nf = cellfun(@full, cell_P_post_nf, 'uniformOutput', false);
% call the function to check if Kalman filter is correct
results = ekf_analyse(x_real, x_est, cell_P_post); % change dummy argument P_post
results_nf = ekf_analyse(x_real, x_est_nf, cell_P_post_nf);

figure
subplot(3,2,1)
results.plot_px;
subplot(3,2,3)
results.plot_py
subplot(3,2,5)
results.plot_theta
subplot(3,2,2)
results.plot_vx
subplot(3,2,4)
results.plot_vy
subplot(3,2,6)
results.plot_omega

mse_px = results.error_px/Ns;
mse_py = results.error_py/Ns;
mse_theta = results.error_theta/Ns;
mse_vx = results.error_vx/Ns;
mse_vy = results.error_vy/Ns;
mse_omega = results.error_omega/Ns;

traj_handle = figure;
results.plot_trajectory;

% plot also the trajectory with no filter
figure(traj_handle)
p = plot(x_est_nf(1,:), x_est_nf(2,:),'g');
legend('initial plan', 'ekf', 'no filter')
xlabel('x position [m]')
ylabel('y position [m]')


% % plot the error ellipsis
% hold on
% for i=1:size(x_est,2)
%     M = cell_P_post{i};
%     M = full(M);
%     M = M(1:2,1:2);
%     error_ellipse(M,[x_est(1,i),x_est(2,i)]);
% end