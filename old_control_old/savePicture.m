function savePicture( fileName )
	
	%set( gca, 'XTick', -10:2:10 );
	%set( gca, 'YTick', -10:2:10 );
	%set(gcf,'PaperPositionMode','auto');
	%print( '-r300', '-dpng', fileName ); 	
	
	% svojstva za propeler_intersection (locateTheta2__all__fixed)
% 	set( gca, 'Units', 'centimeters' );
% 	%set( gca, 'Position', [0 0 12 10] );
% 	get( gca, 'Position' )
	set(gcf, 'PaperPositionMode', 'manual');
	set( gcf, 'PaperUnits', 'centimeters' );
	% set( gcf, 'PaperSize', [12 10] );
	% set(gcf, 'PaperPosition', [0 0 12 10]);
	set( gcf, 'PaperSize', [12 10] );
	set(gcf, 'PaperPosition', [0 0 12 10]);
	set( gca, 'FontSize', 6 );
	print( '-r600', '-dpdf', fileName ); 	
end
