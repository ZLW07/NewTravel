//
// Created by wei on 2022/6/6.
//

#ifndef NEWTRAVEL_ROBOT_JOINT_DEGREE_CONSTROL_SLIDER_H
#define NEWTRAVEL_ROBOT_JOINT_DEGREE_CONSTROL_SLIDER_H

#include <QSlider>
#include <iostream>

class RobotJointDegreeControlSlider :  public  QSlider
{
Q_OBJECT
public:
    RobotJointDegreeControlSlider(QWidget *parent = nullptr);
    ~RobotJointDegreeControlSlider();

public:
    void Initial(int iIndex);
    int  GetCurrent();

};

#endif // NEWTRAVEL_ROBOT_JOINT_DEGREE_CONSTROL_SLIDER_H
