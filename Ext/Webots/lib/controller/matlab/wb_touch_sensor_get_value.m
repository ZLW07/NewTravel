function result = wb_touch_sensor_get_value(tag)
% Usage: wb_touch_sensor_get_value(tag)
% Matlab API for Webots
% Online documentation is available <a href="https://www.cyberbotics.com/doc/reference/touchsensor">here</a>

result = calllib('libController', 'wb_touch_sensor_get_value', tag);
