//
// Created by wei on 2023/8/2.
//

#ifndef NEWTRAVEL_ROBOT_STUABIL_KINEMATICS_H
#define NEWTRAVEL_ROBOT_STUABIL_KINEMATICS_H

#include "Kinematics/modern_robotics.h"
#include <map>

class StuRobotKinematics
{
public:
    StuRobotKinematics();
    ~StuRobotKinematics() = default;

public:
    Eigen::Matrix4d ForwardKinematics(Eigen::Vector<double, 6> &vecTheta, std::vector<Eigen::Matrix4d> &outJointTransForm);
private:
    Eigen::Matrix4d  m_matInitM;
    Eigen::Matrix<double, 6, 6> m_matSlist;

    std::map<std::string,Eigen::Matrix4d> m_mInitTrans;
};
#endif // NEWTRAVEL_ROBOT_STUABIL_KINEMATICS_H
