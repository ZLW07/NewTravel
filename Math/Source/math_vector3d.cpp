////
//// Created by zw on 2021/10/16.
////
//
#include "Math/math_vector3d.h"
//

Vector3D::Vector3D() : m_oV3D(3, 1) {}

Vector3D::~Vector3D(){};

Vector3D::Vector3D(double dData1, double dData2, double dData3) : m_oV3D(3, 1)
{
    (*this)[0] = dData1;
    (*this)[1] = dData2;
    (*this)[2] = dData3;
}

Vector3D::Vector3D(const Vector3D &oVector3D) : m_oV3D(3, 1)
{
    for (int ii = 0; ii < 3; ii++)
    {
        (*this)[ii] = oVector3D[ii];
    }
}

std::ostream &operator<<(std::ostream &out, Vector3D &oVector3D)
{
    out << oVector3D.m_oV3D;
}

double &Vector3D::operator[](unsigned int iIndex) const
{
    return m_oV3D[iIndex][0];
}

double &Vector3D::operator*(const Vector3D &oVector3D)
{
    double dResult = 0.0;
    for (int ii = 0; ii < 3; ii++)
    {
        dResult = (*this)[ii] * oVector3D[ii] + dResult;
    }
    return dResult;
}

Vector3D &Vector3D::operator*(const double &dData)
{
    for (int ii = 0; ii < 3; ii++)
    {
        (*this)[ii] = (*this)[ii] * dData;
    }
    return *this;
}

void Vector3D::operator/(const double &dData)
{
    if (NearZero(dData))
    {
        return;
    }
    double  dTemp = 0.0;
    for (int ii = 0; ii < 3; ii++)
    {
        dTemp = (*this)[ii] / dData;
        (*this)[ii] = dTemp;
    }
}

Vector3D &Vector3D::operator+(const Vector3D &dData)
{
    for (int ii = 0; ii < 3; ii++)
    {
        (*this)[ii] = (*this)[ii] + dData[ii];
    }
    return *this;
}

Vector3D &Vector3D::GetVectorCross(const Vector3D &oVector3D)
{

    double dFirstValue = (*this)[1] * oVector3D[2];
    double dSecondValue = (*this)[2] * oVector3D[1];
    double dTemp0 = dFirstValue - dSecondValue;
    dFirstValue = (*this)[2] * oVector3D[0];
    dSecondValue = (*this)[0] * oVector3D[2];
    double dTemp1 = dFirstValue - dSecondValue;
    dFirstValue = (*this)[0] * oVector3D[1];
    dSecondValue = (*this)[1] * oVector3D[0];
    double dTemp2 = (dFirstValue - dSecondValue);
    (*this)[0] = dTemp0;
    (*this)[1] = dTemp1;
    (*this)[2] = dTemp2;
    return *this;
}

RotateMat Vector3D::GetSkewSymmetric()
{
    RotateMat oRotateMat;
    oRotateMat[0][1] = -(*this)[2];
    oRotateMat[0][2] = (*this)[1];

    oRotateMat[1][0] = (*this)[2];
    oRotateMat[1][2] = -(*this)[0];

    oRotateMat[2][0] = -(*this)[1];
    oRotateMat[2][1] = (*this)[0];
    return oRotateMat;
}

double Vector3D::Norm2()
{
    return m_oV3D.Norm2();
}

Matrix Vector3D::GetMatrix()
{
    return m_oV3D;
}

Vector6D Vector3D::GetScrewAxis(Vector3D &v3dPoint, Vector3D &v3dDirection, double dPitch)
{
    Vector6D oVector6D;
    for (unsigned int ii = 0; ii < 3; ii++)
    {
        oVector6D[ii] = v3dDirection[ii];
    }
    Vector3D oNormalVec = v3dPoint.GetVectorCross(v3dDirection);
    Vector3D oTangentVec = v3dDirection * dPitch;
    oNormalVec = oNormalVec + oTangentVec;
    for (int ii = 0; ii < 3; ii++)
    {

        oVector6D[ii + 3] = oNormalVec[ii];
    }
    return oVector6D;
}

double Vector3D::GetAxisAng3()
{
    double dTheta = this->Norm2();
    *this / dTheta;
    return dTheta;
}
VectorD3::VectorD3() : m_oVD3(1, 3) {}
VectorD3::~VectorD3(){

};

VectorD3::VectorD3(double dData1, double dData2, double dData3) : m_oVD3(1, 3)
{
    (*this)[0] = dData1;
    (*this)[1] = dData2;
    (*this)[2] = dData3;
}
VectorD3::VectorD3(const VectorD3 &oVectorD3) : m_oVD3(1, 3)
{
    for (int ii = 0; ii < 3; ii++)
    {
        (*this)[ii] = oVectorD3[ii];
    }
}

double &VectorD3::operator[](unsigned int uiIndex) const
{
    return m_oVD3[0][uiIndex];
}

std::ostream &operator<<(std::ostream &out, VectorD3 &oVectorD3)
{
    out << oVectorD3.m_oVD3;
}

double VectorD3::operator*(Vector3D &oVector3D)
{
    double dResult = 0.0;
    for (int ii = 0; ii < 3; ii++)
    {
        dResult = (*this)[ii] * oVector3D[ii] + dResult;
    }
    return dResult;
}
