#ifndef WIDGET_H
#define WIDGET_H

#include <QMainWindow>
class GLMainWidget;
class Widget : public QMainWindow
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

private:
    GLMainWidget*glWidget;
};

#endif // WIDGET_H
