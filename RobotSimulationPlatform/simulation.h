//
// Created by wei on 2022/12/22.
//

#ifndef NEWTRAVEL_SIMULATION_H
#define NEWTRAVEL_SIMULATION_H

#include <QWidget>
#include <QGroupBox>
#include "robot_joint_degree_control_slider.h"
#include "robot_body_load.h"
#include "robot_joint_label.h"
#include "robot_joint_degree_spinbox.h"

#include "ui_robot_simulation_platform.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class RobotSimulationPlatform;
}

namespace Ui {

class RobotSimulation: public RobotSimulationPlatform , public QWidget
{
public:
    RobotSimulation(QWidget *parent = nullptr);
    void Init()
    {

    }

    void InitIconInitialPosition();
    void InitSignalConnection();
    void SetUpUI(QWidget *RobotSimulationPlatform);
    void RetranslateUi(QWidget *RobotSimulationPlatform);

private:
    RobotJointSpinBox *m_pSpinBox[6];
    RobotJointDegreeControlSlider *m_pMySlider[6];
    QGroupBox *group_8;
};

RobotSimulation::RobotSimulation(QWidget *parent):QWidget(parent)
{
    Init();
    SetUpUI(this);
    InitIconInitialPosition();
    InitSignalConnection();
}

void RobotSimulation::SetUpUI(QWidget *RobotSimulationPlatform)
{
    if (RobotSimulationPlatform->objectName().isEmpty())
        RobotSimulationPlatform->setObjectName(QString::fromUtf8("RobotSimulationPlatform"));
    RobotSimulationPlatform->resize(1083, 713);
    gridLayout = new QGridLayout(RobotSimulationPlatform);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    horizontalLayout_9 = new QHBoxLayout();
    horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
    openGLWidget = new RobotBody(RobotSimulationPlatform);
    openGLWidget->setObjectName(QString::fromUtf8("openGLWidget"));
    openGLWidget->setEnabled(true);
    openGLWidget->setMinimumSize(QSize(700, 600));

    horizontalLayout_9->addWidget(openGLWidget);

    verticalLayout_4 = new QVBoxLayout();
    verticalLayout_4->setSpacing(21);
    verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
    verticalLayout_4->setContentsMargins(0, -1, -1, -1);
    verticalLayout = new QVBoxLayout();
    verticalLayout->setSpacing(5);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    horizontalLayout = new QHBoxLayout();
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));



    label = new RobotJointLabel(RobotSimulationPlatform);
    label->setObjectName(QString::fromUtf8("label"));

    horizontalLayout->addWidget(label);



    m_pSpinBox[0] = new RobotJointSpinBox(RobotSimulationPlatform);
    m_pSpinBox[0] ->setObjectName(QString::fromUtf8("doubleSpinBox"));
    horizontalLayout->addWidget(m_pSpinBox[0]);

    m_pMySlider[0] = new RobotJointDegreeControlSlider(RobotSimulationPlatform);
    m_pMySlider[0]->setObjectName(QString::fromUtf8("horizontalSlider"));
    m_pMySlider[0]->setOrientation(Qt::Horizontal);

    horizontalLayout->addWidget(m_pMySlider[0]);
    group_8->setLayout(horizontalLayout);
    verticalLayout->addWidget(group_8);
//    verticalLayout->addLayout(horizontalLayout);



    horizontalLayout_2 = new QHBoxLayout();
    horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
    label_2 = new RobotJointLabel(RobotSimulationPlatform);
    label_2->setObjectName(QString::fromUtf8("label_2"));

    horizontalLayout_2->addWidget(label_2);

    m_pSpinBox[1] = new RobotJointSpinBox(RobotSimulationPlatform);
    m_pSpinBox[1] ->setObjectName(QString::fromUtf8("doubleSpinBox_2"));

    horizontalLayout_2->addWidget(m_pSpinBox[1]);

    m_pMySlider[1] = new RobotJointDegreeControlSlider(RobotSimulationPlatform);
    m_pMySlider[1]->setObjectName(QString::fromUtf8("horizontalSlider_2"));
    m_pMySlider[1]->setOrientation(Qt::Horizontal);
