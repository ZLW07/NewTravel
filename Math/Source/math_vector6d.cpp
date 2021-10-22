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

Matrix Vector6D::Get6DToSe3(const Vector6D &oVector6D)
{
    Matrix oResultSe3(4,4);
    Vector3D oVec3D;
    for (int ii = 0; ii < 3; ii++)
    {
        oVec3D[ii] = oVector6D[ii];
    }
    RotateMat oVec3DMat = oVec3D.GetSkewSymmetric();

    for (int jj = 0; jj < 3; jj++)
    {
        for (int ij = 0; ij < 3; ij++)
        {
            oResultSe3[jj][ij] = oVec3DMat[jj][ij];
        }
    }
    for (int ii = 0; ii < 3; ii++)
    {
        oResultSe3[ii][3] = oVector6D[ii + 3];
        oResultSe3[3][ii] = 0.0;
    }
    return oResultSe3;
}