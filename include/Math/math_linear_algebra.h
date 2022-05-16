//
// Created by wei on 2022/5/12.
//

#ifndef NEWTRAVEL_MATH_LINEAR_ALGEBRA_H
#define NEWTRAVEL_MATH_LINEAR_ALGEBRA_H

#include "Math/math_rotation.h"
#include "Math/math_vector3d.h"

Matrix Householder(Vector<double> &vecData)
{
    int iSize = vecData.Size();
    Matrix oMatResult(iSize,iSize);
    if (1 ==iSize)
    {
        oMatResult[0][0] = -1;
        return oMatResult;
    }
    Vector<double> vec_e(iSize);
    double dSigma = vecData.Norm2();
    if (vecData[0] < 0.0)
    {
        dSigma = dSigma * (-1);
    }
    vec_e[0] = dSigma;
    Vector<double> vec_nu = vecData + vec_e;
    oMatResult.SetEye();
    Matrix oMat(iSize,iSize);
    oMat.Dot(vec_nu,vec_nu);
    oMat.Dot(2/pow(vec_nu.Norm2(),2));
    oMatResult = oMatResult - oMat;
    return oMatResult;
}

Rotation GetOBBDirectionVector(Rotation &rotData)
{
    VectorD3 ovd3 = rotData.GetColVector(0);
    Matrix oMat_H1 = Householder(ovd3.GetVectorValue());
    Matrix oMat_H1A1 = oMat_H1 * rotData.GetMatValue();
    Vector<double> vecTemp = oMat_H1A1.GetColVector(1,1);
    Matrix oMat_H2 = Householder(vecTemp);
    Rotation rotRot_H2;
    rotRot_H2.CombinationTransformMatrix(oMat_H2);
    oMat_H1A1 = rotRot_H2.GetMatValue() * oMat_H1A1;
    vecTemp = oMat_H1A1.GetColVector(2,2);
    Matrix oMat_H3 = Householder(vecTemp);
    Rotation rotRot_H3;
    rotRot_H3.CombinationTransformMatrix(oMat_H3);
    Rotation rot_Q;
    Matrix oMat = rotRot_H3.GetMatValue() * rotRot_H2.GetMatValue() * oMat_H1;
    rot_Q.ConversionMatToRot(oMat);
    return rot_Q;
}


#endif // NEWTRAVEL_MATH_LINEAR_ALGEBRA_H
