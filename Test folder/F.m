function s = F(x)

    Ts = 0.01; % external timestep
    K = 100;
    t = 0:Ts/K:Ts*(1-1/K);

    s = zeros(K,6);

for k = 1:99 % length(t)-1
    tk = t(k);
    sk = s(k,:);
    dt = t(k+1)-t(k);
    
    k1 = stateTransition(tk, sk');
    k2 = stateTransition(tk+dt/2, sk'+k1*dt/2);
    k3 = stateTransition(tk+dt/2, sk'+k2*dt/2);
    k4 = stateTransition(tk+dt, sk'+k3*dt);
    
    s(k+1,:) = (sk' + dt * (1/6 * k1 + 1/3 * k2 + 1/3 * k3 + 1/6* k4))';
    
end
end
