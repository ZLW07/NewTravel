set(MODULE_SOURCE_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

set(Configure_DIR ${MODULE_SOURCE_ROOT})
build_library(Configure Log TinyXML)

set(UT_Configure_DIR ${MODULE_SOURCE_ROOT}/Test)
build_execute(UT_Configure  Configure Log TinyXML gtest)