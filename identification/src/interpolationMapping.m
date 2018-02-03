% Run this script after you have the imported the run bags in matlab
load(fname);
fname = getFromDataFolder('pair1');
% arguments can be 'pair1' ,'pair2', 'propeller1', 'propeller2',
% 'propeller3' or 'propeller4'.

perc = pair; % remove this line if you don't do paired identification

dt=0.01;

for i=1:length(perc)
    time{i}=0:dt:perc(i).time(end);
    perc(i) = resample(perc(i),time{i});
end

for p=1:10

% figure(1)
% plot(perc(p).time,perc(p).data)
% title('propeller1, 50%')
% xlabel('time')
% ylabel('angular velocity (of hovercraft)')

figure
plot(perc(p).time,filter(-smooth_diff(20)/dt,1,perc(p).data))
hold on
plot(perc(p).time(1:end-1),diff(perc(p).data)/dt)
title('propeller1, 50%')
xlabel('time')
ylabel('angular acceleration (of hovercraft)')
legend('with smoothing', 'no smoothing')
end

shg
hold off
% Gather manually what seems to be the maximal acceleration

acc1 = [0.62, 3.2, 6, 10, 14.1, 19, 23.4, 25.8, 27.5, 30];
acc2 = [-0.68, -4.448, -8.78, -12.19, -16.69, -20.29, -25.13, -27.8, -32.2, -32.21];
acc3 = [1.482, 5.601, 9.237, 13.46, 17.27, 23.00, 26.27, 31.16, 33.45, 35.26];
acc4 = [-1.013, -3.3, -7, -10.15, -16, -20, -23.6, -27.4, -31, -35];

% 
% xi1 = 5;
% xi4 = -5;
% yi1 = interp1(acc1,1:10,xi1);
% yi4 = interp1(acc4,1:10,xi4);
% 
% xi2 = -7;
% xi3 = 7;
% yi2 = interp1(acc2,1:10,xi2);
% yi3 = interp1(acc3,1:10,xi3);