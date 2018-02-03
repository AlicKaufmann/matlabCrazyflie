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

function s = F_ADiGatorJac(x)
global ADiGator_F_ADiGatorJac
if isempty(ADiGator_F_ADiGatorJac); ADiGator_LoadData(); end
Gator1Data = ADiGator_F_ADiGatorJac.F_ADiGatorJac.Gator1Data;
% ADiGator Start Derivative Computations
Ts.f =  0.01;
%User Line: Ts = 0.01;
K.f =  100;
%User Line: K = 100;
cada1f1 = Ts.f/K.f;
cada1f2 = 1/K.f;
cada1f3 = 1 - cada1f2;
cada1f4 = Ts.f*cada1f3;
t.f = 0:cada1f1:cada1f4;
%User Line: t = 0:Ts/K:Ts*(1-1/K);
s.f = zeros(K.f,6);
%User Line: s = zeros(K,6);
cadaforvar1.f =  1:99;
%User Line: cadaforvar1 = 1:99;
for cadaforcount1 = 1:99
    k.f = cadaforvar1.f(:,cadaforcount1);
    %User Line: k = cadaforvar1(:,cadaforcount1);
    tk.f = t.f(k.f);
    %User Line: tk = t(k);
    sk.f = s.f(k.f,:);
    %User Line: sk = s(k,:);
    cada1f1 = k.f + 1;
    cada1f2 = t.f(cada1f1);
    cada1f3 = t.f(k.f);
    dt.f = cada1f2 - cada1f3;
    %User Line: dt = t(k+1)-t(k);
    cadainput2_1.f = tk.f;
    %User Line: cadainput2_1 = tk;
    cadainput2_2.f = sk.f.';
    %User Line: cadainput2_2 = sk';
    cadaoutput2_1 = ADiGator_stateTransition(cadainput2_1,cadainput2_2);
    % Call to function: stateTransition
    k1.f = cadaoutput2_1.f;
    %User Line: k1 = cadaoutput2_1;
    cada1f1 = dt.f/2;
    cadainput2_1.f = tk.f + cada1f1;
    %User Line: cadainput2_1 = tk+dt/2;
    cada1f1 = sk.f.';
    cada1f3 = k1.f*dt.f;
    cada1f4 = cada1f3/2;
    cadainput2_2.f = cada1f1 + cada1f4;
    %User Line: cadainput2_2 = sk'+k1*dt/2;
    cadaoutput2_1 = ADiGator_stateTransition(cadainput2_1,cadainput2_2);
    % Call to function: stateTransition
    k2.f = cadaoutput2_1.f;
    %User Line: k2 = cadaoutput2_1;
    cada1f1 = dt.f/2;
    cadainput2_1.f = tk.f + cada1f1;
    %User Line: cadainput2_1 = tk+dt/2;
    cada1f1 = sk.f.';
    cada1f3 = k2.f*dt.f;
    cada1f4 = cada1f3/2;
    cadainput2_2.f = cada1f1 + cada1f4;
    %User Line: cadainput2_2 = sk'+k2*dt/2;
    cadaoutput2_1 = ADiGator_stateTransition(cadainput2_1,cadainput2_2);
    % Call to function: stateTransition
    k3.f = cadaoutput2_1.f;
    %User Line: k3 = cadaoutput2_1;
    cadainput2_1.f = tk.f + dt.f;
    %User Line: cadainput2_1 = tk+dt;
    cada1f1 = sk.f.';
    cada1f3 = k3.f*dt.f;
    cadainput2_2.f = cada1f1 + cada1f3;
    %User Line: cadainput2_2 = sk'+k3*dt;
    cadaoutput2_1 = ADiGator_stateTransition(cadainput2_1,cadainput2_2);
    % Call to function: stateTransition
    k4.f = cadaoutput2_1.f;
    %User Line: k4 = cadaoutput2_1;
    cada1f1 = sk.f.';
    cada1f3 = 0.1666666666666667*k1.f;
    cada1f5 = 0.3333333333333333*k2.f;
    cada1f6 = cada1f3 + cada1f5;
    cada1f8 = 0.3333333333333333*k3.f;
    cada1f9 = cada1f6 + cada1f8;
    cada1f11 = 0.1666666666666667*k4.f;
    cada1f12 = cada1f9 + cada1f11;
    cada1f14 = dt.f*cada1f12;
    cada1f15 = cada1f1 + cada1f14;
    cada1f16 = cada1f15.';
    cada1f17 = k.f + 1;
    s.f(cada1f17,:) = cada1f16;
    %User Line: s(k+1,:) = (sk' + dt * (1/6 * k1 + 1/3 * k2 + 1/3 * k3 + 1/6* k4))';
end
end
function ds = ADiGator_stateTransition(t,s)
global ADiGator_F_ADiGatorJac
Gator1Data = ADiGator_F_ADiGatorJac.ADiGator_stateTransition.Gator1Data;
% ADiGator Start Derivative Computations
%User Line: % actually there needs to be 2 u : one fore the translation uT and one for
%User Line: % the rotation uR.
%User Line: % hardcode some stuff
%User Line: %ds = zeros(6,1);
uTrans.f =  ones(10,1)';
%User Line: uTrans = ones(10,1)';
uTransTime.f =  0:9';
%User Line: uTransTime = 0:9';
uRot.f =  ones(10,1)';
%User Line: uRot = ones(10,1)';
uRotTime.f =  0:9';
%User Line: uRotTime = 0:9';
uTrans.f = ppval(Gator1Data.Data1,t.f);
%User Line: uTrans = interp1(uTransTime, uTrans, t);
uRot.f = ppval(Gator1Data.Data2,t.f);
%User Line: uRot = interp1(uRotTime, uRot, t);
cada1f1 = s.f(4);
cada1f2 = s.f(5);
cada1f3 = s.f(6);
cada1f4 = ppval(Gator1Data.Data3,uTrans.f);
cada1f5 = s.f(3);
cada1f6 = cos(cada1f5);
cada1f8 = cada1f4*cada1f6;
cada1f9 = ppval(Gator1Data.Data4,uTrans.f);
cada1f10 = s.f(3);
cada1f11 = sin(cada1f10);
cada1f13 = cada1f9*cada1f11;
cada1f14 = ppval(Gator1Data.Data5,uRot.f);
ds.f = [cada1f1;cada1f2;cada1f3;cada1f8;cada1f13;cada1f14];
%User Line: ds = [s(4);        s(5);        s(6);        interp1([0,2,3,5,6,7,8,9,10]', [0,0.2244,0.3850,0.6309,0.7839,1.022,1.1630,1.3959,1.5340]', uTrans) * cos(s(3));        interp1([0,2,3,5,6,7,8,9,10]', [0,0.2244,0.3850,0.6309,0.7839,1.022,1.1630,1.3959,1.5340]', uTrans) * sin(s(3));        interp1((0:10:100)', [0, 6.3632, 16.8374, 25.6822, 35.5810, 45.7588, 53.0103, 60.5996, 83.5957, 89.0708, 96.1055]',uRot)];
end


function ADiGator_LoadData()
global ADiGator_F_ADiGatorJac
ADiGator_F_ADiGatorJac = load('F_ADiGatorJac.mat');
return
end