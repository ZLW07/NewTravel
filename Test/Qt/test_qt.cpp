//
// Created by wei on 2022/5/21.
//

#include"myopenglwiegt.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    w.resize(800, 600);

    return a.exec();
}


