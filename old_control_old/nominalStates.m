%function s = nominalStates(x,y)
% takes the x-y  size 1xK componant of a trajectory as imput and returns a
% nominal trajectory for the states s=[x,y,theta,vx,vy,omega]
clear all


T = 2*pi; % simmulation endtime
K = 100; % number of time points
dt = T/(K-1); % timestep length

% circle
t = linspace(0,T,K);

r = 2;
px = r * cos(t .^ 2);
py = r * sin(t .^ 2);
%plot(x,y)

% forward differentiation
vx = gradient(px, t);
vy = gradient(py, t);


ax = gradient(vx, t);

ay = gradient(vy, t); % in order to have same length

theta = [];
for i = 1:length(ax)
   theta(i) = atan2(ay(i), ax(i)) + pi/2;
end
omega = gradient(theta, t);

s=[px;py;theta;vx;vy;omega]; % state vector
%end