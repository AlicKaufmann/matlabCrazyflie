function F = create_integrator_cost(trans_map, M, cost)
% f is the function we integrate (casadi form)
% M is the number of integration steps.
% note that the created integrator can integrate non-autonomous ODEs.
import casadi.*

x = MX.sym('x', 6);
u = MX.sym('u', 2);
t = MX.sym('t', 1);

f = Function('f', {x,u,t},{trans_map(x,u,t),cost(x, u, t)});

t0 = MX.sym('t0', 1);
t = t0;
u = MX.sym('u', 2);
Ts = MX.sym('Ts',1);
DT = Ts/M;
x0 = MX.sym('x0', 6);
x = x0;
q = 0;
for j=1:M
    [k1, k1_q] = f(x, u, t);
    [k2, k2_q] = f(x + DT/2 * k1, u, t + DT/2);
    [k3, k3_q] = f(x + DT/2 * k2, u, t + DT/2);
    [k4, k4_q] = f(x + DT * k3, u, t + DT);
    t = t + DT;
    x = x + DT/6 * (k1 + 2 * k2 +2 * k3 + k4);
    q = q + DT/6 * (k1_q + 2 * k2_q + 2 * k3_q + k4_q);
end
F = Function('F', {x0, Ts, u, t0}, {x,q}, {'x0','Ts','p','t0'}, {'xf','qf'});
end