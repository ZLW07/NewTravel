set(MODULE_SOURCE_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

set(CollisionDetection_DIR ${CMAKE_CURRENT_SOURCE_DIR})
build_library(CollisionDetection Model)

set(UT_CollisionDetection_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Test)
build_execute(UT_CollisionDetection CollisionDetection Model gtest)
