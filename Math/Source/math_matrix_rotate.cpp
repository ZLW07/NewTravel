//
// Created by zw on 2021/10/20.
//

#include "Math/math_matrix_rotate.h"

std::ostream &operator<<(std::ostream &out, RotateMat &oRotateMat)
{
    return out << oRotateMat.m_oRateMat;
}

RotateMat::RotateMat() : m_oRateMat(3, 3) {}

RotateMat::RotateMat(int iEyeValue) : m_oRateMat(3, 3)
{
    for (int ii = 0; ii < 3; ii++)
    {
        (*this)[ii][ii] = iEyeValue;
    }
}

RotateMat::RotateMat(const RotateMat &oRotate) : m_oRateMat(3, 3)
{
    for (int ii = 0; ii < 3; ii++)
    {
        for (int jj = 0; jj < 3; jj++)
        {
            (*this)[ii][jj] = oRotate[ii][jj];
        }
    }
}

RotateMat::~RotateMat() {}

double *RotateMat::operator[](int iIndex) const
{
    return m_oRateMat[iIndex];
}

double RotateMat::Norm2()
{
    return m_oRateMat.Norm2();
}

Vector3D RotateMat::GetScrewAxis()
{
    Vector3D oVector3D;
    oVector3D[0] = (*this)[2][1];
    oVector3D[1] = (*this)[0][2];
    oVector3D[2] = (*this)[1][0];
    return oVector3D;
}

void RotateMat::operator/(double dData)
{
    double dTemp = 0.0;
    for (int ii = 0; ii < 3; ii++)
    {
        for (int jj = 0; jj < 3; jj++)
        {
            dTemp = (*this)[ii][jj]/dData;
            (*this)[ii][jj] = dTemp;
        }
    }
}

RotateMat RotateMat::operator+(RotateMat &oRot)
{
    for (int ii = 0; ii < 3; ii++)
    {
        for (int jj = 0; jj < 3; jj++)
        {
            (*this)[ii][jj] = (*this)[ii][jj] + oRot[ii][jj];
        }
    }
    return *this;
}

RotateMat RotateMat::operator*(double &dData)
{
    RotateMat oResult;
    for (int ii = 0; ii < 3; ii++)
    {
        for (int jj = 0; jj < 3; jj++)
        {
            oResult[ii][jj] = (*this)[ii][jj] * dData;
        }
    }
    return oResult;
}

RotateMat RotateMat::operator*(RotateMat &dData)
{
    RotateMat oResult;
    oResult.m_oRateMat = (this->m_oRateMat) * dData.m_oRateMat;
    return oResult;
}

Vector3D RotateMat::operator*(Vector3D &oVec3D)
{
    Vector3D oResult;
    double dValue = 0.0;
    for (int ii = 0; ii < 3; ii++)
    {
        for (int jj = 0; jj < 3; jj++)
        {
            dValue = (*this)[ii][jj] * oVec3D[jj] + dValue;
        }
        oResult[ii] = dValue;
    }
    return oResult;
}

RotateMat RotateMat::GetMatrixExp3()
{
    Vector3D oVec3D = GetScrewAxis();
    double dNormValue = oVec3D.Norm2();
    RotateMat oResultRot(1);
    if (NearZero(dNormValue))
    {
        return oResultRot;
    }
    double dTheta = oVec3D.GetAxisAng3();
    *this/dTheta;
    double dSin = sin(dTheta);
    RotateMat oRotMat0 = (*this) * dSin;
    double dTheta1 = 1 - cos(dTheta);
    RotateMat oRotMat1 = (*this) * (*this);
    oRotMat1 = oRotMat1 * dTheta1;
    oResultRot = oRotMat0 + oRotMat1 + oResultRot;
    return oResultRot;
}

