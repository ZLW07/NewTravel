function result = wb_supervisor_field_get_sf_node(fieldref)
% Usage: wb_supervisor_field_get_sf_node(fieldref)
% Matlab API for Webots
% Online documentation is available <a href="https://www.cyberbotics.com/doc/reference/supervisor">here</a>

result = calllib('libController', 'wb_supervisor_field_get_sf_node', fieldref);
