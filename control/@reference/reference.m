classdef reference
    methods
        function obj = reference()
            % dynamics is the hovercraft_model object describing dynamics
            % ref is the reference reference object that we should track
            % N is the horizon
            import casadi.*
            
            % create the reference function
            r = 2;
            t = MX.sym('t');
            rhs = [r * cos(0.5 * t)
                    r * sin(0.5 * t)];
%             rhs = [-2; 2]; % point tracking
            obj.ref = Function('ref', {t},{rhs});
        end
        function rt = discrete_ref(obj,t)
            rt = zeros(2, length(t));
            for i = 1:length(t)
                rt(:,i) = full(obj.ref(t(i)));
            end
        end
    end
    properties
        ref
    end
end