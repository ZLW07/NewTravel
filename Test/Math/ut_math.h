//
// Created by wei on 2022/4/19.
//

#ifndef NEWTRAVEL_UT_MATH_H
#define NEWTRAVEL_UT_MATH_H

#include "Log/log.h"
#include "Math/math_matrix.h"
#include "Math/math_transfromation_matrix.h"
#include "Math/math_rotation.h"
#include "Math/math_vector3d.h"
#include "Math/math_linear_algebra.h"
#include <iostream>

#include "gtest/gtest.h"

class TestMath : public ::testing::Test
{
public:
    TestMath() = default;
    ~TestMath() {}

private:
};

TEST_F(TestMath, TestVector3DOperate)
{
    TransformMatrix oTran;
    Vector3D v3dData1(1, 0, 0);
    Vector3D v3dData2(0, 1, 0);
    Vector3D v3dData3(0, 0, 1);
    EXPECT_EQ(0, v3dData1.Dot(v3dData2));
    EXPECT_EQ(1, v3dData1.Cross(v3dData2)[2]);
    EXPECT_FLOAT_EQ(90, v3dData1.GetVectorAngleDeg(v3dData2));
}

TEST_F(TestMath, TestTransForm)
{
    Vector3D v3dData1(1, 0, 0);
    Vector3D v3dData2(0, 1, 0);
    Vector3D v3dData3(0, 0, 1);
    Vector3D v3dData4(1, 3, 1);
    Vector3D v3dData5(1, 0, 0);
    Rotation rotData(v3dData1, v3dData2, v3dData3);
    TransformMatrix oTrans(rotData, v3dData5);
    ZLOG << oTrans;
    Vector3D v3dResult = oTrans * v3dData4;
    ZLOG << v3dResult;

    Matrix oMat(2,2);
    oMat[0][1] = 1.0;
    oMat[1][1] = 1.0;
    ZLOG << rotData;
    rotData.CombinationTransformMatrix(oMat);
    ZLOG << rotData;
}

TEST_F(TestMath, TestOBB)
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
    for (int ii = 0; ii < vecSrc.size(); ++ii)
    {
        ZLOG << vecSrc.at(ii);
    }
    Rotation rot = Cov(vecSrc);
    ZLOG << rot;

    Vector<double> vData(3);
    vData[0] = 2;
    vData[1] = 1;
    vData[2] = 2;
    auto Result = Householder(vData);
    ZLOG << Result;
}

#endif // NEWTRAVEL_UT_MATH_H
