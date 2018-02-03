classdef kalman_filter
    methods
        % constructor
        function obj = kalman_filter(fd, h, Q, R)
            import casadi.*

            % set process and noise covariances
            obj.Q = Q;
            obj.R = R;
            
            % create the predict function
            x_post = MX.sym('x_prior', 6);
            P_post = MX.sym('P_post', 6, 6);
            Ts = MX.sym('Ts', 1);
            u = MX.sym('u', 2);
            
            Jfd = fd.jacobian_old(0,0); % jacobian of 0-th output wrt 0-th input
            Jfd_x = Jfd('x0', x_post, 'Ts', Ts, 'p', u);
            F = Jfd_x.jac_xf_x0;
            L = MX.eye(6);
            P_prior = F * P_post * F' + L * Q * L';
            x_prior = fd(x_post, Ts, u);
            obj.predict = Function('predict', {x_post, P_post, Ts, u}, {x_prior, P_prior});
            
            % creating the update function
            M = MX.eye(3); % jacobian wrt v of measMap-->identity for additive noise
            H = MX([1,0,0,0,0,0 % jacobian wrt x of measMap
                    0,1,0,0,0,0;
                    0,0,0,0,0,1]);
            y = MX.sym('y',3);
            P_prior = MX.sym('P_prior',6,6);
            x_prior = MX.sym('x_prior',6,1);
            
            K = P_prior * H' / (H * P_prior * H' + M * R * M');
            x_post = x_prior + K * (y - h(x_prior));
            P_post = (MX.eye(6) - K * H) * P_prior;
            
            obj.update = Function('update', {x_prior, P_prior, y}, {x_post, P_post});
            
        end
        
        % other methods
        
    end
    properties
        
        % process and noise covariance
        Q
        R
        
        % prediction function
        predict
        
        % update function
        update
    end
end