//    m_pMySlider[1]->setStyleSheet("QSlider{border:2px solid rgb(0, 0, 0);}");
    horizontalLayout_2->addWidget(m_pMySlider[1]);



    verticalLayout->addLayout(horizontalLayout_2);



    horizontalLayout_3 = new QHBoxLayout();
    horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
    label_3 = new RobotJointLabel(RobotSimulationPlatform);
    label_3->setObjectName(QString::fromUtf8("label_3"));

    horizontalLayout_3->addWidget(label_3);

    m_pSpinBox[2]  = new RobotJointSpinBox(RobotSimulationPlatform);
    m_pSpinBox[2]->setObjectName(QString::fromUtf8("doubleSpinBox_3"));

    horizontalLayout_3->addWidget(m_pSpinBox[2]);

    m_pMySlider[2] = new RobotJointDegreeControlSlider(RobotSimulationPlatform);
    m_pMySlider[2]->setObjectName(QString::fromUtf8("horizontalSlider_3"));
    m_pMySlider[2]->setOrientation(Qt::Horizontal);

    horizontalLayout_3->addWidget(m_pMySlider[2]);


    verticalLayout->addLayout(horizontalLayout_3);

    horizontalLayout_4 = new QHBoxLayout();
    horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
    label_4 = new RobotJointLabel(RobotSimulationPlatform);
    label_4->setObjectName(QString::fromUtf8("label_4"));

    horizontalLayout_4->addWidget(label_4);

    m_pSpinBox[3] = new RobotJointSpinBox(RobotSimulationPlatform);
    m_pSpinBox[3]->setObjectName(QString::fromUtf8("doubleSpinBox_4"));

    horizontalLayout_4->addWidget(m_pSpinBox[3]);

    m_pMySlider[3] = new RobotJointDegreeControlSlider(RobotSimulationPlatform);
    m_pMySlider[3]->setObjectName(QString::fromUtf8("horizontalSlider_4"));
    m_pMySlider[3]->setOrientation(Qt::Horizontal);

    horizontalLayout_4->addWidget(m_pMySlider[3]);


    verticalLayout->addLayout(horizontalLayout_4);

    horizontalLayout_5 = new QHBoxLayout();
    horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
    label_5 = new RobotJointLabel(RobotSimulationPlatform);
    label_5->setObjectName(QString::fromUtf8("label_5"));

    horizontalLayout_5->addWidget(label_5);

    m_pSpinBox[4] = new RobotJointSpinBox(RobotSimulationPlatform);
    m_pSpinBox[4]->setObjectName(QString::fromUtf8("doubleSpinBox_5"));

    horizontalLayout_5->addWidget(m_pSpinBox[4]);

    m_pMySlider[4] = new RobotJointDegreeControlSlider(RobotSimulationPlatform);
    m_pMySlider[4]->setObjectName(QString::fromUtf8("horizontalSlider_5"));
    m_pMySlider[4]->setOrientation(Qt::Horizontal);

    horizontalLayout_5->addWidget(m_pMySlider[4]);


    verticalLayout->addLayout(horizontalLayout_5);

    horizontalLayout_6 = new QHBoxLayout();
    horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
    label_6 = new RobotJointLabel(RobotSimulationPlatform);
    label_6->setObjectName(QString::fromUtf8("label_6"));

    horizontalLayout_6->addWidget(label_6);

    m_pSpinBox[5] = new RobotJointSpinBox(RobotSimulationPlatform);
    m_pSpinBox[5]->setObjectName(QString::fromUtf8("doubleSpinBox_6"));

    horizontalLayout_6->addWidget(m_pSpinBox[5]);

    m_pMySlider[5] = new RobotJointDegreeControlSlider(RobotSimulationPlatform);
    m_pMySlider[5]->setObjectName(QString::fromUtf8("horizontalSlider_6"));
    m_pMySlider[5]->setOrientation(Qt::Horizontal);

    horizontalLayout_6->addWidget(m_pMySlider[5]);


    verticalLayout->addLayout(horizontalLayout_6);


    verticalLayout_4->addLayout(verticalLayout);

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


    verticalLayout_4->addLayout(verticalLayout_2);

    verticalLayout_3 = new QVBoxLayout();
    verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
    horizontalLayout_8 = new QHBoxLayout();
    horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
    label_8 = new QLabel(RobotSimulationPlatform);
    label_8->setObjectName(QString::fromUtf8("label_8"));

    horizontalLayout_8->addWidget(label_8);

    checkBox_3 = new QCheckBox(RobotSimulationPlatform);
    checkBox_3->setObjectName(QString::fromUtf8("checkBox_3"));

    horizontalLayout_8->addWidget(checkBox_3);

    checkBox_2 = new QCheckBox(RobotSimulationPlatform);
    checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));

    horizontalLayout_8->addWidget(checkBox_2);


    verticalLayout_3->addLayout(horizontalLayout_8);

    textBrowser_2 = new QTextBrowser(RobotSimulationPlatform);
    textBrowser_2->setObjectName(QString::fromUtf8("textBrowser_2"));

    verticalLayout_3->addWidget(textBrowser_2);


    verticalLayout_4->addLayout(verticalLayout_3);


    horizontalLayout_9->addLayout(verticalLayout_4);


    gridLayout->addLayout(horizontalLayout_9, 0, 0, 1, 1);


    RetranslateUi(RobotSimulationPlatform);

    QMetaObject::connectSlotsByName(RobotSimulationPlatform);
}

