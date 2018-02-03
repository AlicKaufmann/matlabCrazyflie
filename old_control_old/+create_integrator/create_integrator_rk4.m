function F = create_integrator_rk4(f, M)
% f is the function we integrate (casadi form)
% M is the number of integration steps.

    import casadi.*
    
    u = MX.sym('u', 2);
    Ts = MX.sym('Ts',1);
    DT = Ts/M;
    x0 = MX.sym('x', 1);
    x = x0;
    for j = 1:M
        k1 = f(x, u);
        k2 = f(x + DT/2 * k1, u);
        k3 = f(x + DT/2 * k2, u);
        k4 = f(x + DT * k3, u);
        x = x + DT/6 * (k1 + 2 * k2 + 2 * k3 + k4);
    end
    F = Function('F', {x0, Ts, u}, {x},{'x0', 'Ts', 'p'}, {'xf'});
end