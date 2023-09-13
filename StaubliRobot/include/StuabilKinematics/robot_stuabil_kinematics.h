//
// Created by wei on 2023/8/2.
//

#ifndef NEWTRAVEL_ROBOT_STUABIL_KINEMATICS_H
#define NEWTRAVEL_ROBOT_STUABIL_KINEMATICS_H

#include "Kinematics/modern_robotics.h"
#include <map>

namespace zl
{
class StuRobotKinematics
{
public:
    StuRobotKinematics();
    ~StuRobotKinematics() = default;

public:
    Eigen::Matrix4d ForwardKinematics(Eigen::Vector<double, 6> &vecTheta, std::vector<Eigen::Matrix4d> &outJointTransForm, bool bAngleFlag = false);
    std::vector<double> IKinSpace(Eigen::Matrix4d &TargetTransForm);

private:
    Eigen::Matrix4d m_matInitM;
    Eigen::Matrix<double, 6, 6> m_matSlist;
};
}
#endif // NEWTRAVEL_ROBOT_STUABIL_KINEMATICS_H
