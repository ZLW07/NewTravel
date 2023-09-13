set(MODULE_SOURCE_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

set(StaubilRobotKinematics_DIR ${CMAKE_CURRENT_SOURCE_DIR})
build_library(StaubilRobotKinematics Kinematics)

set(UT_StaubilRobotKinematics_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Test)
build_execute(UT_StaubilRobotKinematics StaubilRobotKinematics  Kinematics Log gtest)