% KalmanValidation

N = 101;
T = 10;
t = linspace(0, T, N);
dt = t(2) - t(1);
vx = -sin(t);
vy = cos(t);
px = cos(t);
py = sin(t);
ax = -cos(t);
ay = -sin(t);
theta = t + pi/2; % linear increase of the angle because speed on circle is constant
% theta = atan2(ay,ax);
omega = gradient(theta, t);

xReal = [px; py; theta; vx; vy; omega];

% simulate real measurments
noise_prefac = 0.02;

% if we give the correct measurments shifted by some random noise
noise = noise_prefac * (rand(4, N)-0.5);
y = [px; py; theta; omega] + noise;

% [cell_x_post, cell_P_post] = no_filter(noise_prefac);
[cell_x_post, cell_P_post] = estimator2(noise_prefac);
% [cell_x_post, cell_P_post] = test(noise_prefac);

xEst = cell2mat(cellfun(@full, cell_x_post, 'uniformOutput', false));

% plot theta
figure(1)
plot(xEst(3,:))
hold on
plot(theta)
plot(y(3,:))
legend('theta estimated','theta real','theta mesured')
error_theta = mean((theta-xEst(3,:)).^2);

% plot vx
figure(2)
plot(xEst(4,:))
hold on
plot(vx)
legend('vx estimated','vx real')
error_vx = mean((vx-xEst(4,:)).^2);

% plot vy
figure(3)
plot(xEst(5,:))
hold on
plot(vy)
legend('vy estimated','vy real')
error_vy = mean((vy-xEst(5,:)).^2);

% error in position
error_px = mean((px-xEst(1,:)).^2);
error_py = mean((py-xEst(2,:)).^2);

% plot the position
figure(4)
hold on
plot(xEst(1,:),xEst(2,:))

% plot the error ellipse

for i=1:size(xEst,2)
    M = cell_P_post{i};
    M = full(M);
    M = M(1:2,1:2);
    error_ellipse(M,[xEst(1,i),xEst(2,i)]);
end
hold off

