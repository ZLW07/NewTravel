//
// Created by zw on 2021/10/16.
//

#include "Math/math_vector3d.h"

double DegToRad(double dDeg)
{
    return (3.1415926 * dDeg)/180;
}

double RadToDeg(double dRad)
{
    return (180 * dRad)/3.1415926;
}

Vector3D::Vector3D()
{
    m_vecV3D = Vector<double>(3);
}

Vector3D::Vector3D(double dData1, double dData2, double dData3)
{
    m_vecV3D = Vector<double>(3);
    m_vecV3D[0] = dData1;
    m_vecV3D[1] = dData2;
    m_vecV3D[2] = dData3;
}

Vector3D::Vector3D(const Vector3D &v3dData)
{
    m_vecV3D = v3dData.m_vecV3D;
}

double Vector3D::X()
{
    return m_vecV3D[0];
}

double Vector3D::Y()
{
    return m_vecV3D[1];
}

double Vector3D::Z()
{
    return m_vecV3D[2];
}

Matrix Vector3D::GetSkewSymmetricMatrix()
{
    Matrix oSkewSymmetric(3, 3);
    oSkewSymmetric[0][1] = -m_vecV3D[2];
    oSkewSymmetric[0][2] = m_vecV3D[1];

    oSkewSymmetric[1][0] = m_vecV3D[2];
    oSkewSymmetric[1][2] = -m_vecV3D[0];

    oSkewSymmetric[2][0] = -m_vecV3D[1];
    oSkewSymmetric[2][1] = m_vecV3D[0];
    return oSkewSymmetric;
}

double &Vector3D::operator[](int iIndex)
{
    if ((iIndex > 3) || (iIndex < 0))
    {
        ZLOG << " The index is out of range; the actual index is " << iIndex << "; the limit index is " << 3;
        exit(1);
    }
    return m_vecV3D[iIndex];
}

std::ostream &operator<<(std::ostream &os, Vector3D &v3dData)
{
    for (int ii = 0; ii < 3; ++ii)
    {
        os << v3dData[ii] << " ";
    }
    return os;
}

Vector3D Vector3D::operator+(Vector3D &v3dData)
{
    return Vector3D(m_vecV3D[0] + v3dData[0], m_vecV3D[1] + v3dData[1], m_vecV3D[2] + v3dData[2]);
}

Vector3D Vector3D::operator-(Vector3D &v3dData)
{
    return Vector3D(m_vecV3D[0] - v3dData[0], m_vecV3D[1] - v3dData[1], m_vecV3D[2] - v3dData[2]);
}

bool Vector3D::operator==(Vector3D &v3dData)
{
    Vector3D v3dTemp = *this - v3dData;
    if ((fabs(v3dTemp.X() + fabs(v3dTemp.Y()) + fabs(v3dTemp.Z())) > 0.0001))
    {
        return true;
    }
    return false;
}

Vector3D Vector3D::Scale(double dData)
{
    return Vector3D(m_vecV3D[0] * dData, m_vecV3D[1] * dData, m_vecV3D[2] * dData);
}

double Vector3D::Dot(Vector3D &v3dData)
{
    return (m_vecV3D[0] * v3dData[0]) + (m_vecV3D[1] * v3dData[1]) + (m_vecV3D[2] * v3dData[2]);
}

Vector3D Vector3D::Cross(Vector3D &v3dData)
{
    double x = m_vecV3D[1] * v3dData[2] - m_vecV3D[2] * v3dData[1];
    double y = m_vecV3D[2] * v3dData[0] - m_vecV3D[0] * v3dData[2];
    double z = m_vecV3D[0] * v3dData[1] - m_vecV3D[1] * v3dData[0];
    return Vector3D(x, y, z);
}

double Vector3D::Norm()
{
    return sqrt(pow(X(), 2) + pow(Y(), 2) + pow(Z(), 2));
}

double Vector3D::GetVectorAngleRad(Vector3D &v3dData)
{
    double dDot = Dot(v3dData);
    double dNorm1 = Norm();
    double dNorm2 = v3dData.Norm();
    if ((fabs(dNorm1) < 0.0001) && (fabs(dNorm2) < 0.0001))
    {
        return 1.5707963;
    }
    double dAngle = dDot / (dNorm1 * dNorm2);
    return acos(dAngle);
}

double Vector3D::GetVectorAngleDeg(Vector3D &v3dData)
{
    double dAngleRad = GetVectorAngleRad(v3dData);
    return RadToDeg(dAngleRad);
}

void Vector3D::Clear()
{
    m_vecV3D.Clear();
}

Vector<double> & Vector3D::GetVectorValue()
{
    return m_vecV3D;
}




