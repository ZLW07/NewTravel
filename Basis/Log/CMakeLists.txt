set(MODULE_SOURCE_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

set(Log_DIR ${MODULE_SOURCE_ROOT})
build_library(Log)

set(UT_Log_DIR ${MODULE_SOURCE_ROOT}/Test)
build_execute(UT_Log Log)