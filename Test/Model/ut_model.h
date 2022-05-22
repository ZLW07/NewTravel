//
// Created by wei on 2022/4/19.
//

#ifndef NEWTRAVEL_UT_MODEL_H
#define NEWTRAVEL_UT_MODEL_H

#include "Model/model_data.h"
#include "gtest/gtest.h"

class TestModel : public ::testing::Test
{
public:
    TestModel(){};
    ~TestModel(){};

private:
};

TEST_F(TestModel, ReadMode)
{
    ModelDataBase oModelData;
    OBBData oOBBData;
    ModelManager oMod;
    bool bReadJoint1 = oMod.LoadModelData("../../Data/RobotModel/TX2-60L FOREARM.STL", oModelData, oOBBData);
    ZLOG << " The size is  " << oModelData.vecPoint.size();
    EXPECT_TRUE(bReadJoint1);
}

TEST_F(TestModel, OBB)
{
    std::vector<Vector3D> vecSrc;
    Vector3D v3d(3.7, 1.7, 3.5);
    vecSrc.push_back(v3d);
    v3d.Clear();
    v3d = {4.1, 3.8, 5.2};
    vecSrc.push_back(v3d);
    v3d.Clear();
    v3d = {4.7, 2.9, 2.1};
    vecSrc.push_back(v3d);
    v3d.Clear();
    v3d = {5.2, 2.8, 6.0};
    vecSrc.push_back(v3d);
    v3d.Clear();
    ModelManager oMod;
    ModelDataBase oModelData;
    oModelData.vecPoint = vecSrc;
    auto aOBB = oMod.GetModelDataVector(oModelData);
    ZLOG << aOBB.v3dCenterPoint; //    Vector3D: {4.59274, 3.22698, 4.07488}
    ZLOG << aOBB.v3dOBBLength;   //   Vector3D: {1.45647, 0.97438, 1.44308}
}

TEST_F(TestModel, OBB_OBB)
{
    std::vector<Vector3D> vecSrc;
    Vector3D v3d(1, 0, 0);
    vecSrc.push_back(v3d);
    v3d.Clear();
    v3d = {2, 0, 0};
    vecSrc.push_back(v3d);
    v3d.Clear();
    v3d = {1, 1, 0};
    vecSrc.push_back(v3d);
    v3d.Clear();
    v3d = {2, 1, 0};
    vecSrc.push_back(v3d);
    v3d.Clear();
    v3d = {1, 0, 3};
    vecSrc.push_back(v3d);
    v3d.Clear();
    v3d = {2, 0, 3};
    vecSrc.push_back(v3d);
    v3d.Clear();
    v3d = {1, 1, 3};
    vecSrc.push_back(v3d);
    v3d.Clear();
    v3d = {2, 1, 3};
    vecSrc.push_back(v3d);
    v3d.Clear();
    ModelManager oMod;
    ModelDataBase oModelData;
    oModelData.vecPoint = vecSrc;
    auto aOBB = oMod.GetModelDataVector(oModelData);
    ZLOG << aOBB.v3dCenterPoint; //   Vector3D: {1.5, 0.5, 1.5}
    ZLOG << aOBB.v3dOBBLength;   //   Vector3D: {0.5, 0.5, 1.5}
    ZLOG << aOBB.rotBaseVector;  //{-1 0 0} {0 -1 0} {0 0 -1}
}

TEST_F(TestModel, CollisionDetection)
{
    OBBData oOBBA;
    Rotation rotRot;
    rotRot.SetEye();
    Vector3D v3dCenterPoint{1.5, 0.5, 1.5};
    Vector3D v3dLength{0.5, 0.5, 0.5};
    oOBBA.rotBaseVector = rotRot;
    oOBBA.v3dOBBLength = v3dLength;
    oOBBA.v3dCenterPoint = v3dCenterPoint;

    OBBData oBBB;
    oBBB = oOBBA;
    ModelManager oMod;
    Vector3D v3d{0, 0, 1.01};
    TransformMatrix transPose(rotRot, v3d);
    auto bResult = oMod.IsColliding(oOBBA, oBBB, transPose);
    ZLOG << "bResult " << bResult;
}
#endif // NEWTRAVEL_UT_MODEL_H
