//
// Created by zw on 2021/10/19.
//

#include "Math/math_vector6d.h"

Vector6D::Vector6D() : m_oV6D(6, 1) {}

Vector6D::Vector6D(double dData1, double dData2, double dData3, double dData4, double dData5, double dData6)
: m_oV6D(6, 1)
{
    (*this)[0] = dData1;
    (*this)[1] = dData2;
    (*this)[2] = dData3;
    (*this)[3] = dData4;
    (*this)[4] = dData5;
    (*this)[5] = dData6;
}

double &Vector6D::operator[](unsigned int iIndex)
{
    return m_oV6D[iIndex][0];
}