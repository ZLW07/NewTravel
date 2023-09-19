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
    m_vecJointLimit.emplace_back(-3.1415926, 0.0);
    m_vecJointLimit.emplace_back(-2.2252948, 2.2252948);
    m_vecJointLimit.emplace_back(-2.6616271, 2.6616271);
    m_vecJointLimit.emplace_back(-4.7123889, 4.7123889);
    m_vecJointLimit.emplace_back(-2.024582, 2.1642082);
    m_vecJointLimit.emplace_back(-4.7123889, 4.7123889);
}

Eigen::Matrix4d StuRobotKinematics::ForwardKinematics(
    Eigen::Vector<double, 6> &vecTheta, std::vector<Eigen::Matrix4d> &outJointTransForm, bool bAngleFlag)
{
    if (bAngleFlag)
    {
        for (int ii = 0; ii < 6; ++ii)
        {
            vecTheta[ii] = M_PI * (vecTheta[ii]) / 180;
        }
    }
    vecTheta[1] = vecTheta[1];
    vecTheta[2] = vecTheta[2];
    return zl::Kinematics::FKinSpace(outJointTransForm, m_matInitM, m_matSlist, vecTheta);
}

std::vector<std::vector<double>> StuRobotKinematics::IKinSpace(Eigen::Matrix4d &TargetTransForm)
{
    std::vector<std::vector<double>> oResult;
    m_dNx = TargetTransForm(0, 0);
    m_dNy = TargetTransForm(1, 0);
    m_dNz = TargetTransForm(2, 0);

    m_dOx = TargetTransForm(0, 1);
    m_dOy = TargetTransForm(1, 1);
    m_dOz = TargetTransForm(2, 1);

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
    SolvingJointTwoAndThree(oResult);
    SolvingJointFive(oResult);
    return oResult;
}

void StuRobotKinematics::SolvingJointTwoAndThree(std::vector<std::vector<double>> &oAngleRad)
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
        double dTmpCosBeta = (double)((double)17 / 81 - std::pow(dG2, 2)) * 9 / (16 * dG2);
        double dTmpSinBeta21 = std::sqrt(1 - std::pow(dTmpCosBeta, 2));
        double dTmpSinBeta22 = -std::sqrt(1 - std::pow(dTmpCosBeta, 2));
        double dTheta_21 = std::atan2(dTmpSinBeta21, dTmpCosBeta) - dPhi2;
        double dTheta_22 = std::atan2(dTmpSinBeta22, dTmpCosBeta) - dPhi2;
        double dCs3 = (-dG2 * dTmpCosBeta) - (double)8 / 9;
        if (dTheta_21 > m_vecJointLimit.at(1).dMinRadJoints && (dTheta_21 < m_vecJointLimit.at(1).dMaxRadJoints))
        {
            std::vector<double> vecTmpJoint = oAngleRad.at(ii);
            vecTmpJoint.emplace_back(dTheta_21);
            double dSs3 = dG2 * dTmpSinBeta21;
            double theta_31 = std::atan2(dSs3, dCs3);
            if (theta_31 > m_vecJointLimit.at(2).dMinRadJoints && (theta_31 < m_vecJointLimit.at(2).dMaxRadJoints))
            {
                vecTmpJoint.emplace_back(theta_31);
                vecTmp.push_back(vecTmpJoint);
            }
        }
        if (dTheta_22 > m_vecJointLimit.at(1).dMinRadJoints && (dTheta_22 < m_vecJointLimit.at(1).dMaxRadJoints))
        {
            std::vector<double> vecTmpJoint = oAngleRad.at(ii);
            vecTmpJoint.emplace_back(dTheta_22);
            double dSs3 = dG2 * dTmpSinBeta22;
            double theta_31 = std::atan2(dSs3, dCs3);
            if (theta_31 > m_vecJointLimit.at(2).dMinRadJoints && (theta_31 < m_vecJointLimit.at(2).dMaxRadJoints))
            {
                vecTmpJoint.emplace_back(theta_31);
                vecTmp.push_back(vecTmpJoint);
            }
        }
    }
    oAngleRad = vecTmp;
}

