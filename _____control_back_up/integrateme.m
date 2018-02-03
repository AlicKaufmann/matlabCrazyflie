function [t,s] = integrateme(f,st,tspan)
    [t,s] = ode45(f,tspan,st);
end