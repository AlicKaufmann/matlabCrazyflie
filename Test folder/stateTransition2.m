function ds = stateTransition(s) %(t, s, uTrans, uTransTime,uRot, uRotTime)
% actually there needs to be 2 u : one fore the translation uT and one for
% the rotation uR.
    
% hardcode some stuff
    %ds = zeros(6,1);
    t=1;
    uTrans = ones(1,10);
    uTransTime = 0:9;
    
    uRot = ones(1,10);
    uRotTime = 0:9;

    uTrans = interp1(uTransTime, uTrans, t);
    uRot = interp1(uRotTime, uRot, t);
    
   ds = [s(4);
        s(5);
        s(6);
        interp1([0,2,3,5,6,7,8,9,10]', [0,0.2244,0.3850,0.6309,0.7839,1.022,1.1630,1.3959,1.5340]', uTrans) * cos(s(3));
        interp1([0,2,3,5,6,7,8,9,10]', [0,0.2244,0.3850,0.6309,0.7839,1.022,1.1630,1.3959,1.5340]', uTrans) * sin(s(3));
        interp1((0:10:100)', [0, 6.3632, 16.8374, 25.6822, 35.5810, 45.7588, 53.0103, 60.5996, 83.5957, 89.0708, 96.1055]',uRot)];
end