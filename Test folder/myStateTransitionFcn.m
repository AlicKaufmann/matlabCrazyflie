function xNext = myStateTransitionFcn(x)

    Ts = 0.01; % external timestep
    K = 100;
    t = 0:Ts/K:Ts*(1-1/K);
    
    s = zeros(K,6);
    %t = linspace(0,Ts,K);
    
    %x=[0,0,0,0,0,0];
    [dummy,s] = RK4(@stateTransition, t, x);
    xNext = s(K,1:6)';
    % v = s(end,2);
end

