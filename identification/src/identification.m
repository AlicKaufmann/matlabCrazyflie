% In this matlab script :
% u is the input and represents porcentage of speed of the hovercraft blades 0%-100%
% dt is the discretisation time

try
    rosshutdown
catch
end
%% setting environment variables
clear all

setenv('ROS_MASTER_URI','http://localhost:11311/')
% setenv('ROS_IP','128.179.137.102')
setenv('ROS_HOSTNAME','localhost')

rosinit('localhost')

speedTopic = rospublisher('/cmd_vel');
msg = rosmessage(speedTopic);

imu = rossubscriber('/imu');

dataImu=receive(imu);

%% General identification variables



%% identification blade velocity - angular velocity
%{
dt = 0.2;
u_v=[];
vTheta_v=[];
h = zeros(1,100);
for i=1:100
    t = tic;
    u = rand(1)*100; % random input
    u_v=[u_v,u];
    msg.Linear.Y = u;
    send(speedTopic,msg);
    dataImu = receive(imu);
    vTheta = dataImu.AngularVelocity.X;
    vTheta_v=[vTheta_v,vTheta];

    z= toc(t);
    if h(i)<dt
    pause(dt-z);
    end
    h(i) = toc(t);
end

dataForId = iddata(vTheta_v',u_v',dt);
plot(dataForId)

M = oe(dataForId,[4,4,1]);

 compare(M,dataForId);

%% identification blade speed - linear acceleration
save('ctrl.mat','C');
%}

%% step input for linear acceleration
stepResponse=[];
u = 100;
msg.Linear.Y = u;
msg.Angular.X = u;
send(speedTopic,msg);
loopTime = 0.2;
while(1)
    tic
    dataImu = receive(imu); % polling the IMU data
    stepResponse=[stepResponse,dataImu.LinearAcceleration.Z];
    pause(loopTime-toc);
end


%% Identification blade speed - linear acceleration
dt_LinAccel=0.2;
LinAccel_v=[];
u_v=[];
for i=1:15
    tic
    u=rand(1)*15;
    u_v=[u_v,u];
    msg.Linear.Y = u;
    msg.Angular.X = u;
    send(speedTopic,msg);
    dataImu = receive(imu);
    LinAccel = dataImu.LinearAcceleration.Z; % forward acceleration is in Z since howercraft is upsidown
    LinAccel_v = [LinAccel_v,LinAccel];
    pause(dt_LinAccel-toc);
end

dataForId = iddata(LinAccel_v',u_v',dt_LinAccel);
plot(dataForId);
M = oe(dataForId,[4,4,1]);


%% control

load('ctrl.mat')

vThetaRef = 5; % rad/s? reference for angular velocity

%initialisations
dataImu = receive(imu);
vThetaPrev = 0;
int = 0;
ePrev = 0 - vThetaRef;
E=[]; % vector of errors
input=[];
speedTheta=[];
uPrev=0;

%control loop
dt=0.2; % 200ms to execute following loop (calculated via tic toc)
Kp = 18; % proportionnal gain
Ki = 6; % integral gain
Kd = 0;

%K = pid(Kp,Ki,Kd,4*dt,dt);
C = controller(C);
N=100;
h=zeros(1,N);
E = zeros(1,N);
vTheta_vecor=zeros(1,N);

for i=1:N
    t = tic;
    dataImu = receive(imu);
    vTheta = dataImu.AngularVelocity.X;
    
    e = vTheta - vThetaRef; 
    E(i) = e;
    
%     der = (e-ePrev)/dt;
%     int = int + e*dt;
    u=50;
    msg.Linear.Y=u;
    msg.Angular.Y=u;
%     msg.Linear.Y= -C.sample(e);
%     vTheta_vector(i)=vTheta;
%     u = uPrev +3.534*e-3.198*ePrev; % tuned using pidTuner()
%     msg.Linear.Y = -u; % not sure why I have to put a negative sign
%     ---these PID where designed using Zigler-Nicols---
%     msg.Linear.Y = vThetaPrev - Kp*e; % P controller
%     msg.Linear.Y = vThetaPrev-Ki*int; % I controller
%     msg.Linear.Y = vThetaPrev-Kp*e + vThetaPrev-Ki*int; % PI controller
%     msg.Linear.Y = vThetaPrev - Kp*e - Kd*der; % PD controller
%     msg.Linear.Y = vThetaPrev -Kp*e - Ki*int - Kd*der; %PID controller
    send(speedTopic,msg);
    input = [input,msg.Linear.Y];
    speedTheta=[speedTheta,vTheta];
    vThetaPrev = vTheta;
    ePrev = e;
    uPrev = u;
    
    %z= toc(t);
    %if h(i)<dt
    %pause(dt-z);
    %end
    h(i) = toc(t);
    
end

% msg.Linear.Y = 20;
% 
% f=[];
% tic
% while toc<5
%     send(speedTopic,msg);
%     data = receive(imu);
%     f=[f,data.AngularVelocity.X];
% end

rosshutdown