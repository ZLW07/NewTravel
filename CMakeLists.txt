cmake_minimum_required(VERSION 3.16)
project(NewTravel)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/Package/lib)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/Package/bin)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Package/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Package/bin)

include_directories(include)
include_directories(ExternalSource/googletest/include)
include_directories(ExternalSource/googletest)
set(BUILD_SHARED_LIBS ON)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/Cmake)

function(build_library MODULE_NAME)
    message("")
    message("[LIBRARY] [${MODULE_NAME}]------------")
    message(STATUS "Build library ${MODULE_NAME} IN ${${MODULE_NAME}_DIR}")
    if (${ARGC} GREATER_EQUAL 2)
        message(STATUS "Depend on ")
        foreach (arg ${ARGN})
            message("--------------${arg}")
        endforeach (arg)
    endif ()

    include_directories(${${MODULE_NAME}_DIR}/include)
    file(GLOB_RECURSE MODULE_SRC ${${MODULE_NAME}_DIR}/*)
    foreach (file IN LISTS MODULE_SRC)
        message(STATUS "file is = ${file}")
    endforeach (file)
    add_library(${MODULE_NAME} SHARED ${MODULE_SRC})
endfunction()

function(build_execute MODULE_NAME)
    message("")
    message("[Execute] [${MODULE_NAME}]------------")
    message(STATUS "Build library ${MODULE_NAME} IN ${${MODULE_NAME}_DIR}")

    if (${ARGC} GREATER_EQUAL 2)
        message(STATUS "Depend on ")
        foreach (arg ${ARGN})
            message("--------------${arg}")
        endforeach (arg)
    endif ()

    include_directories(${${MODULE_NAME}_DIR}/include)
    file(GLOB_RECURSE MODULE_SRC ${${MODULE_NAME}_DIR}/*)
    foreach (file IN LISTS MODULE_SRC)
        message(STATUS "file is = ${file}")
    endforeach (file)
    add_executable(${MODULE_NAME}  ${MODULE_SRC})
    target_link_libraries(${MODULE_NAME} ${ARGN})
endfunction(build_execute)

include(LibraryTarget)
include(ExecuteTarget)
add_subdirectory(ExternalSource/googletest )

