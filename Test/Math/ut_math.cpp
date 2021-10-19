//
// Created by zw on 2021/10/16.
//
#include "Math/math_matrix.h"
#include "Math/math_vector3d.h"
#include <iostream>

int main()
{
        Matrix oMatrix(2,3,2);
        std::cout << oMatrix << std::endl;
        Matrix oMatrix1(3, 2, 10.0);
//        ZLOG << oMatrix[0][0];
//        ZLOG << oMatrix1[2][0];
//        ZLOG <<  oMatrix1.Norm2();
        Matrix oMat = oMatrix * oMatrix1;
        oMatrix = oMat;
        ZLOG << oMat;
//
//    Vector3D oVec3D(1.0, 0, 0);
//    Vector3D oVec3D1(0.0, 1, 0);
//    std::cout << oVec3D << std::endl;
//    std::cout << " norm " << oVec3D.Nom2();
    //    VectorD3 oVecD3(1.0,2.0,3.0);
    //    Vector3D oMat = oVec3D.GetVectorCross(oVec3D1);
    //    std::cout << " norm " << oMat;
//        Vector3D oExpend = oVec3D + oVec3D1;
//        std::cout << oExpend;
    //    std::cout << oVecD3 << std::endl;
    //    Matrix oMatt = oVec3D.GetSkewSymmetric();
    //    std::cout << oMatt << std::endl;
    //    double dResult = oVecD3 * oVec3D;
    //    ZLOG << "dResult " << dResult;

    return 0;
}
