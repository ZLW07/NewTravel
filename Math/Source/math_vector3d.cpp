//
// Created by zw on 2021/10/16.
//

#include "Math/math_vector3d.h"

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

Matrix Vector3D::GetSkewSymmetricMatrix()
{
    Matrix oSkewSymmetric(3,3);
    oSkewSymmetric[0][1] = -m_vecV3D[2];
    oSkewSymmetric[0][2] = m_vecV3D[1];

    oSkewSymmetric[1][0] = m_vecV3D[2];
    oSkewSymmetric[1][2] = -m_vecV3D[0];

    oSkewSymmetric[2][0] = -m_vecV3D[1];
    oSkewSymmetric[2][1] = m_vecV3D[0];
    return oSkewSymmetric;
}


double & Vector3D::operator[](int iIndex)
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



