//
// Created by zw on 2021/10/19.
//

#ifndef NEWTRAVEL_MATH_VECTOR6D_H
#define NEWTRAVEL_MATH_VECTOR6D_H

#include "Math/math_matrix.h"
#include <iostream>

class Vector6D
    {
    public:
        Vector6D();
        Vector6D(double dData1, double dData2, double dData3, double dData4, double dData5, double dData6);
        double &operator[](unsigned int iIndex);

    private:
        Matrix m_oV6D;
    };
#endif // NEWTRAVEL_MATH_VECTOR6D_H
