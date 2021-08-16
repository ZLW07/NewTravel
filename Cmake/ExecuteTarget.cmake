
message(STATUS "Link path is = ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")

#add_executable(Test Test/Test.cpp)
#target_link_libraries(Test Cout Cin)

set(Test_DIR Test)
build_execute(Test Cout Cin)

set(Test_VirtualClass_DIR Test_VirtualClass)
build_execute(Test_VirtualClass)

set(MD5_DIR MD5)
build_execute(MD5)

set(Test_FileWritAndRead_DIR Test_FileWritAndRead)
build_execute(Test_FileWritAndRead)

set(ToByte_DIR ToByte)
build_execute(ToByte Log)

