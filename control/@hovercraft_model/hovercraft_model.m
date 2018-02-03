classdef hovercraft_model
    methods
        % constructor
        function obj = hovercraft_model()
            import casadi.*
            
            u = MX.sym('u',2); % control input, u = [uT, UR],parameter for the integration
            t = MX.sym('t', 1);
            
            px = MX.sym('px',1);
            py = MX.sym('py',1);
            theta = MX.sym('theta',1);
            vx = MX.sym('vx', 1);
            vy = MX.sym('vy', 1);
            omega = MX.sym('omega',1);
            
            
            uTp = [0,20,30,50,60,70,80,90,100];
            uT = [0,0.2244,0.3850,0.6309,0.7839,1.022,1.1630,1.3959,1.5340];
            uTp_ = -uTp; % eventually identify the right values
            uT_ = -uT; % eventually identify the right values
            uRp = 0:10:100;
            uR = [0, 6.3632, 16.8374, 25.6822, 35.5810, 45.7588, 53.0103, 60.5996, 83.5957, 89.0708, 96.1055];
            uRp_ = -uRp; % eventually identify the right values
            uR_ = -uR; % eventually identify the right values
            
            transMap = casadi.interpolant('LUT','bspline',{union(uTp_, uTp)}, union(uT,uT_));
            rotMap = casadi.interpolant('LUT','bspline',{union(uRp_, uRp)}, union(uR_,uR));
            
            
            states = [px;py;theta;vx;vy;omega];
            rhs = [vx;...
                vy;...
                omega;...
                transMap(u(1))*cos(theta + pi/2);...
                transMap(u(1))*sin(theta + pi/2);...
                rotMap(u(2))];
            
            obj.f = Function('f',{states, u, t},{rhs},{'x','u','t'},{'rhs'}); % fonction of the dynamics
            obj.h = Function('h',{states},{states([1,2,3,6])}); % measurment function
        end
    end
    properties
        % transition and measurment maps
        f
        h
    end
end