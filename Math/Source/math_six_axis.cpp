//
// Created by zw on 2021/10/28.
//

#include "Math/math_six_axis.h"

Se3Matrix Axis6Se3::GetKinSpace(Se3Matrix &oSe3Mat, SixAxisVec6DArray &oSixAxisVec6DAry, Vector6D &oVec6D)
{
    Se3Matrix oSe3M = oSe3Mat;
    int iTotalAxis = oSixAxisVec6DAry.GetTotalNumber();
    ZLOG << " iTotalAxis is " << iTotalAxis;
    double dTheta = 0.0;
    Se3Matrix oTempSe3;
    Se3Matrix oSe3Temp;
    Vector6D oTempVec6d;
    iTotalAxis = iTotalAxis - 1;
    for (int ii = iTotalAxis; ii >= 0; ii--)
    {
        dTheta = oVec6D[ii];
        oTempVec6d = oSixAxisVec6DAry[ii] * dTheta;
        oTempSe3 = Get6DToSe3(oTempVec6d);
        oSe3Mat = GetMatrixExp6(oTempSe3) * oSe3M;
        oSe3M = oSe3Mat;
    }
    oSe3Mat = oSe3M;
    return oSe3M;
}

Se3Matrix Axis6Se3::GetMatrixExp6(Se3Matrix &se3Mat)
{
    RotateMat oRotate = se3Mat.GetRotMatrix();
    Vector3D oVecAix = oRotate.GetScrewAxis();
    double dNormValue = oVecAix.Norm2();
    Vector3D oPose = se3Mat.GetTranslation();
    if (NearZero(dNormValue))
    {
        RotateMat oEye(1);
        Se3Matrix oSe3New(oEye, oPose);
        return oSe3New;
    }
    double dTheta = oVecAix.GetAxisAng3();
    RotateMat oRateW = oRotate;
    oRotate / dTheta;
    RotateMat oRotateMat = oRateW.GetMatrixExp3();
    RotateMat oRotEye(1);
    oRotEye = oRotEye * dTheta;
    double dTemp1 = 1 - cos(dTheta);
    RotateMat oTemp2 = oRotate * dTemp1;
    double dTemp3 = dTheta - sin(dTheta);
    RotateMat oTemp4 = oRotate * dTemp3 * oRotate ;
    RotateMat oTemp5 = oRotEye + oTemp2 + oTemp4;
    oPose / dTheta;
    Vector3D oV3D = oTemp5 * oPose;
    Se3Matrix oSe3Mat(oRotateMat, oV3D);
    return oSe3Mat;
}
