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
    bool bReadJoint1 = oMod.LoadModelData("../../Data/RobotModel/TX2-60L FOREARM.STL",vecJoint1);
    EXPECT_TRUE(bReadJoint1);
    Vector3D v3dPoint(35,0,-1);
    ModelManager oModelManager;
    CollisionDectionData oCollisionData  = oModelManager.GetModelDataVector(v3dPoint,vecJoint1);
    bool bCollisionFlag = oModelManager.IsColliding(oCollisionData);
    ZLOG << " data size is " << vecJoint1.size();
    ZLOG << " bCollisionFlag  is " << bCollisionFlag;
}

TEST_F(TestModel, CollisionDetection)
{
    ModelDataBase oModelDataBase;
    oModelDataBase.v3dCoordinate_1 = Vector3D(1,0,0);
    oModelDataBase.v3dCoordinate_2 = Vector3D(0,0,0);
    oModelDataBase.v3dCoordinate_3 = Vector3D(0,1,0);
    oModelDataBase.v3dNormalVector = Vector3D(0,0,1);
    std::vector<ModelDataBase> oModeData;
    oModeData.push_back(oModelDataBase);
    Vector3D v3dPoint1(0.001,0,0);
    ModelManager oModelManager;
    CollisionDectionData oCollisionData = oModelManager.GetModelDataVector(v3dPoint1,oModeData);
    bool bCheck = oModelManager.IsColliding(oCollisionData);
    ZLOG << "bCheck: " << bCheck;
    std::vector<ModelDataBase>  vecJoint1;
    bool bReadJoint1 = oModelManager.LoadModelData("../../Data/RobotModel/1.STL",vecJoint1);
    CollisionDectionData oCollisionData1 = oModelManager.GetModelDataVector(v3dPoint1,vecJoint1);
    ZLOG << oModelManager.IsColliding(oCollisionData1);

}
#endif // NEWTRAVEL_UT_MODEL_H
