% This code was generated using ADiGator version 1.4
% ©2010-2014 Matthew J. Weinstein and Anil V. Rao
% ADiGator may be obtained at https://sourceforge.net/projects/adigator/ 
% Contact: mweinstein@ufl.edu
% Bugs/suggestions may be reported to the sourceforge forums
%                    DISCLAIMER
% ADiGator is a general-purpose software distributed under the GNU General
% Public License version 3.0. While the software is distributed with the
% hope that it will be useful, both the software and generated code are
% provided 'AS IS' with NO WARRANTIES OF ANY KIND and no merchantability
% or fitness for any purpose or application.

function y = myderiv(x)
global ADiGator_myderiv
if isempty(ADiGator_myderiv); ADiGator_LoadData(); end
Gator1Data = ADiGator_myderiv.myderiv.Gator1Data;
% ADiGator Start Derivative Computations
%User Line: %     N=10;
%User Line: %     u = 1:(N-1)/99:N; %linspace(1,N,100);
%User Line: %     v = 1:(2*N-1)/99:2*N; %linspace(1,2*N,100)
%User Line: %         x1 = x;
%User Line: %         x2 = 2*x;
%User Line: %     t = 3;
%User Line: %     for i=1:N
%User Line: %         x1 = stateTransition(t,x1);
%User Line: %     end
%User Line: %     for i=1:N
%User Line: %         x2 = stateTransition(t,x2);
%User Line: %     end
%User Line: %         y = 0.5*(x1+2*x2);
a.dx = x.dx; a.f = x.f;
%User Line: a = x;
b.dx = x.dx; b.f = x.f;
%User Line: b = x;
N.f = 10;
%User Line: N=10;
cadaforvar1.f = 1:N.f;
%User Line: cadaforvar1 = 1:N;
for cadaforcount1 = 1:10
    i.f = cadaforvar1.f(:,cadaforcount1);
    %User Line: i = cadaforvar1(:,cadaforcount1);
    cadainput2_1.dx = a.dx;     cadainput2_1.f = a.f;
    %User Line: cadainput2_1 = a;
    cadaoutput2_1 = ADiGator_G(cadainput2_1);
    % Call to function: G
    cada1f2dx = 3.*cadaoutput2_1.dx;
    cada1f2 = 3*cadaoutput2_1.f;
    a.dx = cada1f2dx;
    a.f = cada1f2 + 1;
    cada1tempdx = a.dx;
    a.dx = zeros(2,1);
    a.dx(1,1) = cada1tempdx;
    %User Line: a = 3*cadaoutput2_1+1;
    cadainput2_1.dx = b.dx;     cadainput2_1.f = b.f;
    %User Line: cadainput2_1 = b;
    cadaoutput2_1 = ADiGator_G(cadainput2_1);
    % Call to function: G
    cada1f2dx = 5.*cadaoutput2_1.dx;
    cada1f2 = 5*cadaoutput2_1.f;
    b.dx = cada1f2dx;
    b.f = cada1f2 + 2;
    cada1tempdx = b.dx;
    b.dx = zeros(2,1);
    b.dx(1,1) = cada1tempdx;
    %User Line: b = 5*cadaoutput2_1+2;
end
a.dx = a.dx(1,1);
b.dx = b.dx(1,1);
cada1f1dx = b.dx./2;
cada1f1 = b.f/2;
cada1td1 = a.dx;
cada1td1 = cada1td1 + cada1f1dx;
y.dx = cada1td1;
y.f = a.f + cada1f1;
%User Line: y=a+b/2;
y.dx_size = [2,2];
y.dx_location = Gator1Data.Index1;
end
function y = ADiGator_G(x)
global ADiGator_myderiv
Gator1Data = ADiGator_myderiv.ADiGator_G.Gator1Data;
% ADiGator Start Derivative Computations
t.f = 3;
%User Line: t=3;
cada1f1dx = x.dx(Gator1Data.Index1);
cada1f1 = x.f(1);
cada1f2dx = cada1f1dx;
cada1f2 = cada1f1 + t.f;
cada1f3 = ppval(Gator1Data.Data1,t.f);
cada1td1 = zeros(1,1);
cada1td1(1) = cada1f2dx;
y.dx = cada1td1;
y.f = [cada1f2;cada1f3];
%User Line: y = [x(1) + t;        interp1([1,2,3,4],[10,20,30,40],t)];
end


function ADiGator_LoadData()
global ADiGator_myderiv
ADiGator_myderiv = load('myderiv.mat');
return
end