#include "widget.h"
#include <QApplication>
#include"GL/glut.h"

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    QApplication a(argc, argv);
    Widget WW;
    WW.show();
    return a.exec();
}


