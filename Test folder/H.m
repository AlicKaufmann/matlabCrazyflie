function y = H(x)
%     N=10;
%     u = 1:(N-1)/99:N; %linspace(1,N,100);
%     v = 1:(2*N-1)/99:2*N; %linspace(1,2*N,100)
%         x1 = x;
%         x2 = 2*x;
%     t = 3;
%     for i=1:N
%         x1 = stateTransition(t,x1); 
%     end
%     for i=1:N
%         x2 = stateTransition(t,x2); 
%     end
%         y = 0.5*(x1+2*x2);

a = x;
b = x;
N=10;
for i = 1:N
    a = 3*G(a)+1;
    b = 5*G(b)+2;
end
y=a+b/2;
end