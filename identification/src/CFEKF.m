s0 = [0;0;0;1;1;1];
obj = extendedKalmanFilter(@myStateTransitionFcn, @myMeasurementFcn, s0, 'HasAdditiveProcessNoise', false, 'HasAdditiveMeasurementNoise',false);

obj.MeasurementNoise = 0.01;
obj.ProcessNoise = 0.01;

% 1 second simulation

y=[linspace(0,1,101);linspace(0,1,101);ones(1,101)]+0.01*rand(3,101);
%y = rand(3,10); % some random measurments

for k = 1:size(y,2)
    predict(obj);
    correct(obj,y(:,k+1));
end
