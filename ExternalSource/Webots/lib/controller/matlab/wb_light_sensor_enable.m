function wb_light_sensor_enable(tag, sampling_period)
% Usage: wb_light_sensor_enable(tag, sampling_period)
% Matlab API for Webots
% Online documentation is available <a href="https://www.cyberbotics.com/doc/reference/lightsensor">here</a>

calllib('libController', 'wb_light_sensor_enable', tag, sampling_period);
