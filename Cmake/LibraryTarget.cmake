
#the first way to add library

#set(Cout_DIR ${CMAKE_SOURCE_DIR}/Cout)
#message(STATUS "Source path is = ${Cout_DIR}")
#add_library(Cout SHARED ${Cout_DIR}/Cout_Test.cpp)

#the second way to add library
#add_library(Cout SHARED ${MODULE_SRC})

#the third way to add library which use the function user defined
#set(Cout_DIR Cout)
#build_library(Cout Cin)
#
#set(Cin_DIR Cin)
#build_library(Cin)

set(Log_DIR Log)
build_library(Log)

set(Mutex_DIR Mutex)
build_library(Mutex)