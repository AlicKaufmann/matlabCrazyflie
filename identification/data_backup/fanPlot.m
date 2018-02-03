% function fanPlot(fname)
% load(fname)
h=figure;
hold on
for i = 1:length(perc)
%     plot(delsample(perc(i),'Index',1:34));
    plot(perc(i));
    Legend{i} = strcat('perc',num2str(i),'0');
end
legend(Legend);
shg
% end;