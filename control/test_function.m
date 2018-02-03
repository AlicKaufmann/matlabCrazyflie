function F = test_function(f,g)
import casadi.*
x = MX.sym('x',1);
y = MX.sym('y',1);
F = Function('F', {x,y}, {f(x), g(x,y)});
end