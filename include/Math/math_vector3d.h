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
    Matrix GetSkewSymmetricMatrix();

public:
    double &operator[](int iIndex);
private:
    Vector<double> m_vecV3D;
};

#endif // NEWTRAVEL_MATH_VECTOR3D_H
