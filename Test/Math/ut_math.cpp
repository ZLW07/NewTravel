//
// Created by zw on 2021/10/16.
//
#include "Math/math_matrix.h"
#include "Math/math_vector3d.h"
#include "Log/log.h"
#include <iostream>

int main()
{
    Matrix oMatrix(3,3);
    oMatrix[2][0] = 10.7;
    ZLOG << oMatrix[2][0];
    Vector<double> vec(3);
    Vector3D oVector3{1,2,3};
    auto aResult = oVector3.GetSkewSymmetricMatrix();
    ZLOG << aResult[0][1];
    ZLOG << oMatrix;
    ZLOG << aResult;
    ZLOG << (oMatrix + aResult);
    ZLOG << vec;
}