void RobotSimulation::RetranslateUi(QWidget *RobotSimulationPlatform)
{
    RobotSimulationPlatform->setWindowTitle(QApplication::translate("RobotSimulationPlatform", "RobotSimulationPlatform", nullptr));
    label->setProperty("text", QVariant(QApplication::translate("RobotSimulationPlatform", "Joint_1", nullptr)));
    label_2->setProperty("text", QVariant(QApplication::translate("RobotSimulationPlatform", "Joint_2", nullptr)));
    label_3->setProperty("text", QVariant(QApplication::translate("RobotSimulationPlatform", "Joint_3", nullptr)));
    label_4->setProperty("text", QVariant(QApplication::translate("RobotSimulationPlatform", "Joint_4", nullptr)));
    label_5->setProperty("text", QVariant(QApplication::translate("RobotSimulationPlatform", "Joint_5", nullptr)));
    label_6->setProperty("text", QVariant(QApplication::translate("RobotSimulationPlatform", "Joint_6", nullptr)));
    label_7->setText(QApplication::translate("RobotSimulationPlatform", "\346\234\253\347\253\257\345\205\263\350\212\202\345\200\274", nullptr));
    checkBox->setText(QApplication::translate("RobotSimulationPlatform", "\345\274\247\345\272\246", nullptr));
    label_8->setText(QApplication::translate("RobotSimulationPlatform", "\345\244\264\351\203\250\345\210\260\346\234\272\345\231\250\344\272\272\345\235\220\346\240\207\350\275\254\346\215\242\347\237\251\351\230\265\357\274\232", nullptr));
    checkBox_3->setText(QApplication::translate("RobotSimulationPlatform", "\346\257\253\347\261\263", nullptr));
    checkBox_2->setText(QApplication::translate("RobotSimulationPlatform", "\345\274\247\345\272\246", nullptr));
} // retranslateUi

void RobotSimulation::InitIconInitialPosition()
{
    for (int ii = 0; ii < 6; ++ii)
    {
        m_pSpinBox[ii]->SetLimitValue(180,-180,1);
        m_pMySlider[ii]->setMaximum(180);
        m_pMySlider[ii]->setMinimum(-180);
        m_pMySlider[ii]->setValue(0);
    }
}


void RobotSimulation::InitSignalConnection()
{
    for (int ii = 0; ii < 6; ++ii)
    {
        QObject::connect(m_pMySlider[ii], SIGNAL(valueChanged(double)),m_pSpinBox[ii], SLOT(setValue(double)));
        QObject::connect(m_pSpinBox[ii], SIGNAL(valueChanged(double)),m_pMySlider[ii], SLOT(setValue(double)));
    }
    QObject::connect(m_pMySlider[0], SIGNAL(valueChanged(double)),openGLWidget, SLOT(SetRotationAngleOfJoint_0(double)));
    QObject::connect(m_pMySlider[1], SIGNAL(valueChanged(double)),openGLWidget, SLOT(SetRotationAngleOfJoint_1(double)));
    QObject::connect(m_pMySlider[2], SIGNAL(valueChanged(double)),openGLWidget, SLOT(SetRotationAngleOfJoint_2(double)));
    QObject::connect(m_pMySlider[3], SIGNAL(valueChanged(double)),openGLWidget, SLOT(SetRotationAngleOfJoint_3(double)));
    QObject::connect(m_pMySlider[4], SIGNAL(valueChanged(double)),openGLWidget, SLOT(SetRotationAngleOfJoint_4(double)));
    QObject::connect(m_pMySlider[5], SIGNAL(valueChanged(double)),openGLWidget, SLOT(SetRotationAngleOfJoint_5(double)));
}
} // namespace Ui

QT_END_NAMESPACE

#endif // NEWTRAVEL_SIMULATION_H
