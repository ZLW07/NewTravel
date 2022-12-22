
//#include "robot_simulation.h"
//#include <QApplication>
//
//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
//    RobotSimulationPlatform w;
//    w.show();
//    return a.exec();
//}

#include "ui_robot_simulation_platform.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Ui::RobotSimulationPlatform w;
    QWidget qq;
    w.setupUi(&qq);
    qq.show();
    return a.exec();
}


