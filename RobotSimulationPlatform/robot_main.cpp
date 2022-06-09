
#include "robot_simulation.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RobotSimulationPlatform w;
    w.show();
    return a.exec();
}


