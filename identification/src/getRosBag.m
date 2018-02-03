%function getRosBags(varargin)
% This file retreives the rosbag the were saved with the rosbag function of
% ROS.
% If you selct paired = true, it saves the rosbag from the rotation of both
% opposite propellers in the data/pair1.m and the data/pair2.m files
% note that the bagfiles has to be saved in ~/bagiles/bagPair1 and
% ~/bagiles/bagPair2.
% If paired = false the identification will be for just one propeller that
% you have to choose by selecting the varargin and the right lookup indexes.

% arguments : folder path were identification data for the propellers are

%define manually because it is easyer
paired = true; % if true, we want to import the bags for paired propellers

nargin=2;
% varargin{1}='~/bagfiles/bagPropeller1';
% varargin{2}='~/bagfiles/bagPropeller2';
% varargin{3}='~/bagfiles/bagPropeller3';
% varargin{4}='~/bagfiles/bagPropeller4';
varargin{1}='~/bagfiles/bagPair1';
varargin{2}='~/bagfiles/bagPair2';


% conversion between idx and the right propeller number
lookup(1)=1;
lookup(2)=2;
lookup(3)=3;
lookup(4)=4;

current_folder = pwd;

for idx = 1:nargin % outermost loop, loops for each propeller (bag folders)
    % %filepath={filepath1,filepath2,filepath3,filepath4,filepath5,filepath6,filepath
    
    %% afficher l'entrée et la sortie
    dirName = varargin{idx};
    s = dir(dirName);
    
    % remove the . and .. folders and do some swappings
    s = s(3:end);
    s = [s(1);s(3:end);s(2)];
    
    for i = 1:length(s)
        fileName = s(i).name;
        file = [s(i).folder,'/',fileName];
        bag = rosbag(file);
        
        % u is the input (motor command->10%, 20%...100%) and y output (v_theta)
        bag_u = select(bag,'Topic','/cmd_vel');
        bag_y = select(bag,'Topic','/imu');
        switch lookup(idx)
            case 1
                ts_u = timeseries(bag_u,'Linear.Y');
            case 2
                ts_u = timeseries(bag_u,'Linear.X');
            case 3
                ts_u = timeseries(bag_u,'Angular.Y');
            case 4 
                ts_u = timeseries(bag_u,'Angular.X');
            otherwise
                disp('there is a problem with the switch-case')
        end
        ts_y = timeseries(bag_y,'AngularVelocity.X');
        
        % convert from linux time to readable time
        respStt = ts_u.time(1);
        ts_y = delsample(ts_y,'Index', 1:sum(ts_y.time<ts_u.time(1)));
        linux_start_time = ts_y.time(1);
        ts_y.time=ts_y.time-linux_start_time;
        if paired == true
            pair(i) = ts_y;
        else
            perc(i) = ts_y;
        end
    end        
        if paired == true
            destPath = sprintf(strcat(current_folder,'/../data/pair%i'),lookup(idx));
            eval(sprintf('save(destPath,''pair'')',lookup(idx)));
        else
            destPath = sprintf(strcat(current_folder,'/../data/propeller%i'),lookup(idx));
            eval(sprintf('save(destPath,''perc'')',lookup(idx)));
        end
end