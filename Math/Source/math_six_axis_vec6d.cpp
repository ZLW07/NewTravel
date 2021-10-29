//
// Created by zw on 2021/10/28.
//

#include "Math/math_six_axis_vec6d.h"

SixAxisVec6DArray::SixAxisVec6DArray(): m_iIndex(0){};

SixAxisVec6DArray::~SixAxisVec6DArray(){};

void SixAxisVec6DArray::PushBack(Vector6D &Vec6D)
{
    m_oVec6D[m_iIndex] = Vec6D;
    m_iIndex = m_iIndex + 1;
}

std::ostream &operator<<(std::ostream &out, SixAxisVec6DArray &oSixAxisVec6DArray)
{
    for (int ii = 0; ii < oSixAxisVec6DArray.m_iIndex; ii++)
    {
        out << oSixAxisVec6DArray.m_oVec6D[ii];
    }
  return out;
}

Vector6D SixAxisVec6DArray::operator[](int iIndex)
{
    return m_oVec6D[iIndex];
}

int SixAxisVec6DArray::GetTotalNumber()
{
    return m_iIndex;
}

