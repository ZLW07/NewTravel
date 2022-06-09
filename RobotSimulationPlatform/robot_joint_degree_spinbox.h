//
// Created by wei on 2022/6/6.
//

#ifndef NEWTRAVEL_ROBOT_JOINT_DEGREE_SPINBOX_H
#define NEWTRAVEL_ROBOT_JOINT_DEGREE_SPINBOX_H

#include "robot_joint_degree_constrol_slider.h"
#include <QSpinBox>
#include <QTextEdit>

class RobotJointSpinBox :  public  QSpinBox
{
Q_OBJECT
public:
    RobotJointSpinBox(QWidget *parent = nullptr);
    ~RobotJointSpinBox();

public:
    void Initial(int iIndex);
    void SetValue(int iValue);

private:
    RobotJointDegreeControlSlider *m_pSlider;
};

#endif // NEWTRAVEL_ROBOT_JOINT_DEGREE_SPINBOX_H
