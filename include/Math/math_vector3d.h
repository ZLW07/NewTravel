//
// Created by zw on 2021/10/16.
//

#ifndef NEWTRAVEL_MATH_VECTOR3D_H
#define NEWTRAVEL_MATH_VECTOR3D_H

#include <math.h>
#include <vector>

#include "Math/math_matrix.h"

class Vector3D
{
    friend std::ostream &operator<<(std::ostream &os, Vector3D &v3dData);
public:
    Vector3D();
    Vector3D(double dData1, double dData2, double dData3);
    Vector3D(const Vector3D &v3dData);
    Matrix GetSkewSymmetricMatrix();
    double _X();
    double _Y();
    double _Z();
public:
    double &operator[](int iIndex);
    Vector3D operator+(Vector3D &v3dData);
    Vector3D operator-( Vector3D &v3dData);
    Vector3D Scalar(double dData);
    double Dot(Vector3D &v3dData);
    Vector3D Cross(Vector3D &v3dData);
private:
    Vector<double> m_vecV3D;
};

#endif // NEWTRAVEL_MATH_VECTOR3D_H
