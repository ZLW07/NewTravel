//
// Created by wei on 2022/6/6.
//

#include "robot_joint_degree_control_slider.h"

RobotJointDegreeControlSlider::RobotJointDegreeControlSlider(QWidget *parent) : QSlider(parent), m_Multiplier(10000.0)
{

    connect(this, SIGNAL(valueChanged(int)), this, SLOT(setValue(int)));
    setSingleStep(1);
    setOrientation(Qt::Horizontal);
    setFocusPolicy(Qt::NoFocus);
}

RobotJointDegreeControlSlider::~RobotJointDegreeControlSlider() noexcept {}

void RobotJointDegreeControlSlider::Initial(int iIndex)
{
    setMaximum(180);
    setMinimum(-180);
    setOrientation(Qt::Horizontal);
    resize(260, 30);
    move(920, iIndex * 40 + 10);
    setSingleStep(5);
    show();
}

int RobotJointDegreeControlSlider::GetCurrent()
{
    int iValue = value();
    std::cout << iValue << std::endl;
    return iValue;
}

void RobotJointDegreeControlSlider::setValue(int Value)
{
    emit valueChanged((double)Value / m_Multiplier);
}

void RobotJointDegreeControlSlider::setValue(double Value, bool BlockSignals)
{
    QSlider::blockSignals(BlockSignals);

    QSlider::setValue(Value * m_Multiplier);

    if (!BlockSignals)
        emit valueChanged(Value);

    QSlider::blockSignals(false);
}

void RobotJointDegreeControlSlider::setRange(double Min, double Max)
{
    QSlider::setRange(Min * m_Multiplier, Max * m_Multiplier);

    emit rangeChanged(Min, Max);
}

void RobotJointDegreeControlSlider::setMinimum(double Min)
{
    QSlider::setMinimum(Min * m_Multiplier);

    emit rangeChanged(minimum(), maximum());
}

double RobotJointDegreeControlSlider::minimum() const
{
    return QSlider::minimum() / m_Multiplier;
}

void RobotJointDegreeControlSlider::setMaximum(double Max)
{
    QSlider::setMaximum(Max * m_Multiplier);

    emit rangeChanged(minimum(), maximum());
}

double RobotJointDegreeControlSlider::maximum() const
{
    return QSlider::maximum() / m_Multiplier;
}

double RobotJointDegreeControlSlider::value() const
{
    int Value = QSlider::value();
    return (double)Value / m_Multiplier;
}

