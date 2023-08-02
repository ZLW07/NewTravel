set(MODULE_SOURCE_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

set(Model_DIR ${MODULE_SOURCE_ROOT})
build_library(Model PQP Math)

set(UT_Model_DIR ${MODULE_SOURCE_ROOT}/Test)
build_execute(UT_Model Model Math Log PQP gtest)