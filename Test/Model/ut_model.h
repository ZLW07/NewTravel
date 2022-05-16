//
// Created by wei on 2022/4/19.
//

#ifndef NEWTRAVEL_UT_MODEL_H
#define NEWTRAVEL_UT_MODEL_H

#include "gtest/gtest.h"
#include "Model/model_data.h"

class TestModel : public ::testing::Test
{
public:
    TestModel(){};
    ~TestModel(){};
private:
};

TEST_F(TestModel,ReadMode)
{
    std::vector<ModelDataBase>  vecJoint1;
    ModelManager oMod;
//    bool bReadJoint1 = oMod.LoadModelData("../../Data/RobotModel/TX2-60L FOREARM.STL",vecJoint1);
//    EXPECT_TRUE(bReadJoint1);
//    Vector3D v3dPoint(35,0,-1);
//    ModelManager oModelManager;
////    CollisionDectionData oCollisionData  = oModelManager.GetModelDataVector(v3dPoint,vecJoint1);
////    bool bCollisionFlag = oModelManager.IsColliding(oCollisionData);
////    ZLOG << " data size is " << vecJoint1.size();
////    ZLOG << " bCollisionFlag  is " << bCollisionFlag;
}

TEST_F(TestModel, OBB)
{
    std::vector<Vector3D> vecSrc;
    Vector3D v3d(3.7,1.7,3.5);
    vecSrc.push_back(v3d);
    v3d.Clear();
    v3d = {4.1,3.8,5.2};
    vecSrc.push_back(v3d);
    v3d.Clear();
    v3d = { 4.7,2.9,2.1};
    vecSrc.push_back(v3d);
    v3d.Clear();
    v3d = {  5.2,2.8,6.0};
    vecSrc.push_back(v3d);
    v3d.Clear();
    ModelManager oMod;
    ModelDataBase oModelData;
    oModelData.vecPoint = vecSrc;
    auto aOBB = oMod.GetModelDataVector(oModelData);
    ZLOG << aOBB.v3dCenterPoint;            //    Vector3D: {4.59274, 3.22698, 4.07488}
    ZLOG << aOBB.v3dOBBLength;      //   Vector3D: {1.45647, 0.97438, 1.44308}
}

TEST_F(TestModel, CollisionDetection)
{


}
#endif // NEWTRAVEL_UT_MODEL_H
