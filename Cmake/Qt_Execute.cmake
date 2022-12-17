set(UT_QT_DIR Test/Qt)
qt_execute(UT_QT GL GLU Model Math Log)


set(RobotSimulation_DIR RobotSimulationPlatform)
qt_execute(RobotSimulation GL GLU Model Math Log)

set(GLTest_DIR GLTest)
qt_execute(GLTest GL GLU glut Log)