function result = wb_robot_get_synchronization()
% Usage: wb_robot_get_synchronization()
% Matlab API for Webots
% Online documentation is available <a href="https://www.cyberbotics.com/doc/reference/robot">here</a>

result = calllib('libController', 'wb_robot_get_synchronization');
