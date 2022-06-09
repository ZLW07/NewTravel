//
// Created by wei on 2022/6/9.
//

#ifndef NEWTRAVEL_ROBOT_JOINT_LABEL_H
#define NEWTRAVEL_ROBOT_JOINT_LABEL_H

#include <QLabel>
#include <iostream>

class RobotJointLabel  :  public  QLabel
{
Q_OBJECT
public:
    RobotJointLabel(QWidget *parent = nullptr);
    ~RobotJointLabel();

public:
    void Initial(int iIndex);

};

#endif // NEWTRAVEL_ROBOT_JOINT_LABEL_H
