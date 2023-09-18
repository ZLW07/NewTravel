//
// Created by wei on 2023/8/2.
//

#include "StuabilKinematics/robot_stuabil_kinematics.h"
#include "Kinematics/modern_robotics.h"

namespace zl
{
StuRobotKinematics::StuRobotKinematics()
{
    m_matSlist << 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, -0.4, 0.020, -0.85, 0.020, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0;

    m_matInitM << 1, 0, 0, 0, 0, 1, 0, 0.020, 0, 0, 1, 0.920, 0, 0, 0, 1;
    m_vecJointLimit.emplace_back(-10, 3.1415);
    m_vecJointLimit.emplace_back(-10.0, 10);
    m_vecJointLimit.emplace_back(0.0, 3.1415);
    m_vecJointLimit.emplace_back(0.0, 3.1415);
    m_vecJointLimit.emplace_back(0.0, 3.1415);
    m_vecJointLimit.emplace_back(0.0, 3.1415);
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

std::vector<std::vector<double>> StuRobotKinematics::IKinSpace(Eigen::Matrix4d &TargetTransForm)
{
    std::vector<std::vector<double>> oResult;
    m_dAx = TargetTransForm(0, 2);
    m_dAy = TargetTransForm(1, 2);
    m_dAz = TargetTransForm(2, 2);

    m_dPx = TargetTransForm(0, 3);
    m_dPy = TargetTransForm(1, 3);
    m_dPz = TargetTransForm(2, 3);

    // theta1
    double dA1 = 0.07 * m_dAy - m_dPy;
    double dB1 = m_dPx - 0.07 * m_dAx;
    double dG1 = std::sqrt(std::pow(dA1, 2) + std::pow(dB1, 2));
    double dTmpTheta = atan2(dA1 / dG1, dB1 / dG1);
    double dSinTmpTheta = -0.02 / dG1;
    double dCosTmpTheta_1 = std::sqrt(1 - std::pow(dSinTmpTheta, 2));
    double dCosTmpTheta_2 = -std::sqrt(1 - std::pow(dSinTmpTheta, 2));
    double dTheta_11 = atan2(dSinTmpTheta, dCosTmpTheta_1) - dTmpTheta;
    double dTheta_12 = atan2(dSinTmpTheta, dCosTmpTheta_2) - dTmpTheta;
//    ZLOG_INFO << "dTheta_1: " << dTheta_11 << ": dTheta_2: " << dTheta_12 << "; dTmpTheta: " << dTmpTheta;
    if ((dTheta_11 > m_vecJointLimit.at(0).dMinRadJoints) && (dTheta_11 < m_vecJointLimit.at(0).dMaxRadJoints))
    {
        std::vector<double> vecTmp = {dTheta_11};
        oResult.push_back(vecTmp);
    }
    if ((dTheta_12 > m_vecJointLimit.at(0).dMinRadJoints) && (dTheta_11 < m_vecJointLimit.at(0).dMaxRadJoints))
    {
        std::vector<double> vecTmp = {dTheta_12};
        oResult.push_back(vecTmp);
    }
    // theata2
    GetTheta2(oResult);
    return oResult;
}

void StuRobotKinematics::GetTheta2(std::vector<std::vector<double>> &oAngleRad)
{
    std::vector<std::vector<double>> vecTmp;
    for (int ii = 0; ii < oAngleRad.size(); ++ii)
    {
        double TmpTheta1 = oAngleRad.at(ii).at(0);
        double dA2 = m_dAx * cos(TmpTheta1) + m_dAy * sin(TmpTheta1);
        double dB2 = m_dPx * cos(TmpTheta1) + m_dPy * sin(TmpTheta1);
        double dE2 = 20 * (dB2 - 0.07 * dA2) / 9;
        double dF2 = 20 * (0.07 * m_dAz - m_dPz) / 9;
        double dG2 = std::sqrt(std::pow(dE2, 2) + std::pow(dF2, 2)); // todo: check dG2== 0?

        double dPhi2 = std::atan2(dE2 / dG2, dF2 / dG2);
        ZLOG_INFO << dPhi2;
        double dTmpCosBeta = ((double)17 / 81 - std::pow(dG2, 2)) * 9 / (16 * dG2);
        ZLOG_INFO << "dTmpCosBeta: " << dTmpCosBeta;
        double dTmpSinBeta21 = std::sqrt(1 - std::pow(dTmpCosBeta, 2));
        double dTmpSinBeta22 = -std::sqrt(1 - std::pow(dTmpCosBeta, 2));
        ZLOG_INFO << dTmpSinBeta21 << "; " << dTmpSinBeta22;
        double dTheta_21 = std::atan2(dTmpSinBeta21, dTmpCosBeta) - dPhi2;
        double dTheta_22 = std::atan2(dTmpSinBeta22, dTmpCosBeta) - dPhi2;
//        ZLOG_INFO << "dTheta_21: " << dTheta_21 << ": dTheta_22: " << dTheta_22;
        if (dTheta_21 > m_vecJointLimit.at(1).dMinRadJoints && (dTheta_21 < m_vecJointLimit.at(1).dMaxRadJoints))
        {
            std::vector<double> vecTmpJoint = oAngleRad.at(ii);
            vecTmpJoint.emplace_back(dTheta_21);
            vecTmp.push_back(vecTmpJoint);
        }
        if (dTheta_22 > m_vecJointLimit.at(1).dMinRadJoints && (dTheta_22 < m_vecJointLimit.at(1).dMaxRadJoints))
        {
            std::vector<double> vecTmpJoint = oAngleRad.at(ii);
            vecTmpJoint.emplace_back(dTheta_22);
            vecTmp.push_back(vecTmpJoint);
        }
    }
    oAngleRad = vecTmp;
    ZLOG_INFO << vecTmp.size();
}
} // namespace zl