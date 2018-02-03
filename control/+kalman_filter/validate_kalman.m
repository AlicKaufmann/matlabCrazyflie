
function x = validate_kalman(T,Ns);
% validate_kalman() creates the trajectory we want and returns its states

t = linspace(0, T, Ns+1);
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

x = [px; py; theta; vx; vy; omega];

% simulate real measurments
noise_prefac = 0.02;

% if we give the correct measurments shifted by some random noise
noise = noise_prefac * (rand(4, Ns+1)-0.5);
y = [px; py; theta; omega] + noise;


