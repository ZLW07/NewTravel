function result = wb_camera_get_near(tag)
% Usage: wb_camera_get_near(tag)
% Matlab API for Webots
% Online documentation is available <a href="https://www.cyberbotics.com/doc/reference/camera">here</a>

result = calllib('libController', 'wb_camera_get_near', tag);
