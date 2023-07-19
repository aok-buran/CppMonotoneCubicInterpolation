% функция рисования графиков с опорными точками, легенда для 
% опорных точек добавляется последней
function f_my_plot(mx, my, bx, by, legendY,pathname,position,tit,mxlabel,mylabel)
f = figure('pos',[30 60 600 600]);  
hold on;
plot(mx,my,'LineWidth',2);

plot(bx,by,'o','MarkerSize',8, 'MarkerEdgeColor','red',...
    'MarkerFaceColor',[1 .6 .6]);...
    
hold off;
title(tit);
xlabel(mxlabel);
ylabel(mylabel);
legend_handle = legend(legendY,'Interpreter','latex','Location',position);
legend_handle.FontSize = 16;

set(legend_handle);
grid on;
saveas(f,pathname);

end

