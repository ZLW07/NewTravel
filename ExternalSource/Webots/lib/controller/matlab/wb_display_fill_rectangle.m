function wb_display_fill_rectangle(tag, x, y, width, height)
% Usage: wb_display_fill_rectangle(tag, x, y, width, height)
% Matlab API for Webots
% Online documentation is available <a href="https://www.cyberbotics.com/doc/reference/display">here</a>

calllib('libController', 'wb_display_fill_rectangle', tag, x, y, width, height);
