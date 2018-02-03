function ds = stateTransition(t,s) %(t, s, uTrans, uTransTime,uRot, uRotTime)
% actually there needs to be 2 u : one fore the translation uT and one for
% the rotation uR.
    
% hardcode some stuff
    ds = zeros(6,1);
    
    uTrans = 0*ones(10,1)';
    uTransTime = 0:9';
    
    uRot = 0*ones(10,1)';
    uRotTime = 0:9';

    uTrans = interp1(uTransTime, uTrans, t);
    uRot = interp1(uRotTime, uRot, t);
    
    ds(1) = s(4);
    ds(2) = s(5);
    ds(3) = s(6);
    ds(4) = interp1q([0,2,3,5,6,7,8,9,10]', [0,0.2244,0.3850,0.6309,0.7839,1.022,1.1630,1.3959,1.5340]', uTrans) * cos(s(3));
    ds(5) = interp1q([0,2,3,5,6,7,8,9,10]', [0,0.2244,0.3850,0.6309,0.7839,1.022,1.1630,1.3959,1.5340]', uTrans) * sin(s(3));
    ds(6) = interp1((0:10:100)', [0, 6.3632, 16.8374, 25.6822, 35.5810, 45.7588, 53.0103, 60.5996, 83.5957, 89.0708, 96.1055]',uRot);
end