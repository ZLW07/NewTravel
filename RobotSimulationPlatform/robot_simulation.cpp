//
// Created by wei on 2022/6/6.
//

// You may need to build the project (run Qt uic code generator) to get "ui_my_robot.h" resolved

#include "robot_simulation.h"
#include "robot_simulation_main_platform.h"

RobotSimulationPlatform::RobotSimulationPlatform(QWidget *parent) : QWidget(parent), ui(new Ui::RobotSimulation)
{
    ui->setupUi(this);
    m_pWidget = new RobotBody(this);
    m_pWidget->resize(800,600);
    m_pWidget->show();
    for (int ii = 0; ii < 6; ++ii)
    {
        m_pRobotJointLabel[ii] = new RobotJointLabel(this);
        m_pRobotJointLabel[ii]->Initial(ii);
        m_pSpinBox[ii] = new RobotJointSpinBox(this);
        m_pSpinBox[ii]->Initial(ii);

        m_pMySlider[ii] = new RobotJointDegreeControlSlider(this);
        m_pMySlider[ii]->Initial(ii);
        connect(m_pMySlider[ii], SIGNAL(valueChanged(int)),m_pSpinBox[ii], SLOT(setValue(int)));
    }
    connect(m_pMySlider[0], SIGNAL(valueChanged(int)),m_pWidget, SLOT(SetRotationAngleOfJoint_0(int)));
    connect(m_pMySlider[1], SIGNAL(valueChanged(int)),m_pWidget, SLOT(SetRotationAngleOfJoint_1(int)));
    connect(m_pMySlider[2], SIGNAL(valueChanged(int)),m_pWidget, SLOT(SetRotationAngleOfJoint_2(int)));
    connect(m_pMySlider[3], SIGNAL(valueChanged(int)),m_pWidget, SLOT(SetRotationAngleOfJoint_3(int)));
    connect(m_pMySlider[4], SIGNAL(valueChanged(int)),m_pWidget, SLOT(SetRotationAngleOfJoint_4(int)));
    connect(m_pMySlider[5], SIGNAL(valueChanged(int)),m_pWidget, SLOT(SetRotationAngleOfJoint_5(int)));

}

RobotSimulationPlatform::~RobotSimulationPlatform()
{
    delete ui;
}
