%clear

Ts = 0.01;
nt = 99; % number of time intervals


QUADFIT = false; % True to fit a quadratic in thrust, false = linear

for prop = 1:4
  eval(sprintf('dat{prop} = preprocess_perc(''propeller%i.mat'',Ts,nt);', prop));
end



thrust_percentage = 10:10:100;
t = Ts*(1:nt+1);
t = t';

%% Fit a model that's linear in time and quadratic in thrust

for prop = 1:4
  d = dat{prop};
  th = repmat(thrust_percentage, size(d,1), 1);
  tt = repmat(t, 1, size(d,2));
  
  if QUADFIT
    g = fittype({'t','t*th', 't*th^2', '1'}, 'indep', {'t', 'th'});
  else
    g = fittype({'t','t*th', '1'}, 'indep', {'t', 'th'});
  end
  
  [f0, G] = fit([tt(:) th(:)], d(:), g); % Linear in time, quadratic in thrust
  
  figure(prop); clf;
  plot(f0, [tt(:) th(:)], d(:));
  xlabel('Time (sec)')
  ylabel('Thrust (%)');
  zlabel('Rotational speed');
  title(sprintf('Propeller %i', prop));
  
  model(prop).fit = f0;
  model(prop).vel = d;
  model(prop).thrust = th;
  model(prop).time = tt;
  
  % Compute map to acceleration
  % Since the model is linear in time, the acceleration is just the
  % derivative of the model (the coefficient multiplying time)
  
  if QUADFIT
    model(prop).acc_coef = [f0.a f0.b f0.c];
    model(prop).acc = @(th) f0.a  + f0.b * th + f0.c * th.^2;
  else
    model(prop).acc_coef = [f0.a f0.b];
    model(prop).acc = @(th) f0.a  + f0.b * th;
    model(prop).accinv = @(alpha) (alpha-f0.a)/f0.b;
  end
end

%% Plot the resulting thrust-acceleration curve

figure(5)
clf
th = 1:100;
for prop = 1:4
  h=plot(th, model(prop).acc(th), 'linewidth', 2);
  grid on; hold on;
  plot(thrust_percentage, diff(dat{prop})/Ts, '.', 'color', h.Color)
  q=plot(thrust_percentage, mean(diff(dat{prop})/Ts), 'o', 'color', h.Color, 'MarkerFaceColor', 'w', 'markersize', 8);
end
xlabel('Thrust (%)');
ylabel('Acceleration');
