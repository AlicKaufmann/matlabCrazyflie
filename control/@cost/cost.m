classdef cost
    methods
        function obj = cost(ref)
            % ref is a object of class reference
            
            % create the cost function
            import casadi.*
            u = MX.sym('u', 2);
            
            t = MX.sym('t',1);
            px = MX.sym('px',1);
            py = MX.sym('py',1);
            theta = MX.sym('theta',1);
            vx = MX.sym('vx', 1);
            vy = MX.sym('vy', 1);
            omega = MX.sym('omega',1);
            
            x = [px; py; theta; vx; vy; omega];
            
            reft = ref.ref(t);
            
            L = 100 * (px - reft(1))^2 + ...
                100 * (py - reft(2))^2; % + ...
            % theta^2 + ...
            % vx^2 + ...
            % vy^2  + ...
            % u(1)^2 + ...
                    % u(2)^2
            obj.L = Function('L',{x, u, t},{L});
        end    
    end

    properties
        L
    end 
end