//
// Created by zlw on 2023/9/10.
//

#include "ut_stuabli_kinematics.h"
namespace zl
{
TEST_F(TestStuabliKinematics, Forward)
{
    Eigen::Vector<double, 6> vecJoints;
    vecJoints << 0, 3.1415926 / 2, 0, 0, 0, 0;
    std::vector<Eigen::Matrix4d> vecJointTrans;
    ZLOG_INFO << m_oStuRobotKinematics.ForwardKinematics(vecJoints, vecJointTrans);
}

TEST_F(TestStuabliKinematics, IKward)
{
    Eigen::Matrix4d oTarget;
    oTarget << -0.2454, 0.3839, -0.8902, 0.164249, -0.5413, -0.8160, -0.2027, -0.6799430, -0.8041, 0.4321, 0.4080,
        -0.203854, 0, 0, 0, 1;
    m_oStuRobotKinematics.IKinSpace(oTarget);
}
} // namespace zl
