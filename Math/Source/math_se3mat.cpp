//
// Created by zw on 2021/10/19.
//

#include "Math/math_se3mat.h"

std::ostream &operator <<(std::ostream &out, Se3Matrix &oSe3Matrix)
{
    return out << oSe3Matrix.m_oMat4;
}

Se3Matrix::Se3Matrix(): m_oMat4(4,4){}

Se3Matrix::Se3Matrix(const Se3Matrix &oSe3Mat):m_oMat4(4,4)
{
    for (int ii = 0; ii < 4; ii++)
    {
        for (int jj = 0; jj < 4; jj++)
        {
            (*this)[ii][jj] = oSe3Mat[ii][jj];
        }
    }
}


Se3Matrix::Se3Matrix(RotateMat oRotateMat, Vector3D oPose): m_oMat4(4,4)
{
    for (int ii = 0; ii < 3; ii++)
    {
        for (int jj = 0; jj < 3; jj++)
        {
            (*this)[ii][jj] = oRotateMat[ii][jj];
        }
        (*this)[ii][3] = oPose[ii];
    }
    (*this)[3][3] = 1.0;
}

//Se3Matrix Se3Matrix::GetMatrixExp6(Se3Matrix se3Mat)
//{
//    RotateMat oRotate = se3Mat.GetRotMatrix();
//    Vector3D oVecAix = oRotate.GetScrewAxis();
//    double dNormValue = oVecAix.Norm2();
//    Vector3D oPose = se3Mat.GetTranslation();
//    if (NearZero(dNormValue))
//    {
//        RotateMat oEye(1);
//        Se3Matrix oSe3New(oEye,oPose);
//        return oSe3New;
//    }
//    double dTheta = oVecAix.GetAxisAng3();
//    RotateMat oRateW = oRotate;
//    oRotate/dTheta;
//    RotateMat oRotateMat = oRateW.GetMatrixExp3();
//    RotateMat oRotEye(1);
//    oRotEye = oRotEye * dTheta;
//    double dTemp1 = 1 - cos(dTheta);
//    RotateMat oTemp2 = oRotate * dTemp1;
//    double dTemp3 = dTheta - sin(dTheta);
//    RotateMat oTemp4 = oRotate * oRotate * dTemp3;
//    RotateMat oTemp5 = oRotEye + oTemp2 + oTemp4;
//    oPose/dTheta;
//    Vector3D oV3D = oTemp5 * oPose;
//    Se3Matrix oSe3Mat(oRotateMat,oV3D);
//    return  oSe3Mat;
//}

double* Se3Matrix::operator[](const int iIndex) const
{
    return m_oMat4[iIndex];
}

void Se3Matrix::operator*(double dData)
{
    m_oMat4 * dData;
}

Se3Matrix Se3Matrix::operator*(const Se3Matrix &oSecData)
{
    Matrix oTempMat = (*this).m_oMat4 * (oSecData.m_oMat4);
    for (int ii = 0; ii < 4; ii++)
    {
        for (int jj = 0; jj < 4; jj++)
        {
            (*this)[ii][jj] = oTempMat[ii][jj];
        }
    }
    return *this;
}

Vector3D Se3Matrix::GetScrewAxis(Se3Matrix &oMat4)
{
    Vector3D oVec3D;
    return oVec3D;
}

RotateMat Se3Matrix::GetRotMatrix()
{
    RotateMat oMat3;
    for (int ii = 0; ii < 3; ii++)
    {
        for (int jj = 0; jj < 3; jj++)
        {
            oMat3[ii][jj] = (*this)[ii][jj];
        }
    }

    return oMat3;
}

Vector3D Se3Matrix::GetTranslation()
{
    Vector3D oVec3D;
    for (int ii = 0; ii < 3; ii++)
    {
        oVec3D[ii] = (*this)[ii][3];
    }
    return oVec3D;
}

Se3Matrix Get6DToSe3(Vector6D &oVec6dData)
{
    Vector3D oVec3D;
    Se3Matrix oSe3Mat;
    for (int ii = 0; ii < 3; ii++)
    {
        oVec3D[ii] = oVec6dData[ii];
    }
    RotateMat oVec3DMat = oVec3D.GetSkewSymmetric();

    for (int jj = 0; jj < 3; jj++)
    {
        for (int ij = 0; ij < 3; ij++)
        {
            oSe3Mat[jj][ij] = oVec3DMat[jj][ij];
        }
    }
    for (int ii = 0; ii < 3; ii++)
    {
        oSe3Mat[ii][3] = oVec6dData[ii + 3];
        oSe3Mat[3][ii] = 0.0;
    }
    return oSe3Mat;
}

//template <typename T>
//Se3Matrix &Se3Matrix::GetFKinSpace(Se3Matrix &M, Vector6D vec6D(T),double dTheta(T))
//{
//    for (int ii = 0; ii < sizeof(dTheta); ii++)
//    {
//        Se3Matrix se3Result = GetMatrixExp6(vec6D(ii).Get6DToSe3() * dTheta(ii));
//    }
//}
