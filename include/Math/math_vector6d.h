//
// Created by zw on 2021/10/19.
//

#ifndef NEWTRAVEL_MATH_VECTOR6D_H
#define NEWTRAVEL_MATH_VECTOR6D_H

#include "Math/math_matrix.h"
#include <iostream>

class Vector3D;
class Vector6D
{
    friend std::ostream &operator<<(std::ostream &out, Vector6D &oVector6D);

public:
    Vector6D();
    Vector6D(double dData1, double dData2, double dData3, double dData4, double dData5, double dData6);
    double &operator[](unsigned int iIndex) const;
    Matrix Get6DToSe3(const Vector6D &oVector6D);

private:
    Matrix m_oV6D;
};
#endif // NEWTRAVEL_MATH_VECTOR6D_H
