% at first we just try to drive the hovercraft at x = 0, y = 0 and omega =
% 0 from an initial position x != 0 and y !=0. We  note that this is
% possible since there is a control law, namely u = 0 that stabilizes the
% system at this state, i.e. if we are at x* = 0 and we input u* = 0 we
% stay at x* = 0;


import casadi.*

T = 10; % Time horizon
N = 20; % number of control intervals -> this is actually the horizon for me
Ns = 10; % number of steps we do for the tracking

% Declare model variables
x1 = SX.sym('x1');
x2 = SX.sym('x2');
x = [x1; x2];
u = SX.sym('u');

% Model equations
xdot = [(1-x2^2)*x1 - x2 + u; x1];

% Objective term
L = 100*(x1+1)^2; %+ 100*(x2-1)^2; %+ u^2;

% Formulate discrete time dynamics
if false
   % CVODES from the SUNDIALS suite
   dae = struct('x',x,'p',u,'ode', xdot,'quad',L);
   opts = struct('tf',T/N);
   F = integrator('F', 'cvodes', dae, opts);
else
   % Fixed step Runge-Kutta 4 integrator
   M = 4; % RK4 steps per interval
   DT = T/N/M;
   f = Function('f', {x, u}, {xdot, L});
   X0 = MX.sym('X0', 2);
   U = MX.sym('U');
   X = X0;
   Q = 0;
   for j=1:M
       [k1, k1_q] = f(X, U);
       [k2, k2_q] = f(X + DT/2 * k1, U);
       [k3, k3_q] = f(X + DT/2 * k2, U);
       [k4, k4_q] = f(X + DT * k3, U);
       X=X+DT/6*(k1 +2*k2 +2*k3 +k4);
       Q = Q + DT/6*(k1_q + 2*k2_q + 2*k3_q + k4_q);
    end
    F = Function('F', {X0, U}, {X, Q}, {'x0','p'}, {'xf', 'qf'});
end

% Evaluate at a test point
Fk = F('x0',[0.2; 0.3],'p',0.4);
disp(Fk.xf)
disp(Fk.qf)

% Start with an empty NLP
x0 = [0;0];
u_opt = [];
for i = 1:Ns
    w={};
    w0 = [];
    lbw = [];
    ubw = [];
    J = 0;
    g={};
    lbg = [];
    ubg = [];
    
    % Formulate the NLP
    Xk = x0; % initial state
    for k=0:N-1
        % New NLP variable for the control
        Uk = MX.sym(['U_' num2str(k)]);
        w = {w{:}, Uk};
        lbw = [lbw, -100];
        ubw = [ubw,  100];
        w0 = [w0,  0];
        
        % Integrate till the end of the interval
        Fk = F('x0',Xk,'p', Uk);
        Xk = Fk.xf;
        J=J+Fk.qf;
        
        % Add inequality constraint
        g = {g{:}, Xk(1)};
        lbg = [lbg; -inf];
        ubg = [ubg;  inf];
    end
    
    % Create an NLP solver
    prob = struct('f', J, 'x', vertcat(w{:}), 'g', vertcat(g{:}));
    solver = nlpsol('solver', 'ipopt', prob);
    
    % Solve the NLP
    sol = solver('x0', w0, 'lbx', lbw, 'ubx', ubw, ...
        'lbg', lbg, 'ubg', ubg);
    w_opt = full(sol.x);
    
    u_opt = [u_opt; w_opt(1,:)];
    Fv = F('x0',x0,'p',w_opt(1,:)); % since we are doing MPC, we take just apply the first input
    x = Fv.xf;
    x0 = x; % for the next step, we will x as initial state so x0 <--x
end

% Plot the solution
% u_opt = w_opt;
x_opt = [0;0];
for k=0:Ns-1
    Fk = F('x0', x_opt(:,end), 'p', u_opt(k+1));
    x_opt = [x_opt, full(Fk.xf)]; % for plotting at the end
end
x1_opt = x_opt(1,:);
x2_opt = x_opt(2,:);
tgrid = linspace(0, T, N+1);
clf;
hold on
plot(tgrid(1:length(x1_opt)), x1_opt, '--')
plot(tgrid(1:length(x2_opt)), x2_opt, '-')
stairs(tgrid(1:length(u_opt)+1), [u_opt; nan], '-.')
xlabel('t')
legend('x1','x2','u')
