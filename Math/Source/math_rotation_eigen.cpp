//
// Created by wei on 2022/7/16.
//

#include "Math/math_rotation_eigen.h"
#include <iostream>

#define MEAN(data_1, mean_1, data_3, mean_2) (data_1 - mean_1) * (data_3 - mean_2)

std::ostream &operator<<(std::ostream &os, RotationE &rotData)
{
    os << "Rotation matrix is: \n" << rotData.m_mat3Rotation;
    return os;
}

RotationE::RotationE()
{
    m_mat3Rotation = Eigen::Matrix3d::Zero();
}
RotationE::~RotationE() {}

RotationE RotationE::CovarianceMatrix(std::vector<Eigen::Vector3d> &vSrc_1)
{
    int iSize = vSrc_1.size();
    double tMean_1 = 0.0;
    double tMean_2 = 0.0;
    double tMean_3 = 0.0;
    for (int jj = 0; jj < iSize; jj++)
    {
        tMean_1 = tMean_1 + vSrc_1[jj].x();
        tMean_2 = tMean_2 + vSrc_1[jj].y();
        tMean_3 = tMean_3 + vSrc_1[jj].z();
    }
    tMean_1 = tMean_1 / iSize;
    tMean_2 = tMean_2 / iSize;
    tMean_3 = tMean_3 / iSize;
    for (int ij = 0; ij < iSize; ++ij)
    {
        m_mat3Rotation(0, 0) = MEAN(vSrc_1[ij].x(), tMean_1, vSrc_1[ij].x(), tMean_1) + m_mat3Rotation(0, 0);
        m_mat3Rotation(0, 1) = MEAN(vSrc_1[ij].x(), tMean_1, vSrc_1[ij].y(), tMean_2) + m_mat3Rotation(0, 1);
        m_mat3Rotation(0, 2) = MEAN(vSrc_1[ij].x(), tMean_1, vSrc_1[ij].z(), tMean_3) + m_mat3Rotation(0, 2);
        m_mat3Rotation(1, 0) = MEAN(vSrc_1[ij].y(), tMean_2, vSrc_1[ij].x(), tMean_1) + m_mat3Rotation(1, 0);
        m_mat3Rotation(1, 1) = MEAN(vSrc_1[ij].y(), tMean_2, vSrc_1[ij].y(), tMean_2) + m_mat3Rotation(1, 1);
        m_mat3Rotation(1, 2) = MEAN(vSrc_1[ij].y(), tMean_2, vSrc_1[ij].z(), tMean_3) + m_mat3Rotation(1, 2);
        m_mat3Rotation(2, 0) = MEAN(vSrc_1[ij].z(), tMean_3, vSrc_1[ij].x(), tMean_1) + m_mat3Rotation(2, 0);
        m_mat3Rotation(2, 1) = MEAN(vSrc_1[ij].z(), tMean_3, vSrc_1[ij].y(), tMean_2) + m_mat3Rotation(2, 1);
        m_mat3Rotation(2, 2) = MEAN(vSrc_1[ij].z(), tMean_3, vSrc_1[ij].z(), tMean_3) + m_mat3Rotation(2, 2);
    }
    return (*this) / (iSize - 1);
}

Eigen::Vector3d RotationE::GetCol(int iCol)
{
    return m_mat3Rotation.col(iCol);
}

RotationE RotationE::GetOBBDirectionVector(RotationE &rotData)
{
    Eigen::EigenSolver<Eigen::Matrix3d> oMat(rotData.m_mat3Rotation);
    rotData.m_mat3Rotation = oMat.eigenvectors().real();
    return rotData;
}

RotationE RotationE::Inverse()
{
    m_mat3Rotation.inverse();
    return *this;
}

Eigen::Matrix3d RotationE::GetData()
{
    return m_mat3Rotation;
}

void RotationE::IdentityMatrix()
{
    m_mat3Rotation.Identity();
}

RotationE RotationE::operator/(double dData)
{
    m_mat3Rotation = m_mat3Rotation / dData;
    return *this;
}

Vector3DE RotationE::operator*(Vector3DE v3dData)
{
    Vector3DE v3dE;
    v3dE.GetData() = m_mat3Rotation * v3dData.GetData();
    return v3dE;
}

double &RotationE::operator()(int iRow,int iCol)
{
    return m_mat3Rotation(iRow,iCol);
}

Eigen::RowVector3d &RotationE::operator[](int iIndex)
{
    Eigen::RowVector3d vc = m_mat3Rotation.row(iIndex);
    return vc;
}
