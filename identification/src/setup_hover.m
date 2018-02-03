clear 

J = 1; % Inertia
m = 1; % Mass

% Thrust gain of each propeller

% Gain from propeller to force
K_RF = 1 * (0.95 + rand*0.1); % Right, forward thrust
K_RB = 1 * (0.95 + rand*0.1); % Right, backward thrust
K_LF = 1 * (0.95 + rand*0.1); % Left, forward thrust
K_LB = 1 * (0.95 + rand*0.1); % Left, backward thrust

% Gain from propeller to torque
T_RF = 1 * (0.95 + rand*0.1); % Right, forward thrust
T_RB = 1 * (0.95 + rand*0.1); % Right, backward thrust
T_LF = 1 * (0.95 + rand*0.1); % Left, forward thrust
T_LB = 1 * (0.95 + rand*0.1); % Left, backward thrust
