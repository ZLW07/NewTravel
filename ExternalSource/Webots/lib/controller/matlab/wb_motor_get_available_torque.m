function result = wb_motor_get_available_torque(tag)
% Usage: wb_motor_get_available_torque(tag)
% Matlab API for Webots
% Online documentation is available <a href="https://www.cyberbotics.com/doc/reference/motor">here</a>

result = calllib('libController', 'wb_motor_get_available_torque', tag);
