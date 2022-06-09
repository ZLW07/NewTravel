//
// Created by wei on 2022/6/6.
//

#include "robot_joint_degree_constrol_slider.h"

RobotJointDegreeControlSlider::RobotJointDegreeControlSlider(QWidget *parent) : QSlider(parent) {}

RobotJointDegreeControlSlider::~RobotJointDegreeControlSlider() noexcept {}

void RobotJointDegreeControlSlider::Initial(int iIndex)
{
    setMaximum(180);
    setMinimum(-180);
    setOrientation(Qt::Horizontal);
    resize(260, 30);
    move(920, iIndex * 40+ 10);
    setSingleStep(5);
    show();
}

int RobotJointDegreeControlSlider::GetCurrent()
{
    int iValue = value();
    std::cout << iValue << std::endl;
    return iValue;
}
