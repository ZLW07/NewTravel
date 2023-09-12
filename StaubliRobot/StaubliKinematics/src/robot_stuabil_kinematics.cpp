//
// Created by wei on 2023/8/2.
//

#include "StuabilKinematics//robot_stuabil_kinematics.h"
#include "Kinematics/modern_robotics.h"

namespace zl
{
StuRobotKinematics::StuRobotKinematics()
{
    m_matSlist << 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, -0.4, 0.020, -0.85, 0.020, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0;

    m_matInitM << 1, 0, 0, 0, 0, 1, 0, 0.020, 0, 0, 1, 0.920, 0, 0, 0, 1;
}

Eigen::Matrix4d StuRobotKinematics::ForwardKinematics(Eigen::Vector<double, 6> &vecTheta,
    std::vector<Eigen::Matrix4d> &outJointTransForm)
{
    return Kinematics::FKinSpace(outJointTransForm, m_matInitM, m_matSlist, vecTheta);
}

std::vector<double> StuRobotKinematics::IKinSpace(Eigen::Matrix4d &TargetTransForm)
{

    // theta1
    double dA1 = TargetTransForm(1,3) - 0.07 *TargetTransForm(1,2);
    double dB1 = TargetTransForm(0,3) - 0.07 *TargetTransForm(0,2);
    double dC1 = std::sqrt(std::pow(dA1, 2) + std::pow(dB1, 2));
    double dSinTmpTheta = 0.02/dC1;
    double dCosTmpTheta_1 = std::sqrt(1 - std::pow(dSinTmpTheta,2));
    double dCosTmpTheta_2 = - std::sqrt(1 - std::pow(dSinTmpTheta,2));
    double dTheta_1 = atan2(dSinTmpTheta,dCosTmpTheta_1);
    double dTheta_2 = atan2(dSinTmpTheta,dCosTmpTheta_2);
    return std::vector<double>();
}
}