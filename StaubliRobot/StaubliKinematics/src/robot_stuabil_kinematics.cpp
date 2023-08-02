//
// Created by wei on 2023/8/2.
//

#include "StubilRobotKinematics/robot_stuabil_kinematics.h"
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
        0, 0, 1, 920,
        0, 0, 0, 1;

    Eigen::Matrix4d matLink1;
    matLink1 <<
        1,0,0,0,
        0,0,1,0,
        0,-1,0,-0.375,
        0,0,0,1;

    m_mInitTrans["Link_1"] = matLink1;
    Eigen::Matrix4d matLink2;
    matLink2 <<
        1,0,0,0,
        0,0,1,0,
        0,-1,0,0,
        0,0,0,1;
    m_mInitTrans["Link_2"] = matLink2;
    Eigen::Matrix4d matLink3;
    matLink3 << 1,0,0,0,
        0,0,1,0,
        0,-1,0,0,
        0,0,0,1;
    m_mInitTrans["Link_3"] = matLink3;
    Eigen::Matrix4d matLink4;
    matLink4 << 1,0,0,0,
        0,0,1,0.020,
        0,-1,0,0.4,
        0,0,0,1;
    m_mInitTrans["Link_4"] = matLink4;

    Eigen::Matrix4d matLink5;
    matLink5 << 1,0,0,0,
        0,1,0,0.020,
        0,0,1,0.4,
        0,0,0,1;
    m_mInitTrans["Link_5"] = matLink5;

    Eigen::Matrix4d matLink6;
    matLink6 << 1,0,0,0,
        0,0,-1,0.020,
        0,1,0,0.85,
        0,0,0,1;
    m_mInitTrans["Link_6"] = matLink6;

    Eigen::Matrix4d matLink7;
    matLink7 << 1, 0, 0, 0,
        0, 1, 0, 0.020,
        0, 0, 1, 0.92,
        0, 0, 0, 1;
    m_mInitTrans["Link_7"] = matLink7;
}

Eigen::Matrix4d StuRobotKinematics::ForwardKinematics(Eigen::Vector<double, 6> &vecTheta,std::vector<Eigen::Matrix4d> &outJointTransForm)
{
    return zl::Kinematics::FKinSpace(outJointTransForm, m_matInitM, m_matSlist, vecTheta);
}

