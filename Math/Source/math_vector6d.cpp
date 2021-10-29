//
// Created by zw on 2021/10/19.
//

#include "Math/math_vector6d.h"
#include <Math/math_vector3d.h>

Vector6D::Vector6D() : m_oV6D(6, 1) {}

Vector6D::Vector6D(double dData1, double dData2, double dData3, double dData4, double dData5, double dData6)
    : m_oV6D(6, 1)
{
    (*this)[0] = dData1;
    (*this)[1] = dData2;
    (*this)[2] = dData3;
    (*this)[3] = dData4;
    (*this)[4] = dData5;
    (*this)[5] = dData6;
}

std::ostream &operator<<(std::ostream &out, Vector6D &oVector6D)
{
    return out << oVector6D.m_oV6D;
}

double &Vector6D::operator[](unsigned int iIndex) const
{
    return m_oV6D[iIndex][0];
}

Vector6D &Vector6D::operator=(Vector6D &vec6D)
{
        for (int ii = 0; ii < 6; ii++)
        {
            (*this)[ii] = vec6D[ii];
        }
        return *this;
}

Vector6D &Vector6D::operator* (double dData)
{
    for (int ii = 0; ii < 6; ii++)
    {
        double dTempValue = (*this)[ii] * dData;
        (*this)[ii] = dTempValue;
    }
    return *this;
}

//Global function
Vector6D GetScrewAxis(Vector3D &v3dPoint, Vector3D &v3dDirection, double dPitch)
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


