//
// Created by zw on 2021/10/28.
//

#include "Math/math_six_axis_screw_array.h"

Axis6ScrewAry::Axis6ScrewAry(): m_iIndex(0){};

Axis6ScrewAry::~Axis6ScrewAry(){};

void Axis6ScrewAry::PushBack(Vector6D &Vec6D)
{
    m_oVec6D[m_iIndex] = Vec6D;
    m_iIndex = m_iIndex + 1;
}

std::ostream &operator<<(std::ostream &out, Axis6ScrewAry &oAxis6ScrewAry)
{
    for (int ii = 0; ii < oAxis6ScrewAry.m_iIndex; ii++)
    {
        out << oAxis6ScrewAry.m_oVec6D[ii];
    }
  return out;
}

Vector6D Axis6ScrewAry::operator[](int iIndex)
{
    return m_oVec6D[iIndex];
}

int Axis6ScrewAry::GetTotalNumber()
{
    return m_iIndex;
}

