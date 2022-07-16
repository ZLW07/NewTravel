//
// Created by wei on 2022/7/16.
//

#ifndef NEWTRAVEL_MATH_ROTATION_EIGEN_H
#define NEWTRAVEL_MATH_ROTATION_EIGEN_H
#include "Eigen/Eigen"
#include <iostream>
#include "Math/math_vector3d_eigen.h"

class RotationE
{
    friend  std::ostream &operator<<(std::ostream &os, RotationE &rotData);
public:
    RotationE();
    ~RotationE();
    RotationE CovarianceMatrix(std::vector<Eigen::Vector3d> &vSrc_1);
    Eigen::Vector3d GetCol(int iCol);
    RotationE GetOBBDirectionVector(RotationE &rotData);
    RotationE Inverse();
    Eigen::Matrix3d GetData();
    void IdentityMatrix();
public:
    RotationE operator/(double dData);
    Vector3DE operator*(Vector3DE v3dData);
    double &operator()(int iRow,int iCol);
    Eigen::RowVector3d &operator[](int iIndex);

private:

    Eigen::Matrix3d  m_mat3Rotation;
};

#endif // NEWTRAVEL_MATH_ROTATION_EIGEN_H
