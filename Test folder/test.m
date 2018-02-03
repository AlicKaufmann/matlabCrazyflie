% predict function
import casadi.*

x = MX.sym('x');
y = MX.sym('y');
f = Function('f',{x,y},{y,x},{'a','b'},{'c','d'});

x0 = MX.sym('x0');
p = MX.sym('p');
x = MX.sym('x');
T = MX.sym('T');
dae = struct('x',x,'p',T,'ode',T*x);
F = integrator('F', 'cvodes', dae);
jac = F.jacobian;
sol = F('x0', 1,'p',3);
expr = F('x0',x0,'p',p);
expr2 = expr.xf;
JF = jacobian(expr2,x0);

