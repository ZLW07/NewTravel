//
// Created by wei on 2022/7/16.
//

#ifndef NEWTRAVEL_MATH_MATRIX4_EIGEN_H
#define NEWTRAVEL_MATH_MATRIX4_EIGEN_H

#include "Eigen/Eigen"
#include "Math/math_rotation_eigen.h"

class Matrix4E
{
public:
    Matrix4E();
    Matrix4E(RotationE oRot, Vector3DE v3d);
    ~Matrix4E();

public:
    RotationE GetRotation();
    Vector3DE GetPose();

public:
    void Inv();
    Matrix4E operator*(Matrix4E &oMat4);
private:
    Eigen::Matrix4d m_mat;
};

#endif // NEWTRAVEL_MATH_MATRIX4_EIGEN_H
