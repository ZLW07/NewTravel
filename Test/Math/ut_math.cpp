//
// Created by zw on 2021/10/16.
//
#include "Math/math_matrix.h"
#include "Math/math_vector3d.h"
#include "Math/math_transfromation_matrix.h"
#include "Log/log.h"
#include <iostream>
#include "Model/model_data.h"

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
    TransformMatrix tranMat;
    TransformMatrix tranMat1;
    tranMat1[3][3] = 2;
    TransformMatrix tranMat2 = tranMat * tranMat1;
    ZLOG << tranMat2;
    Vector<double> v1 = tranMat.GetColVector(3);
    Vector<double> v2 = tranMat.GetColVector(3);
    Vector<double> v3 = vec;

    ZLOG << v3;
    double ddd = v1 * v2;
    ZLOG << ddd;
    ZLOG << tranMat[3][3];
    Vector3D v3dVec;
    ZLOG << v3dVec;

    double dData1 = 10.2;
    const int &iData = dData1;
    ZLOG << iData;
    dData1 = 2.1e02;
    ZLOG << iData;
    const int &iData1 = 10;
    const double &dData2 = dData1 + 120.2;
    std::string sData = "1.2e+03";
    double dData3 = std::atof(sData.c_str());
    ZLOG << dData3;

    Vector3D v3dData1{1,0,0};
    Vector3D v3dData2{0,1,0};
    auto Result = v3dData1.GetVectorAngleDeg(v3dData2);
    ZLOG << Result;
}
