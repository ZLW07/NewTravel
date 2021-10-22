//
// Created by zw on 2021/10/19.
//

#include "Math/math_se3mat.h"

std::ostream &operator <<(std::ostream &out, Se3Matrix &oSe3Matrix)
{
    return out << oSe3Matrix.m_oMat4;
}

Se3Matrix::Se3Matrix(): m_oMat4(4,4){}

Se3Matrix::Se3Matrix(const Se3Matrix &oSe3Mat):m_oMat4(4,4)
{
    for (int ii = 0; ii < 4; ii++)
    {
        for (int jj = 0; jj < 4; jj++)
        {
            (*this)[ii][jj] = oSe3Mat[ii][jj];
        }
    }
}


Se3Matrix::Se3Matrix(RotateMat oRotateMat, Vector3D oPose): m_oMat4(4,4)
{
    for (int ii = 0; ii < 3; ii++)
    {
        for (int jj = 0; jj < 3; jj++)
        {
            (*this)[ii][jj] = oRotateMat[ii][jj];
        }
        (*this)[ii][3] = oPose[ii];
    }
    (*this)[3][3] = 1.0;
}

Se3Matrix Se3Matrix::GetMatrixExp6()
{
    RotateMat oRotate = (*this).GetRotMatrix();
    Vector3D oVecAix = oRotate.GetScrewAxis();
    double dNormValue = oVecAix.Norm2();
    Vector3D oPose = (*this).GetTranslation();
    if (NearZero(dNormValue))
    {
        RotateMat oEye(1);
        Se3Matrix oSe3New(oEye,oPose);
        return oSe3New;
    }
    double dTheta = oVecAix.GetAxisAng3();
    RotateMat oRateW = oRotate;
    oRotate/dTheta;
    RotateMat oRotateMat = oRateW.GetMatrixExp3();
    RotateMat oRotEye(1);
    oRotEye = oRotEye * dTheta;
    double dTemp1 = 1 - cos(dTheta);
    RotateMat oTemp2 = oRotate * dTemp1;
    double dTemp3 = dTheta - sin(dTheta);
    RotateMat oTemp4 = oRotate * oRotate * dTemp3;
    RotateMat oTemp5 = oRotEye + oTemp2 + oTemp4;
    oPose/dTheta;
    Vector3D oV3D = oTemp5 * oPose;
    Se3Matrix oSe3Mat(oRotateMat,oV3D);
    return  oSe3Mat;
}

double* Se3Matrix::operator[](const int iIndex) const
{
    return m_oMat4[iIndex];
}

Vector3D Se3Matrix::GetScrewAxis(Se3Matrix &oMat4)
{
    Vector3D oVec3D;
    return oVec3D;
}

RotateMat Se3Matrix::GetRotMatrix()
{
    RotateMat oMat3;
    for (int ii = 0; ii < 3; ii++)
    {
        for (int jj = 0; jj < 3; jj++)
        {
            oMat3[ii][jj] = (*this)[ii][jj];
        }
    }

    return oMat3;
}

Vector3D Se3Matrix::GetTranslation()
{
    Vector3D oVec3D;
    for (int ii = 0; ii < 3; ii++)
    {
        oVec3D[ii] = (*this)[ii][3];
    }
    return oVec3D;
}
