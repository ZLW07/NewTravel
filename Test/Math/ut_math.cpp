//
// Created by zw on 2021/10/16.
//
#include "Math/math_matrix.h"
#include "Math/math_matrix_rotate.h"
#include "Math/math_vector3d.h"
#include "Math/math_se3mat.h"
#include <iostream>

int main()
{
    //        Matrix oMatrix(2,3,2);
    //        std::cout << oMatrix << std::endl;
    //        Matrix oMatrix1(3, 2, 10.0);
    //        ZLOG << oMatrix[0][0];
    //        ZLOG << oMatrix1[2][0];
    //        ZLOG <<  oMatrix1.Norm2();
    //        Matrix oMat = oMatrix * oMatrix1;
    //        oMatrix = oMat;
    //        ZLOG << oMat;
    //    Vector6D oVec6D(1, 2, 3, 4, 5, 6);
    //    Matrix oMatV6D2Se3 = oVec6D.Get6DToSe3(oVec6D);
    //    std::cout << oMatV6D2Se3 << std::endl;
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

    // Vector6D oo(1,2,3,4,5,6);
    // std::cout << oo << std::endl;
    //    Vector3D oW(0,0,-1);
    //    Vector3D oQ(0.817,0.109,0.089);
    //    Vector6D oS = oW.GetScrewAxis(oQ,oW,0);
    //    std::cout << oS << std::endl;
//    Vector3D oVec3D(1, 2, 3);
//    RotateMat oMat = oVec3D.GetSkewSymmetric();
//    oMat = oMat.GetMatrixExp3();
//    std::cout << oMat << std::endl;
      Vector3D oVec3D(1.5708, 0, 0);
      RotateMat oMat = oVec3D.GetSkewSymmetric();
      Vector3D oVecP(0,2.3562,2.3562);
      Se3Matrix oSe3(oMat,oVecP);
      oSe3[3][3] = 0.0;
      Se3Matrix oMatSe3 = oSe3.GetMatrixExp6();
      std::cout << oMatSe3 << std::endl;
//      std::cout << 1111 << std::endl;
//      std::cout << 1111 << std::endl;
//      std::cout << 1111 << std::endl;
//      std::cout << 1111 << std::endl;
    return 0;
}
