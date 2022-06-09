/********************************************************************************
** Form generated from reading UI file 'my_robot.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MY_ROBOT_H
#define UI_MY_ROBOT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class UiWindowOfRobot
{
public:

    void setupUi(QWidget *my_robot)
    {
        if (my_robot->objectName().isEmpty())
            my_robot->setObjectName(QString::fromUtf8("my_robot"));
        my_robot->resize(1200, 600);

        retranslateUi(my_robot);

        QMetaObject::connectSlotsByName(my_robot);
    } // setupUi

    void retranslateUi(QWidget *my_robot)
    {
        my_robot->setWindowTitle(QApplication::translate("my_robot", "my_robot", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RobotSimulation : public UiWindowOfRobot
{};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MY_ROBOT_H
