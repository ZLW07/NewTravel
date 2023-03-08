//
// Created by wei on 2022/7/16.
//

#ifndef NEWTRAVEL_MATH_MATRIX4_H
#define NEWTRAVEL_MATH_MATRIX4_H

#include "Eigen/Eigen"
#include "Math/math_rotation.h"

namespace zl
{
class Matrix4
{
    friend std::ostream &operator<<(std::ostream &os, Matrix4 &oMatrix4E);

public:
    Matrix4();
    Matrix4(Rotation oRot, Vector3D v3d);
    ~Matrix4();

public:
    Eigen::RowVector4d &operator[](int iIndex);
public:
    Rotation GetRotation();
    Vector3D GetPose();

public:
    Matrix4 Inv();
    Matrix4 operator*(Matrix4 &oMat4);

private:
    Eigen::Matrix4d m_mat;
};
}
#endif // NEWTRAVEL_MATH_MATRIX4_H
