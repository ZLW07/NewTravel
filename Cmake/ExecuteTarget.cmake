
message(STATUS "Link path is = ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")

set(UT_Log_DIR Test/Log)
build_execute(UT_Log Log)

set(UT_Math_DIR Test/Math)
build_execute(UT_Math Math Log  gtest)

set(UT_Model_DIR Test/Model)
build_execute(UT_Model Model Math Log PQP gtest)

set(UT_Configure_DIR Test/Configure)
build_execute(UT_Configure  Configure Log TinyXML gtest)

set(UT_PQP_DIR Test/PQP)
build_execute(UT_PQP  PQP Log gtest)

set(UT_Kinematics_DIR Test/Kinematics)
build_execute(UT_Kinematics  Kinematics Log gtest)

set(UT_CollisionDetection_DIR Test/CollisionDetection)
build_execute(UT_CollisionDetection  CollisionDetection PQP Log Kinematics gtest )
