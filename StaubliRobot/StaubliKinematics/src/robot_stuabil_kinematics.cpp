//
// Created by wei on 2023/8/2.
//

#include "StuabilKinematics//robot_stuabil_kinematics.h"
#include "Kinematics/modern_robotics.h"

StuRobotKinematics::StuRobotKinematics()
{
    m_matSlist <<0, 0, 0, 0, 0, 0,
                 0, 1, 1, 0, 1, 0,
                 1, 0, 0, 1, 0, 1,
                 0, 0,-0.4, 0.020, -0.85, 0.020,
                 0, 0, 0, 0, 0, 0,
                 0, 0, 0, 0, 0, 0;

    m_matInitM << 1, 0, 0, 0,
        0, 1, 0, 0.020,
        0, 0, 1, 0.920,
        0, 0, 0, 1;
}

Eigen::Matrix4d StuRobotKinematics::ForwardKinematics(Eigen::Vector<double, 6> &vecTheta,std::vector<Eigen::Matrix4d> &outJointTransForm)
{
    return zl::Kinematics::FKinSpace(outJointTransForm, m_matInitM, m_matSlist, vecTheta);
}

