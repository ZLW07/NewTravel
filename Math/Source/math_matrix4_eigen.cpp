//
// Created by wei on 2022/7/16.
//

#include "Math/math_matrix4_eigen.h"

Matrix4E::Matrix4E()
{
    m_mat = Eigen::Matrix4d::Zero();
}

Matrix4E::Matrix4E(RotationE oRot, Vector3DE v3d)
{
    m_mat =Eigen::Matrix4d::Identity();
    for (int ii = 0; ii < 3; ++ii)
    {
        for (int ij = 0; ij < 3; ++ij)
        {
            m_mat(ii,ij) = oRot(ii,ij);
        }
    }
    for (int jj = 0; jj < 3; ++jj)
    {
        m_mat(jj,3) = v3d[jj];
    }
}

Matrix4E::~Matrix4E() {}

std::ostream &operator<<(std::ostream &os, Matrix4E &oMatrix4E)
{
    os << oMatrix4E.m_mat;
    return os;
}

RotationE Matrix4E::GetRotation()
{
    RotationE oRat;
    for (int ii = 0; ii < 3; ++ii)
    {
        for (int ij = 0; ij < 3; ++ij)
        {
            oRat(ii,ij) = m_mat(ii,ij);
        }
    }
    return oRat;
}

Vector3DE Matrix4E::GetPose()
{
    Vector3DE v3dResult;
    for (int ii = 0; ii < 3; ++ii)
    {
        v3dResult[ii] = m_mat(ii,3);
    }
    return v3dResult;
}



Matrix4E Matrix4E::Inv()
{
    Matrix4E oMatrix4E;
    oMatrix4E.m_mat = m_mat.inverse();
    return oMatrix4E;
}

Matrix4E Matrix4E::operator*(Matrix4E &oMat4)
{
    Matrix4E oMat;
    oMat.m_mat = m_mat * oMat4.m_mat;
    return oMat;
}

