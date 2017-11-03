%function findMapping(varargin)
% arguments : folder path were identification data for the propellers are

%define manually because it is easyer
nargin=2;
varargin{1}='~/bagfiles/bagPropeller1';
varargin{2}='~/bagfiles/bagPropeller4';

for idx = 1:nargin % outermost loop, loops for each propeller (bag folders)
% %filepath={filepath1,filepath2,filepath3,filepath4,filepath5,filepath6,filepath

%% afficher l'entrée et la sortie
dirName = varargin{idx};
%dirName = '~/bagfiles/bagPropeller4'; %directory where you have the bag files
s = dir(dirName);
s = s(3:end); % remove the . and .. folders
for i = 1:length(s)
    file = [s(i).folder,'/',s(i).name];
    bag = rosbag(file);
    
    % u is the input (motor command->10%, 20%...100%) and y output (v_theta)
bag_u = select(bag,'Topic','/cmd_vel');
bag_y = select(bag,'Topic','/imu');
ts_u = timeseries(bag_u,'Linear.X');
ts_y = timeseries(bag_y,'AngularVelocity.X');

% convert from linux time to readable time
linux_start_time = ts_y.time(1);
ts_u.time=ts_u.time-linux_start_time; 
ts_y.time=ts_y.time-linux_start_time;


start_time_input = ts_u.time(1);
end_time_input = ts_u.time(end);
end_time_output = ts_y.time(end);

% append zeros to the left and the right of u

ts_u = append(timeseries([0,0]',[0,start_time_input]),ts_u,timeseries([0,0]',[end_time_input,end_time_output]));

u{i} = ts_u;
y{i} = ts_y;
end

%% transmform the timeseries into matrices for differentiating (by hand)
%{1}->10%, {2}->20%, {3}->30%, ...

omegaPer{1} = [y{1}.data';y{1}.time'];
omegaPer{2} = [y{3}.data';y{3}.time'];
omegaPer{3} = [y{4}.data';y{4}.time'];
omegaPer{4} = [y{5}.data';y{5}.time'];
omegaPer{5} = [y{6}.data';y{6}.time'];
omegaPer{6} = [y{7}.data';y{7}.time'];
omegaPer{7} = [y{8}.data';y{8}.time'];
omegaPer{8} = [y{9}.data';y{9}.time'];
omegaPer{9} = [y{10}.data';y{10}.time'];
omegaPer{10} = [y{2}.data';y{2}.time'];

%derivative
for i=1:10
    alphaPer{i} = diff(omegaPer{i}(1,:))./diff(omegaPer{i}(2,:));
end

% % filter() apply a filter with rationnal transfer function b(q⁻1)/a(q⁻1)
% N=40;
% b=1/N*ones(1,N);
% a=1;
% F=filter(b,a,f);

% sgolayfilt(), I think this one is closer to truth

% F is the filtered version of the angular acceleration
for i=1:10
    F{i} = sgolayfilt(alphaPer{i},2,71);
    maximum{idx}(i)=max(F{i});
end

figure(idx)
plot(maximum{idx})

%% interpolation
xq = 10; %acceleration of xq rad/s
sigToApply(idx) = interp1(maximum{idx},10:10:100,xq);

% % u is the input (motor command->10%, 20%...100%) and y output (v_theta)
% bag{1}=rosbag('~/bagfiles/specialBagAlic50.bag');
% bag_u{1} = select(bag{1},'Topic','/cmd_vel');
% bag_y{1} = select(bag{1},'Topic','/imu');
% ts_u{1} = timeseries(bag_u{1},'Linear.X');
% ts_y{1} = timeseries(bag_y{1},'AngularVelocity.X');
% 
% % convert from linux time to readable time
% linux_start_time = ts_y{1}.time(1);
% ts_u{1}.time=ts_u{1}.time-linux_start_time; 
% ts_y{1}.time=ts_y{1}.time-linux_start_time;
% 
% 
% start_time_input = ts_u{1}.time(1);
% end_time_input = ts_u{1}.time(end);
% end_time_output = ts_y{1}.time(end);
% 
% % append zeros to the left and the right of u
% 
% ts_u_corrected = append(timeseries([0,0]',[0,start_time_input]),ts_u{1},timeseries([0,0]',[end_time_input,end_time_output]));
% 
end
