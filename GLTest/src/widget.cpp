#include "widget.h"
#include"GLMainWidget.h"
Widget::Widget(QWidget *parent)
    : QMainWindow(parent)
{
    showMaximized();
    glWidget=new GLMainWidget();
    setCentralWidget(glWidget);
}

Widget::~Widget()
{
    delete glWidget;
}
