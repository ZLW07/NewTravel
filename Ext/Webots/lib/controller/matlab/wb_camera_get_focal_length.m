function result = wb_camera_get_focal_length(tag)
% Usage: wb_camera_get_focal_length(tag)
% Matlab API for Webots
% Online documentation is available <a href="https://www.cyberbotics.com/doc/reference/camera">here</a>

result = calllib('libController', 'wb_camera_get_focal_length', tag);
