
f = figure(1);
hold on
myLegend={};


%% section

file='pair1perc10.bag';
bag=rosbag(['~/bagfiles/bagPair1/',file]);
bag=select(bag,'Topic','/imu');
ts=timeseries(bag,'AngularVelocity.X');
ts.time=ts.time-ts.time(1);

h1 = plot(ts,'o');
myLegend{end+1}=file;

legend(myLegend)
shg

%% compute slope
slope = [];

delta = cursor_info(1).Position-cursor_info(2).Position;
slope = [slope, delta(2)/delta(1)];


