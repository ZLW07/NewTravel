//
// Created by wei on 2022/5/21.
//

//#include <QApplication>
//#include <QPushButton>
//#include "Log/log.h"
//
//int main(int argc, char *argv[]) {
//    QApplication a(argc, argv);
//    QPushButton button("Hello world!", nullptr);
//    button.resize(200, 100);
//    button.show();
//    return QApplication::exec();
//}

#include<QApplication>
#include"myopenglwiegt.h"

int main(int argc,char* argv[])
{
    QApplication app(argc,argv);
    MyopenGLWiegt w;
     w.resize(400,300);
    w.show();
    return app.exec();
}

