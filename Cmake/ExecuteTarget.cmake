
message(STATUS "Link path is = ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")

set(UT_Log_DIR Test/Log)
build_execute(UT_Log Log)

set(UT_Math_DIR Test/Math)
build_execute(UT_Math  Math Log gtest)

set(UT_Model_DIR Test/Model)
build_execute(UT_Model Model Math Log gtest)


set(my_robot_controller_DIR Test/Webots)
build_execute(my_robot_controller Controller CppController)

