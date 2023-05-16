//
// Created by wei on 2023/5/11.
//

#include "ut_collision_detection.h"

TEST_F(TestCollision, Test1)
{
    std::vector<Eigen::Matrix4d> outJointTrans;
    Eigen::Matrix<double, 6, 6> oSlist;
    oSlist << 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, -375, -775, 20, -1225, 20, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0;

    Eigen::Vector<double, 6> vecTheta;
    /*vecTheta << M_PI * 112.87 / 180, M_PI * (-59.79 + 90) / 180, M_PI * (210.65 - 90) / 180, M_PI * (-160.15) / 180,
        M_PI * 64.14 / 180, M_PI * (-81.19) / 180;*/
    Eigen::Matrix4d InitTransform;
    InitTransform << 1, 0, 0, 0, 0, 1, 0, 20, 0, 0, 1, 1295, 0, 0, 0, 1;
    auto result = zl::Kinematics::FKinSpace(outJointTrans, InitTransform, oSlist, vecTheta);
    for (int ii = 0; ii < outJointTrans.size(); ++ii)
    {
        ZLOG_INFO << ii << "\n" << outJointTrans.at(ii);
    }
    ZLOG_INFO << "\n" << result;
    PQP_Model pPQP_Model;
}

TEST_F(TestCollision, IsCollision)
{
    zl::CollisionDetection oCollisionDetection;
    Eigen::Vector<double, 6> vecTheta;
/*    vecTheta << M_PI * 0 / 180, M_PI * (0 + 90) / 180, M_PI * (166.08 - 90) / 180, M_PI * (0) / 180,
        M_PI * 108.4 / 180, M_PI * (0) / 180;*/
    vecTheta << M_PI *0 / 180, M_PI * (0) / 180, M_PI * (180) / 180, M_PI * (0) / 180,
        M_PI * 0 / 180, M_PI * (0) / 180;
    ZLOG << oCollisionDetection.IsCollision(vecTheta);
}