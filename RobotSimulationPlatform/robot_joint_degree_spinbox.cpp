//
// Created by wei on 2022/6/6.
//

#include "robot_joint_degree_spinbox.h"

RobotJointSpinBox::RobotJointSpinBox(QWidget *parent) : QDoubleSpinBox(parent)
{
}

RobotJointSpinBox::~RobotJointSpinBox() noexcept {

}

void RobotJointSpinBox::Initial(int iIndex)
{
    resize(50, 30);
    move(860, iIndex * 40 + 10);
    setMinimum(-180);
    setMaximum(180);
    setSingleStep(1);
    show();
}

void RobotJointSpinBox::SetLimitValue(double iMaxValue,double iMinValue,double iStep)
{
    setMaximum(iMaxValue);
    setMinimum(iMinValue);
    setSingleStep(iStep);
    setValue(0);
}



