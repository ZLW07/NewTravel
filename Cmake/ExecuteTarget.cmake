
message(STATUS "Link path is = ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")

#add_executable(Test Test/Test.cpp)
#target_link_libraries(Test Cout Cin)

#set(Test_DIR Test)
#build_execute(Test Cout Cin)
#
#set(Test_VirtualClass_DIR Test_VirtualClass)
#build_execute(Test_VirtualClass)
#
#set(MD5_DIR MD5)
#build_execute(MD5)
#
#set(Test_FileWritAndRead_DIR Test_FileWritAndRead)
#build_execute(Test_FileWritAndRead)
#
#set(ToByte_DIR ToByte)
#build_execute(ToByte Log)

set(UT_Log_DIR Test/Log)
build_execute(UT_Log Log)

set(UT_Mutex_DIR Test/Mutex)
build_execute(UT_Mutex  Mutex Log gtest)

set(UT_Math_DIR Test/Math)
build_execute(UT_Math  Math Log gtest)

set(UT_Model_DIR Test/Model)
build_execute(UT_Model Model Math Log gtest)

