set(UT_Log_DIR Test/Log)
build_execute(UT_Log Log gtest)

set(UT_Math_DIR Test/Math)
build_execute(UT_Math  Math Log gtest)

set(UT_Robot_DIR Test/Robot)
build_execute(UT_Robot Robot Math Log gtest)