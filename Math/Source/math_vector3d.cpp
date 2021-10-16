//
// Created by zw on 2021/10/16.
//

#include "Math/math_vector3d.h"

Vector3D::Vector3D()
{
    m_v3d = {0.0,0.0,0.0};
}

Vector3D::Vector3D(double dData1, double dData2, double dData3)
{
    m_v3d = {dData1,dData2,dData3};
}

Matrix Vector3D::GetSkewSymmetric()
{
    Matrix oSkewSymmetric(3);
    oSkewSymmetric[0][1] = -m_v3d[2];
    oSkewSymmetric[0][2] = m_v3d[1];

    oSkewSymmetric[1][0] = m_v3d[2];
    oSkewSymmetric[1][2] = -m_v3d[0];

    oSkewSymmetric[2][0] = -m_v3d[1];
    oSkewSymmetric[2][1] = m_v3d[0];
    return oSkewSymmetric;
}


