//
// Created by wei on 2023/8/7.
//

#include "ut_staubli_kinematics.h"

TEST_F(TestStaubliKinematics, ForwardKinematics)
{
    std::vector<Eigen::Matrix4d> outJointTransForm;
    Eigen::Vector<double, 6> vecTheta;
    vecTheta << 112.87, -59.79, 210.65, -160.15, 64.14, -81.19;
    auto transEndLink = m_oStuRobotKinematics.ForwardKinematics(vecTheta, outJointTransForm,true);
    /****
        -0.94467    0.315908     -0.0883197   -0.187993
        -0.093647  -0.00169042    0.995604    0.449266
        0.31437    0.948788       0.0311808  -0.0451872
        0           0             0           1
    ****/
    ZLOG_INFO << "end trans is \n" << transEndLink;
}