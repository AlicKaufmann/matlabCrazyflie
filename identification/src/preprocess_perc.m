function dat = preprocess_perc(fname,Ts,varargin)
%
% Remove initial delay, resample to a regular period 
% and select the first second of the step response
%
% number of time intervals we keep

fname = getFromDataFolder(fname);

%% Load the data
load(fname);
% eval(sprintf('perc(%i) = perc%i;\n', [1:10;10:10:100]));

% Resample the signal at a regular period of 0.01 seconds

Fs = 1/Ts;
time = 0:Ts:5-Ts;
for i = 1:length(perc)
  perc(i) = resample(perc(i),time);
end

if nargin > 2
    nt = varargin{1};
else
    nt = length(time);
end

%% Fit a line to the response

% Grab the first second of data, as this is quite linear.
t = 0:Ts:100; t = t(1:100);

% Estimate the start of the step response. Delete any zero values at the
% start of the response (tolerance of 0.5 %)
for i = 1:length(perc)
  tmp = perc(i).Data;
  for j = 1:length(tmp)
    if abs(tmp(j)) > max(abs(tmp)) * 0.005
      ind(i) = j;
      break
    end
  end

  % Take the first 1 second, which is very linear
  dat(:,i) = tmp(ind(i)+[0:nt]); 
end
% % Least-squares to fit a linear model
% % Fit the step response to a line
% lin = [t' ones(length(t),1)] \ dat;
% 
% % Least-squares fit 
% 
% fit.acc = lin(1,:)';
% fit.offset = lin(2,:)'; % This should be very close to zero
% fit.error = [t' ones(length(t),1)]*lin - dat;
% fit.error = sum(fit.error .* fit.error); % Squared error
% fit.dat = dat;
% fit.t = t;
% 
