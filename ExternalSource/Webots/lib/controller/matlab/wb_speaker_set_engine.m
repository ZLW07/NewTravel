function result = wb_speaker_set_engine(tag, language)
% Usage: wb_speaker_set_engine(tag, language)
% Matlab API for Webots
% Online documentation is available <a href="https://www.cyberbotics.com/doc/reference/speaker">here</a>

result = calllib('libController', 'wb_speaker_set_engine', tag, language);
