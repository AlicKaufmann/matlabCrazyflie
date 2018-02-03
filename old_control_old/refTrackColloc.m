%
%     This file is part of CasADi.
%
%     CasADi -- A symbolic framework for dynamic optimization.
%     Copyright (C) 2010-2014 Joel Andersson, Joris Gillis, Moritz Diehl,
%                             K.U. Leuven. All rights reserved.
%     Copyright (C) 2011-2014 Greg Horn
%
%     CasADi is free software; you can redistribute it and/or
%     modify it under the terms of the GNU Lesser General Public
%     License as published by the Free Software Foundation; either
%     version 3 of the License, or (at your option) any later version.
%
%     CasADi is distributed in the hope that it will be useful,
%     but WITHOUT ANY WARRANTY; without even the implied warranty of
%     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
%     Lesser General Public License for more details.
%
%     You should have received a copy of the GNU Lesser General Public
%     License along with CasADi; if not, write to the Free Software
%     Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
%

% An implementation of direct collocation
% Joel Andersson, 2016

import casadi.*

% Degree of interpolating polynomial
d = 3;

% Get collocation points
tau_root = [0 collocation_points(d, 'legendre')];

% Coefficients of the collocation equation
C = zeros(d+1,d+1);

% Coefficients of the continuity equation
D = zeros(d+1, 1);

% Coefficients of the quadrature function
B = zeros(d+1, 1);

% Construct polynomial basis
for j=1:d+1
  % Construct Lagrange polynomials to get the polynomial basis at the collocation point
  coeff = 1;
  for r=1:d+1
    if r ~= j
      coeff = conv(coeff, [1, -tau_root(r)]);
      coeff = coeff / (tau_root(j)-tau_root(r));
    end
  end
  % Evaluate the polynomial at the final time to get the coefficients of the continuity equation
  D(j) = polyval(coeff, 1.0);

  % Evaluate the time derivative of the polynomial at all collocation points to get the coefficients of the continuity equation
  pder = polyder(coeff);
  for r=1:d+1
    C(j,r) = polyval(pder, tau_root(r));
  end

  % Evaluate the integral of the polynomial to get the coefficients of the quadrature function
  pint = polyint(coeff);
  B(j) = polyval(pint, 1.0);
end

% Time horizon
T = 10;

% Declare time variable

t = MX.sym('t',1);

% Declare model variables
px = MX.sym('px');
py = MX.sym('py');
theta = MX.sym('theta');
vx = MX.sym('vx');
vy = MX.sym('vy');
omega = MX.sym('omega');
states = [px;py;theta;vx;vy;omega];
u = MX.sym('u',2); % control input, u = [uT, UR],parameter for the integration

% LUT for u

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

% Model equations
rhs = [vx;...
    vy;...
    omega;...
    transMap(u(1))*cos(theta + pi/2);... % +pi/2 because acceleration orthog. to HC angle 
    transMap(u(1))*sin(theta + pi/2);...
    rotMap(u(2))];

% Objective term
r = 2;
rx = r * cos(t);
ry = r * sin(t);
cost = 100 * (px + 1)^2 + ...
       100 * (py - 0)^2 + ...
       (theta-1.56)^2; % + ...
        % vx^2 + ...
        % vy^2  + ...
        % u(1)^2 + ...
        % u(2)^2

% Continuous time dynamics
f = Function('f', {states, u}, {rhs, cost});

% Control discretization
N = 30; % number of control intervals
h = T/N;

% Start with an empty NLP
w={};
w0 = [];
lbw = [];
ubw = [];
J = 0;
g={};
lbg = [];
ubg = [];

% "Lift" initial conditions
Xk = MX.sym('X0', 6);
w = {w{:}, Xk};
lbw = [lbw; [0; 0; pi/2; 0; 0; 0]];
ubw = [ubw; [0; 0; pi/2; 0; 0; 0]];
w0 = [w0; zeros(6,1)];

% Formulate the NLP
for k=0:N-1
    % New NLP variable for the control
    Uk = MX.sym(['U_' num2str(k)],2);
    w = {w{:}, Uk};
    lbw = [lbw; [0; -0]];
    ubw = [ubw;  [100; 0]];
    w0 = [w0;  [0; 0]];

    % State at collocation points
    Xkj = {};
    for j=1:d
        Xkj{j} = MX.sym(['X_' num2str(k) '_' num2str(j)], 6);
        w = {w{:}, Xkj{j}};
        lbw = [lbw; [-inf; -inf; -inf; -inf; -inf; -inf]];
        ubw = [ubw; [inf;  inf; inf; inf; inf; inf]];
        w0 = [w0; zeros(6,1)];
    end

    % Loop over collocation points
    Xk_end = D(1)*Xk;
    for j=1:d
       % Expression for the state derivative at the collocation point
       xp = C(1,j+1)*Xk;
       for r=1:d
           xp = xp + C(r+1,j+1)*Xkj{r};
       end

       % Append collocation equations
       [fj, qj] = f(Xkj{j},Uk);
       g = {g{:}, h*fj - xp};
       lbg = [lbg; zeros(6,1)];
       ubg = [ubg; zeros(6,1)];

       % Add contribution to the end state
       Xk_end = Xk_end + D(j+1)*Xkj{j};

       % Add contribution to quadrature function
       J = J + B(j+1)*qj*h;
    end

    % New NLP variable for state at end of interval
    Xk = MX.sym(['X_' num2str(k+1)], 6);
    w = {w{:}, Xk};
    lbw = [lbw; [-4; -6; -inf; -inf; -inf; -inf]];
    ubw = [ubw;  [4;  6; inf; inf; inf; inf]];
    w0 = [w0; zeros(6,1)];

    % Add equality constraint
    g = {g{:}, Xk_end-Xk};
    lbg = [lbg; zeros(6,1)];
    ubg = [ubg; zeros(6,1)];
end

% Create an NLP solver
prob = struct('f', J, 'x', vertcat(w{:}), 'g', vertcat(g{:}));
solver = nlpsol('solver', 'ipopt', prob);

% Solve the NLP
sol = solver('x0', w0, 'lbx', lbw, 'ubx', ubw,...
            'lbg', lbg, 'ubg', ubg);
w_opt = full(sol.x);

% % Plot the solution
% x1_opt = w_opt(1:3+2*d:end);
% x2_opt = w_opt(2:3+2*d:end);
% u_opt = w_opt(3:3+2*d:end);
% tgrid = linspace(0, T, N+1);
% clf;
% hold on
% plot(tgrid, x1_opt, '--')
% plot(tgrid, x2_opt, '-')
% stairs(tgrid, [u_opt; nan], '-.')
% xlabel('t')
% legend('x1','x2','u')

%

px_opt = w_opt(1:2 + 6 * (d + 1):end);
py_opt = w_opt(2:2 + 6 * (d + 1):end);
theta_opt = w_opt(3:2 + 6 * (d + 1):end);
vx_opt = w_opt(4:2 + 6 * (d + 1):end);
vy_opt = w_opt(5:2 + 6 * (d + 1):end);
omega_opt = w_opt(6:2 + 6 * (d + 1):end);
u_trans_opt = w_opt(7:2 + 6 * (d + 1):end);
u_rot_opt = w_opt(8:2 + 6 * (d + 1):end);

time = 0:h:T;
x = [px_opt, py_opt, theta_opt, vx_opt, vy_opt, omega_opt];