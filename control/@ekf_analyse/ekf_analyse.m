classdef ekf_analyse
    methods
        % constructor, takes states and covariance matrices as arg. xTrue
        % is the true values of the states and x the one we estimated
        function obj = ekf_analyse(xTrue,x,P)
            % statess
            obj.var_px = cellfun(@(P) P(1,1), P);
            obj.xTrue = xTrue;
            obj.xEst = x;
            
            % errors
            error = sum(abs(xTrue-x), 2);
            obj.error_px = error(1);
            obj.error_py = error(2);
            obj.error_theta = error(3);
            obj.error_vx = error(4);
            obj.error_vy = error(5);
            obj.error_omega = error(6);
        end
        
        function f = plot_px(obj)
            hold on
            plot(obj.xTrue(1,:))
            % errorbar(obj.xEst(1,:), obj.var_px)
            plot(obj.xEst(1,:),'r-')
%             legend('true px', 'estimated px')
            title('p_x')
            xlabel('time')
            ylabel('px [m]')
        end
        
        function f = plot_py(obj)
            hold on
            plot(obj.xTrue(2,:))
            plot(obj.xEst(2,:),'r-')
%             legend('true py', 'estimated py')
            title('p_y')
            xlabel('time')
            ylabel('py [m]')
        end
        
        function f = plot_theta(obj)
            hold on
            plot(obj.xTrue(3,:))
            plot(obj.xEst(3,:),'r-')
%             legend('true theta', 'estimated theta')
            title('\theta')
            xlabel('time')
            ylabel('\theta [m]')
        end
        
        function f = plot_vx(obj)
            hold on
            plot(obj.xTrue(4,:))
            plot(obj.xEst(4,:),'r-')
%             legend('true vx', 'estimated vx')
            title('v_x')
            xlabel('time')
            ylabel('vx [m]')
        end
        
        function f = plot_vy(obj)
            hold on
            plot(obj.xTrue(5,:),'r-')
            plot(obj.xEst(5,:))
%             legend('true vy', 'estimated vy')
            title('v_y')
            xlabel('time')
            ylabel('vy [m]')
        end
        
        function f = plot_omega(obj)
            hold on
            plot(obj.xTrue(6,:))
            plot(obj.xEst(6,:),'r-')
%             legend('true omega', 'estimated omega')
            title('\omega')
            xlabel('time')
            ylabel('\omega [m]')
        end
        
        function f = plot_trajectory(obj)
            hold on
            plot(obj.xTrue(1,:), obj.xTrue(2,:))
            plot(obj.xEst(1,:), obj.xEst(2,:),'r-')
%             legend('true trajectory', 'trajectory with ekf')
        end
        
    end
    properties
        % states
        xTrue
        xEst
        
        % variances
        var_px
        
        % errors
        error_px
        error_py
        error_theta
        error_vx
        error_vy
        error_omega
    end
end