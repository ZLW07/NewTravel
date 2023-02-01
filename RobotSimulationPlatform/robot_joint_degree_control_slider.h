//
// Created by wei on 2022/6/6.
//

#ifndef NEWTRAVEL_ROBOT_JOINT_DEGREE_CONTROL_SLIDER_H
#define NEWTRAVEL_ROBOT_JOINT_DEGREE_CONTROL_SLIDER_H

#include <QSlider>
#include <iostream>
#include <QtGui/QtGui>

class RobotJointDegreeControlSlider :  public  QSlider
{
Q_OBJECT
public:
    RobotJointDegreeControlSlider(QWidget *parent = nullptr);
    ~RobotJointDegreeControlSlider();
    void setRange(double Min, double Max);
    void setMinimum(double Min);
    double minimum() const;
    void setMaximum(double Max);
    double maximum() const;
    double value() const;

public slots:
    void setValue(int value);
    void setValue(double Value, bool BlockSignals = false);

private slots:

signals :
    void valueChanged(double Value);
    void rangeChanged(double Min, double Max);

private:
    double m_Multiplier;
public:
    void Initial(int iIndex);
    int  GetCurrent();

};

#endif // NEWTRAVEL_ROBOT_JOINT_DEGREE_CONTROL_SLIDER_H
