//
// Created by wei on 2022/6/9.
//

#include "robot_joint_label.h"

RobotJointLabel::RobotJointLabel(QWidget *parent) : QLabel(parent) {}

RobotJointLabel::~RobotJointLabel() noexcept = default;

void RobotJointLabel::Initial(int iIndex)
{
    move(800, iIndex * 40 + 10);
    resize(50, 30);
    setText(QString::fromStdString("Joint_" + std::to_string(iIndex)));
    show();
}