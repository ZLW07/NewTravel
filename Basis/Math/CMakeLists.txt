set(MODULE_SOURCE_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

set(Math_DIR ${MODULE_SOURCE_ROOT})
build_library(Math Log)

set(UT_Math_DIR ${MODULE_SOURCE_ROOT}/Test)
build_execute(UT_Math Math Log  gtest)