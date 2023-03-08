//
// Created by wei on 2022/4/19.
//

#ifndef NEWTRAVEL_UT_MODEL_H
#define NEWTRAVEL_UT_MODEL_H

#include <fstream>

#include "Model/model_data.h"
#include "Log/log.h"
#include "gtest/gtest.h"

namespace zl
{
class TestModel : public ::testing::Test
{
public:
    TestModel(){};
    ~TestModel(){};

private:
};

TEST_F(TestModel, OBB_OBBE)
{
    std::vector<Vector3D> vecSrc;
    Vector3D v3d(1, 0, 0);
    vecSrc.push_back(v3d);
    v3d = {2, 0, 0};
    vecSrc.push_back(v3d);
    v3d = {1, 1, 0};
    vecSrc.push_back(v3d);
    v3d = {2, 1, 0};

    vecSrc.push_back(v3d);
    v3d = {1, 0, 3};
    vecSrc.push_back(v3d);
    v3d = {2, 0, 3};
    vecSrc.push_back(v3d);
    v3d = {1, 1, 3};
    vecSrc.push_back(v3d);
    v3d = {2, 1, 3};
    vecSrc.push_back(v3d);
    auto aOBB = ModelManager::GetOBBData(vecSrc);
    ZLOG << aOBB.v3dCenterPoint; //   Vector3D: {1.5, 0.5, 1.5}
    ZLOG << aOBB.v3dOBBLength;   //   Vector3D: {0.5, 0.5, 1.5}
    ZLOG << aOBB.rotBaseVector;  //{-1 0 0} {0 -1 0} {0 0 -1}
}

TEST_F(TestModel, CollisionDetectionE)
{
    OBBElement oOBBA;
    Rotation rotRot;
    rotRot.IdentityMatrix();
    Vector3D v3dCenterPoint{1.5, 0.5, 1.5};
    Vector3D v3dLength{0.5, 0.5, 0.5};
    oOBBA.rotBaseVector = rotRot;
    oOBBA.v3dOBBLength = v3dLength;
    oOBBA.v3dCenterPoint = v3dCenterPoint;

    OBBElement oBBB;
    oBBB = oOBBA;
    ModelManager oMod;
    Vector3D v3d{0, 0, 1.01};
    Matrix4 transPose(rotRot, v3d);
    auto bResult = oMod.IsColliding(oOBBA, oBBB, transPose,0.009);
    ZLOG << "bResult " << bResult;
}

TEST_F(TestModel, ModelCollisionDetectionE)
{
    ModelManager oMod;
    ModelDataElement oModelDataElement1;
    OBBElement oOBBElement1;
    ZLOG << oMod.LoadModelData(
        "/home/wei/CLionProjects/NewTravel/Data/RobotModel/1.STL", oModelDataElement1, oOBBElement1);
    ZLOG << oOBBElement1.v3dCenterPoint;
    ZLOG << oOBBElement1.v3dOBBLength;
    ModelDataElement oModelDataElement2;
    OBBElement oOBBElement2;
    ZLOG << oMod.LoadModelData(
        "/home/wei/CLionProjects/NewTravel/Data/RobotModel/2.STL", oModelDataElement2, oOBBElement2);
    Rotation rotRot;
    rotRot.IdentityMatrix();
    Vector3D v3d{0, 0, 0.4};
    Matrix4 transPose(rotRot, v3d);
    ZLOG << "==============: start ";
    auto bResult = oMod.IsColliding(oOBBElement1, oOBBElement2, transPose);
    ZLOG << "==============: end: " << bResult ;
}

TEST_F(TestModel, PQPModel)
{
    ModelDataElement oModelDataElement1;
    OBBElement oOBBElement1;
    ZLOG << ModelManager::LoadModelData(
        "/home/wei/CLionProjects/NewTravel/Data/RobotModel/1.STL", oModelDataElement1, oOBBElement1);
    auto Points = oModelDataElement1.TriangularPointCloud();
    auto oModel = ModelManager::BuildPQPModel(Points);
    ZLOG << "The bv size is " << oModel.num_bvs;
    for (int ii = 0; ii < 1; ++ii)
    {
        ZLOG << oModel.b[ii].d[0] << "; " << oModel.b[ii].d[1] << "; " << oModel.b[ii].d[2];
        ZLOG << oModel.b[ii].To[0] << "; " << oModel.b[ii].To[1] << "; " << oModel.b[ii].To[2];
    }

}
}
#endif // NEWTRAVEL_UT_MODEL_H
