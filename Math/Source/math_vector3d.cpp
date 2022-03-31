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


