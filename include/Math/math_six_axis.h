//
// Created by zw on 2021/10/28.
//

#ifndef NEWTRAVEL_MATH_SIX_AXIS_H
#define NEWTRAVEL_MATH_SIX_AXIS_H

#include "Math/math_se3mat.h"
#include "Math/math_six_axis_screw_array.h"

class Axis6Se3: public CheckZero
{

public:
    Se3Matrix GetKinSpace(Se3Matrix &oSe3Mat, Axis6ScrewAry &oSixAxisVec6DAry, Vector6D &oVec6D);
    Se3Matrix GetMatrixExp6(Se3Matrix &se3Mat);
private:
    Se3Matrix m_se3Mat;
};

#endif // NEWTRAVEL_MATH_SIX_AXIS_H
