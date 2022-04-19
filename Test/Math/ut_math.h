//
// Created by wei on 2022/4/19.
//

#ifndef NEWTRAVEL_UT_MATH_H
#define NEWTRAVEL_UT_MATH_H

#include "Math/math_matrix.h"
#include "Math/math_vector3d.h"
#include "Math/math_transfromation_matrix.h"
#include "Log/log.h"
#include <iostream>

#include "gtest/gtest.h"

class TestMath : public ::testing::Test
{
public:
    TestMath()= default;
    ~TestMath(){}
private:
};

TEST_F(TestMath,TestVector3DOperate)
{
    Vector3D v3dData1(1,0,0);
    Vector3D v3dData2(0, 1, 0);
    Vector3D v3dData3(0,0,1);
    EXPECT_EQ(0, v3dData1.Dot(v3dData2));
    EXPECT_EQ(1 ,v3dData1.Cross(v3dData2)[2]);
    EXPECT_FLOAT_EQ(90,v3dData1.GetVectorAngleDeg(v3dData2));
}



#endif // NEWTRAVEL_UT_MATH_H
