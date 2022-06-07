//
// Created by wei on 2022/5/21.
//

//#include"myopenglwiegt.h"
//#include <QApplication>
//
//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
//    Widget w;
//    w.show();
//    w.resize(800, 600);
//
//    return a.exec();
//}


#include"my_robot.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    my_robot w;
    w.show();
    return a.exec();
}


