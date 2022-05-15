//
// Created by wei on 2022/5/12.
//

#ifndef NEWTRAVEL_MATH_LINEAR_ALGEBRA_H
#define NEWTRAVEL_MATH_LINEAR_ALGEBRA_H

#include "Math/math_rotation.h"
#include "Math/math_vector3d.h"

template <typename T> T Mean(T tSrc_1, T tSrc_2, T tSrc_3, T tSrc_4)
{
    return (tSrc_1 - tSrc_2) * (tSrc_3 - tSrc_4);
}

Rotation Cov(std::vector<Vector3D> &vSrc_1)
{
    int iSize = vSrc_1.size();
    double tMean_1 = 0.0;
    double tMean_2 = 0.0;
    double tMean_3 = 0.0;
    for (int jj = 0; jj < iSize; jj++)
    {
        tMean_1 = tMean_1 + vSrc_1[jj].X();
        tMean_2 = tMean_2 + vSrc_1[jj].Y();
        tMean_3 = tMean_3 + vSrc_1[jj].Z();
    }
    tMean_1 = tMean_1 / iSize;
    tMean_2 = tMean_2 / iSize;
    tMean_3 = tMean_3 / iSize;
    Rotation oRation;
    for (int ij = 0; ij < iSize; ++ij)
    {
        oRation[0][0] = Mean(vSrc_1[ij].X(), tMean_1, vSrc_1[ij].X(), tMean_1) + oRation[0][0];
        oRation[0][1] = Mean(vSrc_1[ij].X(), tMean_1, vSrc_1[ij].Y(), tMean_2) + oRation[0][1];
        oRation[0][2] = Mean(vSrc_1[ij].X(), tMean_1, vSrc_1[ij].Z(), tMean_3) + oRation[0][2];
        oRation[1][0] = Mean(vSrc_1[ij].Y(), tMean_2, vSrc_1[ij].X(), tMean_1) + oRation[1][0];
        oRation[1][1] = Mean(vSrc_1[ij].Y(), tMean_2, vSrc_1[ij].Y(), tMean_2) + oRation[1][1];
        oRation[1][2] = Mean(vSrc_1[ij].Y(), tMean_2, vSrc_1[ij].Z(), tMean_3) + oRation[1][2];
        oRation[2][0] = Mean(vSrc_1[ij].Z(), tMean_3, vSrc_1[ij].X(), tMean_1) + oRation[2][0];
        oRation[2][1] = Mean(vSrc_1[ij].Z(), tMean_3, vSrc_1[ij].Y(), tMean_2) + oRation[2][1];
        oRation[2][2] = Mean(vSrc_1[ij].Z(), tMean_3, vSrc_1[ij].Z(), tMean_3) + oRation[2][2];
    }
    return oRation/(iSize - 1);
}


Matrix Householder(Vector<double> &vecData)
{
    int iSize = vecData.Size();
    Vector<double> vec_e(iSize);
    double dSigma = vecData.Norm2();
    if (vecData[0] < 0.0)
    {
        dSigma = dSigma * (-1);
    }
    vec_e[0] = dSigma;
    Vector<double> vec_nu = vecData + vec_e;
    Matrix oMatResult(iSize,iSize);
    oMatResult.SetEye();
    Matrix oMat(iSize,iSize);
    oMat.Dot(vec_nu,vec_nu);
    oMat.Dot(2/pow(vec_nu.Norm2(),2));
    auto aTemp = oMatResult - oMat;
    return aTemp;
}

Rotation GetOBBDirectionVector(Rotation &rotData)
{
    VectorD3 ovd3 = rotData.GetColVector(0);
    Matrix oMat_0 = Householder(ovd3.GetVectorValue());
    Matrix oMat_1 = oMat_0 *rotData.GetMatValue();
    Vector<double> vecTemp = oMat_1.GetColVector(1,1);
    Matrix oMat_2 = Householder(vecTemp);
    Rotation rotRot;
    rotRot.CombinationTransformMatrix(oMat_2);
    return rotData;
}


#endif // NEWTRAVEL_MATH_LINEAR_ALGEBRA_H
