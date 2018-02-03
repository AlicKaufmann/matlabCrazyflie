function simulationHC(t, s)
    
    r = 1; % radius of the circle
    phi = 0:pi/50:2*pi; % angle for plotting the circle
    figure(1)
    axis([-5,5,-5,5])
    pbaspect([1,1,1]);
%     plot(s(:,1),s(:,2));
    hold on
    grid on
    ax = gradient(s(:,4), t);
    ay = gradient(s(:,5), t);
    
    for k = 1:size(s,1)-1
        px = s(k,1);
        py = s(k,2);
        theta = s(k,3);
        
        xc = px + r * cos(phi);
        yc = py + r * sin(phi);
        circle = plot(xc,yc,'k');
        bar = plot([px - r * cos(theta), px + r * cos(theta)], [py - r * sin(theta), py + r * sin(theta)], 'b');
        velocity = quiver(px, py, ax(k), ay(k));
        pause(t(k+1)-t(k));
        delete(circle);
        delete(bar);
        delete(velocity);
    end
end