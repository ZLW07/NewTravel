//
// Created by zw on 2021/10/16.
//
#include "Math/math_matrix.h"
#include "Math/math_vector3d.h"
#include <iostream>

int main()
{
    Matrix oMatrix(3);
    oMatrix[2][2] = 10;
    std::cout << oMatrix[2][2]<< std::endl;

    Vector3D oVector3{1,2,3};
    auto aResult = oVector3.GetSkewSymmetric();
    std::cout << aResult[0][1] << std::endl;
}
