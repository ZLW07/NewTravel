//
// Created by wei on 2023/5/11.
//

#include "ut_collision_detection.h"

TEST_F(TestCollision, Test1)
{
    std::vector<Eigen::Matrix4d> outJointTrans;
    Eigen::Matrix<double, 6, 6> oSlist;
    oSlist << 0, 0, 0, 0, 0, 0,
              0, 1, 1, 0, 1, 0,
              1, 0, 0, 1, 0, 1,
             0, -375, -775, 20, -1225, 20,
             0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0;

    Eigen::Vector<double, 6> vecTheta;
    /*vecTheta << M_PI * 112.87 / 180, M_PI * (-59.79 + 90) / 180, M_PI * (210.65 - 90) / 180, M_PI * (-160.15) / 180,
        M_PI * 64.14 / 180, M_PI * (-81.19) / 180;*/
    Eigen::Matrix4d InitTransform;
    InitTransform << 1, 0, 0, 0,
        0, 1, 0, 20,
        0, 0, 1, 1295,
        0, 0, 0, 1;
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
    vecTheta << 0, 0, M_PI , 0, 0, 0;
    ZLOG << oCollisionDetection.IsCollision(vecTheta);
}

TEST_F(TestCollision, IsCollision1)
{
    PQP_Model *p2 = new PQP_Model();
    zl::ModelManager::BuildPQPModel(
        p2, "../../Data/RobotModel/2.STL");
    PQP_Model *p3 = new PQP_Model();

    zl::ModelManager::BuildPQPModel(
        p3, "../../Data/RobotModel/7.STL");

    PQP_REAL R1[3][3], R2[3][3], T1[3], T2[3];

    R1[0][0] = 1.0;
    R1[0][1] =R1[0][2] = 0.0;

    R1[1][0] = R1[1][1] = 0.0;
    R1[1][2] = -1;

    R1[2][0] = R2[2][2] = 0.0;
    R1[2][1] = 1.0;


    R2[0][0] = R2[1][1] = R2[2][2] = 1.0;
    R2[0][1] = R2[1][0] = R2[2][0] = 0.0;
    R2[0][2] = R2[1][2] = R2[2][1] = 0.0;

    T1[0] = 0.0;
    T1[1] = 375;
    T1[2] = 0.0;

    T2[0] = 0.0;
    T2[1] = 255.0;
    T2[2] = 0.0;

    PQP_CollideResult cres;
    PQP_Collide(
        &cres, R1, T1, p2, R2, T2, p3, PQP_FIRST_CONTACT);

    PQP_ToleranceResult tres;
    PQP_REAL tolerance = (PQP_REAL)0.01;
    PQP_Tolerance(&tres, R1, T1, p2, R2, T2, p3, tolerance);
    ZLOG_INFO << cres.Colliding();
    ZLOG_INFO << tres.Distance();
}
