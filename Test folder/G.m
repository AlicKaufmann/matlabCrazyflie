function y = G(x)
    t=3;
    uTime = t;
    y = [x(1) + t;
        interp1([1,2,3,4],[10,20,30,40],t)];
end
