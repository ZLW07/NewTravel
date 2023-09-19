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
    Eigen::Matrix4d ForwardKinematics(
        Eigen::Vector<double, 6> &vecTheta, std::vector<Eigen::Matrix4d> &outJointTransForm, bool bAngleFlag = false);
    std::vector<std::vector<double>> IKinSpace(Eigen::Matrix4d &TargetTransForm);

private:
    struct JointLimit
    {
        double dMinRadJoints;
        double dMaxRadJoints;
        JointLimit(double dMinRad, double dMaxRad) : dMinRadJoints(dMinRad), dMaxRadJoints(dMaxRad) {}
    };

private:
    void SolvingJointTwoAndThree(std::vector<std::vector<double>> &vecAngleRad);
    void SolvingJointFive(std::vector<std::vector<double>> &vecAngleRad);
    std::vector<double> SolvingJointFour(std::vector<double> &vecAngleRad,double &dTheta5);
    std::vector<double> SolvingJointSix(std::vector<double> &vecAngleRad,double &dTheta5);

private:
    Eigen::Matrix4d m_matInitM;
    Eigen::Matrix<double, 6, 6> m_matSlist;
    std::vector<JointLimit> m_vecJointLimit;

    double m_dNx{};
    double m_dNy{};
    double m_dNz{};

    double m_dOx{};
    double m_dOy{};
    double m_dOz{};

    double m_dAx{};
    double m_dAy{};
    double m_dAz{};

    double m_dPx{};
    double m_dPy{};
    double m_dPz{};
};
} // namespace zl
#endif // NEWTRAVEL_ROBOT_STUABIL_KINEMATICS_H
