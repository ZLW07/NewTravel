//
// Created by wei on 2022/7/16.
//

#include "../../Include/Math/math_matrix4.h"

namespace zl
{
Matrix4::Matrix4()
{
    m_mat = Eigen::Matrix4d::Zero();
}

Matrix4::Matrix4(Rotation oRot, Vector3D v3d)
{
    m_mat = Eigen::Matrix4d::Identity();
    for (int ii = 0; ii < 3; ++ii)
    {
        for (int ij = 0; ij < 3; ++ij)
        {
            m_mat(ii, ij) = oRot(ii, ij);
        }
    }
    for (int jj = 0; jj < 3; ++jj)
    {
        m_mat(jj, 3) = v3d[jj];
    }
}

Matrix4::~Matrix4() {}

std::ostream &operator<<(std::ostream &os, Matrix4 &oMatrix4E)
{
    os << oMatrix4E.m_mat;
    return os;
}

Rotation Matrix4::GetRotation()
{
    Rotation oRat;
    for (int ii = 0; ii < 3; ++ii)
    {
        for (int ij = 0; ij < 3; ++ij)
        {
            oRat(ii, ij) = m_mat(ii, ij);
        }
    }
    return oRat;
}

Vector3D Matrix4::GetPose()
{
    Vector3D v3dResult;
    for (int ii = 0; ii < 3; ++ii)
    {
        v3dResult[ii] = m_mat(ii, 3);
    }
    return v3dResult;
}

Matrix4 Matrix4::Inv()
{
    Matrix4 oMatrix4E;
    oMatrix4E.m_mat = m_mat.inverse();
    return oMatrix4E;
}

Matrix4 Matrix4::operator*(Matrix4 &oMat4)
{
    Matrix4 oMat;
    oMat.m_mat = m_mat * oMat4.m_mat;
    return oMat;
}
}
