classdef MPC < handle
    methods
        function obj = MPC(dynamics, tracking_cost, N, dt)
            import casadi.*
            obj.cost = tracking_cost;
            obj.N = N;
            obj.dt = dt;
            M = 4;
            obj.qd = create_integrator.create_integrator_cost(dynamics.f, M, tracking_cost.L);
            obj.u_all = {};
            
            
            %---------------optimal control problem-------------------
            
        end
        function control_plan = planning(obj, x, t)
            % x is the current state estimated from the EKF
            % t is the time at which we compute the control plan
            
            import casadi.* % Is there a way to import one and for all
            
            % initialise problem
            w = {};
            w0 = [];
            lbw = [];
            ubw = [];
            J = 0;
            g = {};
            lbg = [];
            ubg = [];
            
            xk = x;
            
            % we initialise the time used in the prediction to the current time
            pred_t = t;
            for k = 1:obj.N-1
                uk = MX.sym(['u',num2str(k)],2);
                w = [w, {uk}];
                lbw = [lbw; [-100; -100]]; % input should be constrained to [0%, 100%]
                ubw = [ubw; [100; 100]];
                w0 = [w0; [0; 0]];
                
                % integration on one timestep
                fdk = obj.qd('x0', xk, 'Ts', obj.dt, 'p', uk,'t0', pred_t);
                xk = fdk.xf;
                J = J + fdk.qf;
                
                % Add inequality constraints
                g = {g{:}, xk([1,2])}; % we constraint px and py, constraint theta in [-pi,pi]?
                lbg = [lbg; [-4; -6]]; % x and y constrained wrt size of airhockey table
                ubg = [ubg; [4; 6]];
                pred_t = pred_t + obj.dt;
            end
            
            nlp = struct('x',vertcat(w{:}),'f', J, 'g', vertcat(g{:}));
            solver = nlpsol('solver', 'ipopt', nlp);
            sol = solver('x0', w0, 'lbg', lbg, 'ubg', ubg, 'lbx', lbw, 'ubx', ubw);
            control_plan = reshape(full(sol.x),[2,obj.N-1]);
            obj.u_plan = control_plan;
            obj.u_all = [obj.u_all, {control_plan}];
            
            obj.x_prev = x; % set previous state est. to current state est.
            obj.t_prev = t;
        end
        function draw_contr_plan(obj,idx,x_init)
            u = obj.u_all{idx};
            % compute the states for the plan u_plan and x_prev
            x = x_init;
            x_plan = x;
            t = obj.t_prev;
            for k=1:obj.N-1
                x = obj.qd(x,obj.dt,u(:,k),t);
                t = t + obj.dt;
                x_plan = [x_plan, x];
            end
            plot(full(x_plan(1,:)),full(x_plan(2,:)),'ok','MarkerFaceColor','g')
        end
        
        
    end
    properties
        N % horizon
        qd % state transition map & cost integration
        cost % casadi function
        dt % time step
        u_plan % the last control plan that was computed
        x_prev % the previous state estimate we had
        t_prev
        u_all
    end
end