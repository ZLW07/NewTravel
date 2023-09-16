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
    std::vector<Eigen::Matrix4d> &outJointTransForm, bool bAngleFlag)
{
    if (bAngleFlag)
    {
        for (int ii = 0; ii < 6; ++ii)
        {
            vecTheta[ii] = M_PI * (vecTheta[ii]) / 180;
        }
    }
    vecTheta[1] = vecTheta[1] + M_PI * (90) / 180;
    vecTheta[2] = vecTheta[2] + M_PI * (-90) / 180;
    return zl::Kinematics::FKinSpace(outJointTransForm, m_matInitM, m_matSlist, vecTheta);
}

std::vector<double> StuRobotKinematics::IKinSpace(Eigen::Matrix4d &TargetTransForm)
{
    auto a_y = TargetTransForm(1, 2);
    auto a_x = TargetTransForm(0, 2);

    auto p_x = TargetTransForm(0, 3);
    auto p_y = TargetTransForm(1, 3);

    // theta1
    double dA1 = 0.07 * a_y - p_y;
    double dB1 = p_x - 0.07 * a_x;
    double dG1 = std::sqrt(std::pow(dA1, 2) + std::pow(dB1, 2));
    double dTmpTheta = atan2(dA1/dG1,dB1/dG1);
    double dSinTmpTheta = -0.02/dG1;
    double dCosTmpTheta_1 = std::sqrt(1 - std::pow(dSinTmpTheta, 2));
    double dCosTmpTheta_2 = -std::sqrt(1 - std::pow(dSinTmpTheta, 2));
    double dTheta_1 = atan2(dSinTmpTheta, dCosTmpTheta_1) - dTmpTheta;
    double dTheta_2 = atan2(dSinTmpTheta, dCosTmpTheta_2) -dTmpTheta;
    ZLOG_INFO << "dTheta_1: " << dTheta_1 << ": dTheta_2: " << dTheta_2 << "; dTmpTheta: " << dTmpTheta;
    return std::vector<double>();
}
} // namespace zl