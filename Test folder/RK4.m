function [t,s] = RK4(f,t,s0)
% Self implemented classical Runge-Kutta of order 4. 
% s0 should be a column vector

s = s0(:)'; % to be shure it is a row.
%f = @(t,s)reshape(f(t,s),1,length(s0)); % to be shure f returns a row vector

for k = 1:99 % length(t)-1
    tk = t(k);
    sk = s(k,:);
    dt = t(k+1)-t(k);
    
    k1 = f(tk, sk');
    k2 = f(tk+dt/2, sk'+k1*dt/2);
    k3 = f(tk+dt/2, sk'+k2*dt/2);
    k4 = f(tk+dt, sk'+k3*dt);
    
    s(k+1,:) = (sk' + dt * (1/6 * k1 + 1/3 * k2 + 1/3 * k3 + 1/6* k4))';
end

end