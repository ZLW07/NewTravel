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
    bool bReadJoint1 = oMod.LoadModelData("../../Data/RobotModel/1.STL",vecJoint1);
    EXPECT_TRUE(bReadJoint1);
    ZLOG << " data size is " << vecJoint1.size();
}

#endif // NEWTRAVEL_UT_MODEL_H
