function F = create_integrator_rk4(f, M)
% f is the function we integrate (casadi form)
% M is the number of integration steps.
% note that the created integrator can integrate non-autonomous ODEs.

    import casadi.*
    
    t0 = MX.sym('t0', 1);
    t = t0;
    u = MX.sym('u', 2);
    Ts = MX.sym('Ts',1);
    DT = Ts/M;
    x0 = MX.sym('x0', 6);
    x = x0;
    for j = 1:M
        k1 = f(x, u, t);
        k2 = f(x + DT/2 * k1, u, t + DT/2);
        k3 = f(x + DT/2 * k2, u, t + DT/2);
        k4 = f(x + DT * k3, u, t + DT);
        x = x + DT/6 * (k1 + 2 * k2 + 2 * k3 + k4);
        t = t + DT;
    end
    F = Function('F', {x0, Ts, u, t0}, {x},{'x0', 'Ts', 'p','t0'}, {'xf'});
end