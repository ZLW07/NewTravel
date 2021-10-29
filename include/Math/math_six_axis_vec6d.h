//
// Created by zw on 2021/10/28.
//

#ifndef NEWTRAVEL_MATH_SIX_AXIS_VEC6D_H
#define NEWTRAVEL_MATH_SIX_AXIS_VEC6D_H
#include "Math/math_vector6d.h"

class SixAxisVec6DArray
{
    friend std::ostream &operator<<(std::ostream &out, SixAxisVec6DArray &oSixAxisVec6DArray);
public:
    SixAxisVec6DArray();
    void PushBack(Vector6D &Vec6D);
    Vector6D operator[](int iIndex);
    int GetTotalNumber();
    ~SixAxisVec6DArray();

private:
    Vector6D m_oVec6D[6];
    int m_iIndex;
};

#endif // NEWTRAVEL_MATH_SIX_AXIS_VEC6D_H
