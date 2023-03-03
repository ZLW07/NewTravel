//
// Created by wei on 2022/7/16.
//

#ifndef NEWTRAVEL_MATH_ROTATION_H
#define NEWTRAVEL_MATH_ROTATION_H
#include "Eigen/Eigen"
#include "Math/math_vector3d.h"
#include <iostream>

namespace zl
{

class Rotation
{
    friend std::ostream &operator<<(std::ostream &os, Rotation &rotData);

public:
    Rotation();
    ~Rotation();

    Vector3D GetCol(int iCol);
    Rotation GetOBBDirectionVector(Rotation &rotData);
    Rotation Inverse();
    Eigen::Matrix3d GetData();
    void IdentityMatrix();

public:
    Rotation operator/(double dData);
    Vector3D operator*(Vector3D v3dData);
    double &operator()(int iRow, int iCol);
    Eigen::RowVector3d &operator[](int iIndex);

private:
    Eigen::Matrix3d m_mat3Rotation;
    Eigen::RowVector3d m_vecD3;
};
}
#endif // NEWTRAVEL_MATH_ROTATION_H
