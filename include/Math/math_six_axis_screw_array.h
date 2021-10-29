//
// Created by zw on 2021/10/28.
//

#ifndef NEWTRAVEL_MATH_SIX_AXIS_SCREW_ARRAY_H
#define NEWTRAVEL_MATH_SIX_AXIS_SCREW_ARRAY_H
#include "Math/math_vector6d.h"

class Axis6ScrewAry
{
    friend std::ostream &operator<<(std::ostream &out, Axis6ScrewAry &oSixAxisVec6DArray);
public:
    Axis6ScrewAry();
    void PushBack(Vector6D &Vec6D);
    Vector6D operator[](int iIndex);
    int GetTotalNumber();
    ~Axis6ScrewAry();

private:
    Vector6D m_oVec6D[6];
    int m_iIndex;
};

#endif // NEWTRAVEL_MATH_SIX_AXIS_SCREW_ARRAY_H
