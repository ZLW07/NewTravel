//
// Created by wei on 2022/6/6.
//

#ifndef NEWTRAVEL_ROBOT_SIMULATION_H
#define NEWTRAVEL_ROBOT_SIMULATION_H

#include "robot_body_load.h"
#include "robot_joint_degree_constrol_slider.h"
#include "robot_joint_degree_spinbox.h"
#include "robot_joint_label.h"
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui
{
class RobotSimulation;
}
QT_END_NAMESPACE

class RobotSimulationPlatform : public QWidget
{
    Q_OBJECT

public:
    explicit RobotSimulationPlatform(QWidget *parent = nullptr);
    ~RobotSimulationPlatform() override;

private:
    Ui::RobotSimulation *ui;
    RobotBody *m_pWidget;
    RobotJointDegreeControlSlider *m_pMySlider[6];
    RobotJointSpinBox *m_pSpinBox[6];
    RobotJointLabel *m_pRobotJointLabel[6];
};

#endif // NEWTRAVEL_ROBOT_SIMULATION_H