void StuRobotKinematics::SolvingJointFive(std::vector<std::vector<double>> &vecAngleRad)
{
    int iCount = vecAngleRad.size();
    for (int iIndex = 0; iIndex < iCount; ++iIndex)
    {
        std::vector<std::vector<double>> vecTmpResult;
        auto vecJoints = vecAngleRad.at(iIndex);
        double dTheta23 = vecJoints.at(1) + vecJoints.at(2);
        double Cs5 = m_dAz * cos(dTheta23) + m_dAx * sin(dTheta23) * cos(vecJoints.at(0)) +
                     m_dAy * sin(dTheta23) * sin(vecJoints.at(0));
        double dTheta_51 = std::atan2(std::sqrt(1 - std::pow(Cs5, 2)), Cs5);
        double dTheta_52 = std::atan2(-std::sqrt(1 - std::pow(Cs5, 2)), Cs5);

        if(std::isnan(dTheta_51))
        {
            dTheta_51 = 0.0;
        }
        if(std::isnan(dTheta_52))
        {
            dTheta_52 = 0.0;
        }
        if ((dTheta_51 > m_vecJointLimit.at(4).dMinRadJoints) && (dTheta_51 < m_vecJointLimit.at(4).dMaxRadJoints))
        {
            std::vector<double> vecTheta4 = SolvingJointFour(vecAngleRad.at(iIndex), dTheta_51);
            for (int iJ = 0; iJ < vecTheta4.size(); ++iJ)
            {
                std::vector<double> dTmpJoints = vecAngleRad.at(iIndex);
                dTmpJoints.push_back(vecTheta4.at(iJ));
                dTmpJoints.push_back(dTheta_51);
                vecTmpResult.push_back(dTmpJoints);
            }
        }

        if ((dTheta_52 > m_vecJointLimit.at(4).dMinRadJoints) && (dTheta_52 < m_vecJointLimit.at(4).dMaxRadJoints) &&
            ((dTheta_51 - dTheta_52)) > 0.000001)
        {
            std::vector<double> vecTheta4 = SolvingJointFour(vecAngleRad.at(iIndex), dTheta_52);
            for (int iJ = 0; iJ < vecTheta4.size(); ++iJ)
            {
                std::vector<double> dTmpJoints = vecAngleRad.at(iIndex);
                dTmpJoints.push_back(vecTheta4.at(iJ));
                dTmpJoints.push_back(dTheta_52);
                vecTmpResult.push_back(dTmpJoints);
            }
        }
        vecAngleRad = vecTmpResult;
    }
    std::vector<std::vector<double>> vecTmpRe;
    for (int ii = 0; ii < vecAngleRad.size(); ++ii)
    {
        auto Joints = vecAngleRad.at(ii);
        auto vecTheta6 = SolvingJointSix(Joints, Joints.at(4));
        for (int iJ = 0; iJ < vecTheta6.size(); ++iJ)
        {
            std::vector<double> vecTmpJoints = Joints;
            vecTmpJoints.push_back(vecTheta6.at(iJ));
            vecTmpRe.push_back(vecTmpJoints);
        }
    }
    vecAngleRad = vecTmpRe;
}
std::vector<double> StuRobotKinematics::SolvingJointFour(std::vector<double> &vecAngleRad, double &dTheta5)
{
    std::vector<double> dResult;
    double dA4 = m_dPy * cos(vecAngleRad.at(0)) - m_dPx * sin(vecAngleRad.at(0)) - 0.02;

    if (std::fabs(sin(dTheta5)) > 0.0000001)
    {
        double dTheta23 = vecAngleRad.at(1) + vecAngleRad.at(2);
        double Cs4 =
            (0.4 * sin(vecAngleRad.at(2)) - m_dPz * sin(dTheta23) + m_dPx * cos(dTheta23) * cos(vecAngleRad.at(0)) +
                m_dPy * cos(dTheta23) * sin(vecAngleRad.at(0))) /
            (0.07 * sin(dTheta5));
        double dSs4 = dA4 / (0.07 * sin(dTheta5));
        double dTheta_41 = std::atan2(dSs4, Cs4);
        if (dTheta_41 > m_vecJointLimit.at(3).dMinRadJoints && (dTheta_41 < m_vecJointLimit.at(3).dMaxRadJoints))
        {
            dResult.push_back(dTheta_41);
            if (((dTheta_41 + 2 * 3.1415926) > m_vecJointLimit.at(3).dMinRadJoints) &&
                ((dTheta_41 + 2 * 3.1415926) < m_vecJointLimit.at(3).dMaxRadJoints))
            {
                dResult.push_back(dTheta_41 + 2 * 3.1415926);
            }
            if (((dTheta_41 - 2 * 3.1415926) > m_vecJointLimit.at(3).dMinRadJoints) &&
                ((dTheta_41 - 2 * 3.1415926) < m_vecJointLimit.at(3).dMaxRadJoints))
            {
                dResult.push_back(dTheta_41 - 2 * 3.1415926);
            }
        }
    }
    else
    {
        dResult.push_back(0.0);
        dResult.push_back(3.1415926);
        dResult.push_back(-3.1415926);
    }
    return dResult;
}

