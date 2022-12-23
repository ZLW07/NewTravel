//
// Created by wei on 2022/6/6.
//

#ifndef NEWTRAVEL_ROBOT_JOINT_DEGREE_SPINBOX_H
#define NEWTRAVEL_ROBOT_JOINT_DEGREE_SPINBOX_H

#include <QSpinBox>
#include <QTextEdit>

class RobotJointSpinBox :  public  QDoubleSpinBox
{
Q_OBJECT
public:
    RobotJointSpinBox(QWidget *parent = nullptr);
    ~RobotJointSpinBox();

public:
    void Initial(int iIndex);
    void SetLimitValue(double iMaxValue,double iMinValue,double iStep);
};

#endif // NEWTRAVEL_ROBOT_JOINT_DEGREE_SPINBOX_H
