function result = wb_display_get_height(tag)
% Usage: wb_display_get_height(tag)
% Matlab API for Webots
% Online documentation is available <a href="https://www.cyberbotics.com/doc/reference/display">here</a>

result = calllib('libController', 'wb_display_get_height', tag);