std::vector<double> StuRobotKinematics::SolvingJointSix(std::vector<double> &vecAngleRad, double &dTheta5)
{
    std::vector<double> dResult;
    double dTheta23 = vecAngleRad.at(1) + vecAngleRad.at(2);
    if (std::fabs(sin(dTheta5)) > 0.0000001)
    {
        double dCs6 = -(m_dNz * cos(dTheta23) + m_dNx * sin(dTheta23) * cos(vecAngleRad.at(0)) +
                          m_dNy * sin(dTheta23) * sin(vecAngleRad.at(0))) /
                      sin(dTheta5);
        double dSs6 = (m_dOz * cos(dTheta23) + m_dOx * sin(dTheta23) * cos(vecAngleRad.at(0)) +
                          m_dOy * sin(dTheta23) * sin(vecAngleRad.at(0))) /
                      sin(dTheta5);
        double dTheta_61 = std::atan2(dSs6, dCs6);
        if (dTheta_61 > m_vecJointLimit.at(5).dMinRadJoints && (dTheta_61 < m_vecJointLimit.at(5).dMaxRadJoints))
        {
            dResult.push_back(dTheta_61);
            if (((dTheta_61 + 2 * 3.1415926) > m_vecJointLimit.at(5).dMinRadJoints) &&
                ((dTheta_61 + 2 * 3.1415926) < m_vecJointLimit.at(5).dMaxRadJoints))
            {
                dResult.push_back(dTheta_61 + 2 * 3.1415926);
            }
            if (((dTheta_61 - 2 * 3.1415926) > m_vecJointLimit.at(5).dMinRadJoints) &&
                ((dTheta_61 - 2 * 3.1415926) < m_vecJointLimit.at(5).dMaxRadJoints))
            {
                dResult.push_back(dTheta_61 - 2 * 3.1415926);
            }
        }
    }
    else
    {
        double dSc46 = -(m_dOx * cos(dTheta23) * cos(vecAngleRad.at(0)) - m_dOz * sin(dTheta23) +
                         m_dOy * cos(dTheta23) * sin(vecAngleRad.at(0)));
        double dCc46 = (m_dOy * cos(vecAngleRad.at(0)) - m_dOx * sin(vecAngleRad.at(0)));
        double dTheta46 = std::atan2(dSc46, dCc46);
        double dTheta6 = dTheta46 - vecAngleRad.at(3);

        if (dTheta6 > m_vecJointLimit.at(5).dMinRadJoints && (dTheta6 < m_vecJointLimit.at(5).dMaxRadJoints))
        {
            dResult.push_back(dTheta6);
        }
    }
    return dResult;
}
} // namespace zl