//
// Created by zw on 2021/10/21.
//

#ifndef NEWTRAVEL_UT_MATH_H
#define NEWTRAVEL_UT_MATH_H

#include "gtest/gtest.h"

#include "Math/math_matrix.h"
#include "Math/math_matrix_rotate.h"
#include "Math/math_se3mat.h"
#include "Math/math_vector3d.h"
#include "Math/math_six_axis_vec6d.h"
#include "Math/math_six_axis.h"

class MathTest : public ::testing::Test
{
public:
    MathTest();
    ~MathTest();

private:
};

MathTest::MathTest(){}

MathTest::~MathTest(){}

TEST_F(MathTest, CoutMatrix)
{
    Matrix oMatrix(2, 3, 2);
    std::cout << oMatrix << std::endl;
}

TEST_F(MathTest, MatrixNorm)
{
    Matrix oMatrix1(3, 2, 10.0);
    ZLOG << oMatrix1.Norm2();
}

TEST_F(MathTest, MatrixMultiplication)
{
    Matrix oMatrix(2, 3, 2);
    Matrix oMatrix1(3, 2, 10.0);
    Matrix oMat = oMatrix * oMatrix1;
    Matrix oMatrix2(3, 2, 10.0);
    ZLOG << oMat;
}

TEST_F(MathTest, Vec6DToSe3)
{
    Vector6D oVec6D(1, 2, 3, 4, 5, 6);
    Se3Matrix oMatV6D2Se3;
    oMatV6D2Se3 = Get6DToSe3(oVec6D);
    std::cout << oMatV6D2Se3 << std::endl;
}

TEST_F(MathTest, Vec3DNorm)
{
    Vector3D oVec3D1(0.0, 1, 0);
    std::cout << " norm2 " << oVec3D1.Norm2();
}

TEST_F(MathTest, Vec3DCross)
{
    Vector3D oVec3D(1.0, 0, 0);
    Vector3D oVec3D1(0.0, 1, 0);
    Vector3D oMat = oVec3D.GetVectorCross(oVec3D1);
    std::cout << " VectorCross-Product Value  " << oMat;
}

TEST_F(MathTest, Vec3DSkewSymmetric)
{
    Vector3D oVec3D(1.0, 0, 0);
    RotateMat oMat = oVec3D.GetSkewSymmetric();
    std::cout << " SkewSymmetric Value  " << oMat;
}

TEST_F(MathTest, VecD3Product)
{
    Vector3D oVec3D(1.0, 0, 0);
    VectorD3 oVecD3(1.0, 0, 0);
    double dValue = oVecD3 * oVec3D;
    std::cout << " VecD3Product Value  " << dValue;
}

TEST_F(MathTest, ScrewAxis)
{
    Vector3D oW(0, 0, 1);
    Vector3D oQ(3, 3, 0);
    Vector6D oS = oW.GetScrewAxis(oQ, oW, 2); //(0,0,-1,0,-3,2)
    std::cout << " ScrewAxis Value  " << oS;
}

TEST_F(MathTest, RotateExp3)
{
    Vector3D oVec3D(1, 2, 3);
    RotateMat oMat = oVec3D.GetSkewSymmetric();
    oMat = oMat.GetMatrixExp3();
    /*
        -0.6949    0.7135    0.0893
        -0.1920   -0.3038    0.9332
        0.6930    0.6313    0.3481
     */
    std::cout << oMat << std::endl;
}

TEST_F(MathTest, Se3Exp6)
{
    Vector3D oVec3D(1.5708, 0, 0);
    RotateMat oMat = oVec3D.GetSkewSymmetric();
    Vector3D oVecP(0, 2.3562, 2.3562);
    Se3Matrix oSe3(oMat, oVecP);
    oSe3[3][3] = 0.0;
    Axis6Se3 oAxis6Se3;
    Se3Matrix oSe3Result = oAxis6Se3.GetMatrixExp6(oSe3);
    /*
       1.0000         0         0         0
         0            0.0000   -1.0000   -0.0000
         0            1.0000    0.0000    3.0000
         0             0         0       1.0000
     */
        std::cout << oSe3Result << std::endl;
}

TEST_F(MathTest, SixAxisArray)
{
    Vector6D oVec6D(1, 2, 3, 4, 5, 6);
    SixAxisVec6DArray oSixAxisVec6DAry;
    oSixAxisVec6DAry.PushBack(oVec6D);
    oSixAxisVec6DAry.PushBack(oVec6D);
    ZLOG << oSixAxisVec6DAry;
}

TEST_F(MathTest, Axis6Math)
{
    Vector6D oVec6D1(0, 0, 1, 4, 0,    0);
    Vector6D oVec6D2(0, 0, 0, 0, 1,    0);
    Vector6D oVec6D3(0, 0, -1, -6, 0,    -0.1);
    SixAxisVec6DArray oSixAxisVec6DAry;
    oSixAxisVec6DAry.PushBack(oVec6D1);
    oSixAxisVec6DAry.PushBack(oVec6D2);
    oSixAxisVec6DAry.PushBack(oVec6D3);
    Vector6D oVec6DTheta(1.5708,3.000000,3.1415926,0.0,0.0,0.0);
    RotateMat oRat(1);
    oRat[0][0] = -1;
    oRat[2][2] = -1;
    Vector3D oV3d(0,6,2);
    Se3Matrix oSe3(oRat,oV3d);
    Axis6Se3 oAxis6;
    oAxis6.GetKinSpace(oSe3,oSixAxisVec6DAry,oVec6DTheta);
    /*  expect result:
     * -0.0000    1.0000         0          -5.0000
     *  1.0000    0.0000         0          4.0000
     *  0         0             -1.0000     1.6858
     *  0         0             0           1.0000
     */
    ZLOG << oSe3;
}


#endif // NEWTRAVEL_UT_MATH_H
