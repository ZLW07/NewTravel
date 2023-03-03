//
// Created by wei on 2022/7/16.
//

#include "Math/math_rotation.h"
#include <iostream>

namespace zl
{


std::ostream &operator<<(std::ostream &os, Rotation &rotData)
{
    os << "Rotation matrix is: \n" << rotData.m_mat3Rotation;
    return os;
}

Rotation::Rotation()
{
    m_mat3Rotation = Eigen::Matrix3d::Zero();
    m_vecD3 = Eigen::RowVector3d::Zero();
}
Rotation::~Rotation() {}



Vector3D Rotation::GetCol(int iCol)
{
    Vector3D v3dDate(m_mat3Rotation.col(iCol));
    return v3dDate;
}

Rotation Rotation::GetOBBDirectionVector(Rotation &rotData)
{
    Eigen::EigenSolver<Eigen::Matrix3d> oMat(rotData.m_mat3Rotation);
    rotData.m_mat3Rotation = oMat.eigenvectors().real();
    return rotData;
}

Rotation Rotation::Inverse()
{
    m_mat3Rotation.inverse();
    return *this;
}

Eigen::Matrix3d Rotation::GetData()
{
    return m_mat3Rotation;
}

void Rotation::IdentityMatrix()
{
    m_mat3Rotation = m_mat3Rotation.Identity();
}

Rotation Rotation::operator/(double dData)
{
    m_mat3Rotation = m_mat3Rotation / dData;
    return *this;
}

Vector3D Rotation::operator*(Vector3D v3dData)
{
    Vector3D v3dE;
    v3dE.GetData() = m_mat3Rotation * v3dData.GetData();
    return v3dE;
}

double &Rotation::operator()(int iRow, int iCol)
{
    return m_mat3Rotation(iRow, iCol);
}

Eigen::RowVector3d &Rotation::operator[](int iIndex)
{
    m_vecD3 = m_mat3Rotation.row(iIndex);
    return m_vecD3;
}
}