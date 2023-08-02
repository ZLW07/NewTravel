set(MODULE_SOURCE_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

set(Kinematics_DIR ${MODULE_SOURCE_ROOT})
build_library(Kinematics)

set(UT_Kinematics_DIR ${MODULE_SOURCE_ROOT}/Test)
build_execute(UT_Kinematics  Kinematics Log gtest)