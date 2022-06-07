//
// Created by wei on 2022/6/6.
//

#ifndef NEWTRAVEL_MY_ROBOT_H
#define NEWTRAVEL_MY_ROBOT_H

#include "my_SpinBox.h"
#include "my_slider.h"
#include "myopenglwiegt.h"
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui
{
class my_robot;
}
QT_END_NAMESPACE

class my_robot : public QWidget
{
    Q_OBJECT

public:
    explicit my_robot(QWidget *parent = nullptr);
    ~my_robot() override;

private:
    Ui::my_robot *ui;
    Widget *m_pWidget;
    my_slider *m_pMySlider[6];
    my_SpinBox *m_pSpinBox[6];
};

#endif // NEWTRAVEL_MY_ROBOT_H
