/********************************************************************************
** Form generated from reading UI file 'robot_simulation_platform.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ROBOT_SIMULATION_PLATFORM_H
#define UI_ROBOT_SIMULATION_PLATFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "robot_body_load.h"
#include "robot_joint_degree_spinbox.h"
#include "robot_joint_label.h"


QT_BEGIN_NAMESPACE

class Ui_RobotSimulationPlatform
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    RobotBody *openGLWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    RobotJointLabel *label;
    RobotJointSpinBox *doubleSpinBox;
    QSlider *horizontalSlider;
    QHBoxLayout *horizontalLayout_2;
    RobotJointLabel *label_2;
    RobotJointSpinBox *doubleSpinBox_2;
    QSlider *horizontalSlider_2;
    QHBoxLayout *horizontalLayout_4;
    RobotJointLabel *label_4;
    RobotJointSpinBox *doubleSpinBox_4;
    QSlider *horizontalSlider_4;
    QHBoxLayout *horizontalLayout_3;
    RobotJointLabel *label_3;
    RobotJointSpinBox *doubleSpinBox_3;
    QSlider *horizontalSlider_3;
    QHBoxLayout *horizontalLayout_6;
    RobotJointLabel *label_6;
    RobotJointSpinBox *doubleSpinBox_6;
    QSlider *horizontalSlider_6;
    QHBoxLayout *horizontalLayout_5;
    RobotJointLabel *label_5;
    RobotJointSpinBox *doubleSpinBox_5;
    QSlider *horizontalSlider_5;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_7;
    QCheckBox *checkBox;
    QTextBrowser *textBrowser;

    void setupUi(QWidget *RobotSimulationPlatform)
    {
        if (RobotSimulationPlatform->objectName().isEmpty())
            RobotSimulationPlatform->setObjectName(QString::fromUtf8("RobotSimulationPlatform"));
        RobotSimulationPlatform->resize(874, 476);
        gridLayout_2 = new QGridLayout(RobotSimulationPlatform);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        openGLWidget = new RobotBody(RobotSimulationPlatform);
        openGLWidget->setObjectName(QString::fromUtf8("openGLWidget"));
        openGLWidget->setEnabled(true);
        openGLWidget->setMinimumSize(QSize(400, 400));

        gridLayout->addWidget(openGLWidget, 0, 0, 2, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new RobotJointLabel(RobotSimulationPlatform);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        doubleSpinBox = new RobotJointSpinBox(RobotSimulationPlatform);
        doubleSpinBox->setObjectName(QString::fromUtf8("doubleSpinBox"));

        horizontalLayout->addWidget(doubleSpinBox);

        horizontalSlider = new QSlider(RobotSimulationPlatform);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setMinimum(-180);
        horizontalSlider->setMaximum(180);
        horizontalSlider->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(horizontalSlider);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new RobotJointLabel(RobotSimulationPlatform);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        doubleSpinBox_2 = new RobotJointSpinBox(RobotSimulationPlatform);
        doubleSpinBox_2->setObjectName(QString::fromUtf8("doubleSpinBox_2"));

        horizontalLayout_2->addWidget(doubleSpinBox_2);

        horizontalSlider_2 = new QSlider(RobotSimulationPlatform);
        horizontalSlider_2->setObjectName(QString::fromUtf8("horizontalSlider_2"));
        horizontalSlider_2->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(horizontalSlider_2);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_4 = new RobotJointLabel(RobotSimulationPlatform);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_4->addWidget(label_4);

        doubleSpinBox_4 = new RobotJointSpinBox(RobotSimulationPlatform);
        doubleSpinBox_4->setObjectName(QString::fromUtf8("doubleSpinBox_4"));

        horizontalLayout_4->addWidget(doubleSpinBox_4);

        horizontalSlider_4 = new QSlider(RobotSimulationPlatform);
        horizontalSlider_4->setObjectName(QString::fromUtf8("horizontalSlider_4"));
        horizontalSlider_4->setOrientation(Qt::Horizontal);

        horizontalLayout_4->addWidget(horizontalSlider_4);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new RobotJointLabel(RobotSimulationPlatform);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        doubleSpinBox_3 = new RobotJointSpinBox(RobotSimulationPlatform);
        doubleSpinBox_3->setObjectName(QString::fromUtf8("doubleSpinBox_3"));

        horizontalLayout_3->addWidget(doubleSpinBox_3);

        horizontalSlider_3 = new QSlider(RobotSimulationPlatform);
        horizontalSlider_3->setObjectName(QString::fromUtf8("horizontalSlider_3"));
        horizontalSlider_3->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(horizontalSlider_3);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_6 = new RobotJointLabel(RobotSimulationPlatform);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_6->addWidget(label_6);

        doubleSpinBox_6 = new RobotJointSpinBox(RobotSimulationPlatform);
        doubleSpinBox_6->setObjectName(QString::fromUtf8("doubleSpinBox_6"));

        horizontalLayout_6->addWidget(doubleSpinBox_6);

        horizontalSlider_6 = new QSlider(RobotSimulationPlatform);
        horizontalSlider_6->setObjectName(QString::fromUtf8("horizontalSlider_6"));
        horizontalSlider_6->setOrientation(Qt::Horizontal);

        horizontalLayout_6->addWidget(horizontalSlider_6);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_5 = new RobotJointLabel(RobotSimulationPlatform);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_5->addWidget(label_5);

        doubleSpinBox_5 = new RobotJointSpinBox(RobotSimulationPlatform);
        doubleSpinBox_5->setObjectName(QString::fromUtf8("doubleSpinBox_5"));

        horizontalLayout_5->addWidget(doubleSpinBox_5);

        horizontalSlider_5 = new QSlider(RobotSimulationPlatform);
        horizontalSlider_5->setObjectName(QString::fromUtf8("horizontalSlider_5"));
        horizontalSlider_5->setOrientation(Qt::Horizontal);

        horizontalLayout_5->addWidget(horizontalSlider_5);


        verticalLayout->addLayout(horizontalLayout_5);


        gridLayout->addLayout(verticalLayout, 0, 1, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_7 = new QLabel(RobotSimulationPlatform);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_7->addWidget(label_7);

        checkBox = new QCheckBox(RobotSimulationPlatform);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        horizontalLayout_7->addWidget(checkBox);


        verticalLayout_2->addLayout(horizontalLayout_7);

        textBrowser = new QTextBrowser(RobotSimulationPlatform);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));

        verticalLayout_2->addWidget(textBrowser);


        gridLayout->addLayout(verticalLayout_2, 1, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        retranslateUi(RobotSimulationPlatform);

        QMetaObject::connectSlotsByName(RobotSimulationPlatform);
    } // setupUi

    void retranslateUi(QWidget *RobotSimulationPlatform)
    {
        RobotSimulationPlatform->setWindowTitle(QApplication::translate("RobotSimulationPlatform", "RobotSimulationPlatform", nullptr));
        label->setProperty("text", QVariant(QApplication::translate("RobotSimulationPlatform", "Joint_1", nullptr)));
        label_2->setProperty("text", QVariant(QApplication::translate("RobotSimulationPlatform", "Joint_2", nullptr)));
        label_4->setProperty("text", QVariant(QApplication::translate("RobotSimulationPlatform", "Joint_3", nullptr)));
        label_3->setProperty("text", QVariant(QApplication::translate("RobotSimulationPlatform", "Joint_4", nullptr)));
        label_6->setProperty("text", QVariant(QApplication::translate("RobotSimulationPlatform", "Joint_5", nullptr)));
        label_5->setProperty("text", QVariant(QApplication::translate("RobotSimulationPlatform", "Joint_6", nullptr)));
        label_7->setText(QApplication::translate("RobotSimulationPlatform", "\346\234\253\347\253\257\345\205\263\350\212\202\345\200\274", nullptr));
        checkBox->setText(QApplication::translate("RobotSimulationPlatform", "\345\274\247\345\272\246", nullptr));

        doubleSpinBox->setMinimum(-180);
        doubleSpinBox->setMaximum(180);
        doubleSpinBox->setSingleStep(0.01);
        QObject::connect(horizontalSlider, SIGNAL(valueChanged(int)),doubleSpinBox, SLOT(setValue(int)));
//        QObject::connect(doubleSpinBox, SIGNAL(ValueChange(double)),horizontalSlider, SLOT(setValue(double)));
        QObject::connect(horizontalSlider, SIGNAL(valueChanged(int)),openGLWidget, SLOT(SetRotationAngleOfJoint_0(int)));

    } // retranslateUi

};

namespace Ui {
    class RobotSimulationPlatform: public Ui_RobotSimulationPlatform {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ROBOT_SIMULATION_PLATFORM_H
