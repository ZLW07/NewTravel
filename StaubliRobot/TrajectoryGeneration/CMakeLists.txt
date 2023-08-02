set(MODULE_SOURCE_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

set(TrajectoryGeneration_DIR ${CMAKE_CURRENT_SOURCE_DIR})
build_library(TrajectoryGeneration CollisionDetection)

set(UT_TrajectoryGeneration_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Test)
build_execute(UT_TrajectoryGeneration TrajectoryGeneration CollisionDetection PQP Log Kinematics Model  Math gtest )