import casadi.*

% add the fake noise

T = 10; % time
Ns = 100; % number of steps
dt = T/Ns; 
noise_prefac = 0.1;

Q = 0.1 * MX.eye(6); % process noise covariance
R = 0.1 * MX.eye(4); % measurment noise covariance

% object with transition and measurement map
dynamics = hovercraft_model();

% create a runge-kutta integrator
M = 4; % number of integration steps
fd = create_integrator.create_integrator_rk4(dynamics.f, M);

% create kalman-filter object for our model with pred. and upd. function
ext_kal_filt = kalman_filter.kalman_filter(fd, dynamics.h, Q, R);

% initial value for the states
P_post = eye(6);
x_post = [1; 0; 0 + pi/2; 0; 1; 1];

uVec = [6.88958658029 * ones(1,Ns);zeros(1,Ns)]; % u = 6.88958658029 -> acc = 1
cell_x_post = {x_post};
cell_P_post = {P_post};
t = 0;
for k = 1:Ns % eventually replace this loop by a mapaccum
    
    u = uVec(:,k);
%     y = yVec(:,k+1);
    
    % prediction step
    [x_prior, P_prior] = ext_kal_filt.predict(x_post, P_post, dt, u);
   
    % correction step
    y_ideal = x_prior([1,2,3,6]); % simulate the noise
    y_sim = y_ideal + noise_prefac * (rand(size(y_ideal))-0.5); % we substract 0.5 to have white noise
    
    % if we have no filter, would we update the states like this ?
    x_post = [y_sim(1:3); x_prior(4:5) ;y(4)];
    P_post = P_prior;
    
    cell_x_post = {cell_x_post{:}, x_post};
    cell_P_post = {cell_P_post{:}, P_post};

    t = k * dt; % current time
end

x_real = kalman_filter.validate_kalman;
x_est = cell2mat(cellfun(@full, cell_x_post, 'uniformOutput', false));

% call the function to check if Kalman filter is correct
results = ekf_analyse(x_real, x_est, P_post); % change dummy argument P_post

results.plot_px
% results.plot_py
% results.plot_theta
% results.plot_vx
% results.plot_vy
% results.plot_omega
results.plot_trajectory
