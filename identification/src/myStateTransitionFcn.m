function xNext = myStateTransitionFcn(x,w)

    Ts = 0.01; % external timestep
    K = 100;
    t = linspace(0,Ts,K);
    s = zeros(K,6);
    
    %x=[0,0,0,0,0,0];
    [dummy,s] = ode45(@stateTransition,t, x);
    xNext = s(K,1:6)' + w;
    % v = s(end,2);
end

