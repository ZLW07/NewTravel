function wb_display_detach_camera(tag)
% Usage: wb_display_detach_camera(tag)
% Matlab API for Webots
% Online documentation is available <a href="https://www.cyberbotics.com/doc/reference/display">here</a>

calllib('libController', 'wb_display_detach_camera', tag);
