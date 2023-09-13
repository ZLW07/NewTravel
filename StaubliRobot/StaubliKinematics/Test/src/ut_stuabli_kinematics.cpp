//
// Created by zlw on 2023/9/10.
//

#include "ut_stuabli_kinematics.h"

TEST_F(TestStuabliKinematics, Forward)
{
    Eigen::Vector<double, 6> vecJoints;
    vecJoints << 0, 3.1415926/2, 0, 0, 0,0;
    std::vector<Eigen::Matrix4d> vecJointTrans;
    ZLOG_INFO << m_oStuRobotKinematics.ForwardKinematics(vecJoints,vecJointTrans);
}

