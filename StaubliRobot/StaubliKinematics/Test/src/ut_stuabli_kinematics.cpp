//
// Created by zlw on 2023/9/10.
//

#include "ut_stuabli_kinematics.h"
namespace zl
{
TEST_F(TestStuabliKinematics, Forward)
{
    Eigen::Vector<double, 6> vecJoints;
    vecJoints << 0, 0, 0, 0, 0, 0;
    std::vector<Eigen::Matrix4d> vecJointTrans;
    ZLOG_INFO << m_oStuRobotKinematics.ForwardKinematics(vecJoints, vecJointTrans);

    Eigen::Vector<double, 6> vecPara1={-1.27122, 1.34242, 1.0289, 1.31863, -1.91867, -0.337958};
    ZLOG_INFO <<"\n" << m_oStuRobotKinematics.ForwardKinematics(vecPara1, vecJointTrans);
}

TEST_F(TestStuabliKinematics, IKward)
{
    Eigen::Matrix4d oTarget;
    oTarget << -0.2454, 0.3839, -0.8902, 0.164249,
        -0.5413, -0.8160, -0.2027, -0.6799430,
        -0.8041, 0.4321, 0.4080,-0.203854,
        0, 0, 0, 1;
    auto oResult = m_oStuRobotKinematics.IKinSpace(oTarget);
    for (int ii = 0; ii < oResult.size(); ++ii)
    {
        std::cout << "The resutl is: ";
        for (int ij = 0; ij < oResult.at(ii).size(); ++ij)
        {
            std::cout << oResult.at(ii).at(ij) <<", " ;
        }
        std::cout <<"\n";
    }
}
} // namespace zl
