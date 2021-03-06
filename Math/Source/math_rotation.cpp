//
// Created by wei on 2022/4/23.
//

#include "Math/math_rotation.h"

Rotation::Rotation() : m_matData(3, 3), m_iCol(3), m_iRow(3) {}

Rotation::Rotation(Vector3D &v3dColData_1, Vector3D &v3dColData_2, Vector3D &v3dColData_3):m_matData(3, 3), m_iCol(3), m_iRow(3)
{
    for (int iRow = 0; iRow < 3; iRow++)
    {
        m_matData[iRow][0] = v3dColData_1[iRow];
        m_matData[iRow][1] = v3dColData_2[iRow];
        m_matData[iRow][2] = v3dColData_3[iRow];
    }
}

Rotation::Rotation(const Rotation &rotData):m_matData(3, 3)
{
    m_matData = rotData.m_matData;
    m_iRow = rotData.m_iRow;
    m_iCol = rotData.m_iCol;
}

Vector3D Rotation::operator*(Vector3D &v3dData)
{
    Vector3D oResult;
    double dTempResult = 0.0;
    for (int iRow = 0; iRow < m_iRow; iRow++)
    {
        for (int iCol = 0; iCol < m_iCol; iCol++)
        {
            dTempResult = m_matData[iCol][iRow] * v3dData[iCol] + dTempResult;
        }
        oResult[iRow] = dTempResult;
        dTempResult = 0.0;
    }
    return oResult;
}

Rotation Rotation::operator/(double dData)
{
    for (int iRow = 0; iRow < m_iRow; iRow++)
    {
        for (int iCol = 0; iCol < m_iCol; iCol++)
        {
            m_matData[iRow][iCol] = m_matData[iRow][iCol] /dData;
        }
    }
    return *this;
}

Rotation Rotation::operator/(int iData)
{
    for (int iRow = 0; iRow < m_iRow; iRow++)
    {
        for (int iCol = 0; iCol < m_iCol; iCol++)
        {
            m_matData[iRow][iCol] = m_matData[iRow][iCol] /iData;
        }
    }
    return *this;
}

std::ostream &operator<<(std::ostream &os, Rotation &rotData)
{
    int iTemp = 2;
    for (int ii = 0; ii < 3; ii++)
    {
        os << "{";
        for (int jj = 0; jj < 3; jj++)
        {
            os << rotData.m_matData[ii][jj];
            if (iTemp != jj)
            {
                os << " ";
            }
        }
        os << "} ";
    }
    return os;
}

Vector<double> &Rotation::operator[](int iIndex)
{
    return m_matData[iIndex];
}

Rotation Rotation::CombinationTransformMatrix(Matrix &srcMat)
{
    if (3 <= srcMat.GetColSize() || 3 <= srcMat.GetRowSize())
    {
        ZLOG << " the src size is wrong, which is required to be 2 * 2 ";
        exit(1);
    }
    if ((2 == srcMat.GetColSize()) || (2 == srcMat.GetRowSize()))
    {
        m_matData[0][0] = 1.0 ;
        for ( int ii = 0; ii < 2; ii++)
        {
            for (int ij = 0; ij < 2; ++ij)
            {
                m_matData[ii +1][ij+1] = srcMat[ii][ij];
            }
        }
    }
    else if ((1 == srcMat.GetColSize()) || (1 == srcMat.GetRowSize()))
    {
        m_matData[0][0] = 1.0 ;
        m_matData[1][1] = 1.0 ;
        m_matData[2][2] = srcMat[0][0];
    }
    else
    {
        ZLOG << " The size is not match";
        exit(1);
    }
    return *this;
}
VectorD3 Rotation::GetColVector(unsigned int iCol)
{
    VectorD3 v3dResult;
    for (int ii = 0; ii < m_iRow; ++ii)
    {
        v3dResult[ii] = m_matData[ii][iCol];
    }
    return v3dResult;
}

Vector<double> Rotation::GetColVector(unsigned int iCol, unsigned int uiBeginRow)
{
    Vector<double> vecResult(m_iRow);
    for (int ii = uiBeginRow; ii < m_iRow; ++ii)
    {
        vecResult.push_back(m_matData[ii][iCol]);
    }
    return vecResult;
}

Vector3D Rotation::GetRowVector(unsigned int iRow)
{
    Vector3D v3dResult;
    for (int ii = 0; ii < m_iCol; ++ii)
    {
        v3dResult[ii] = m_matData[iRow][ii];
    }
    return v3dResult;
}

Rotation Rotation::Dot(VectorD3 &vd3Data, Vector3D &v3dData)
{
    for (int ii = 0; ii < m_iRow; ++ii)
    {
        for (int ij = 0; ij < m_iCol; ++ij)
        {
            m_matData[ii][ij] = vd3Data[ii] * v3dData[ij];
        }
    }
    return *this;
}

double Rotation::Dot(Vector3D &vd3Data, VectorD3 &v3dData)
{
    double dResult = 0.0;
    for (int ii = 0; ii < 3; ++ii)
    {
        dResult = dResult + vd3Data[ii] * v3dData[ii];
    }
    return dResult;
}

Matrix &Rotation::GetMatValue()
{
    return m_matData;
}

Rotation Rotation::ConversionMatToRot(Matrix &matData)
{
    if ((matData.GetRowSize() != m_iRow) || (matData.GetColSize() != m_iCol))
    {
        ZLOG << " The size is not match";
        exit(1);
    }
    m_matData = matData;
    return *this;
}

Rotation Rotation::Cov(std::vector<Vector3D> &vSrc_1)
{
    int iSize = vSrc_1.size();
    double tMean_1 = 0.0;
    double tMean_2 = 0.0;
    double tMean_3 = 0.0;
    for (int jj = 0; jj < iSize; jj++)
    {
        tMean_1 = tMean_1 + vSrc_1[jj].X();
        tMean_2 = tMean_2 + vSrc_1[jj].Y();
        tMean_3 = tMean_3 + vSrc_1[jj].Z();
    }
    tMean_1 = tMean_1 / iSize;
    tMean_2 = tMean_2 / iSize;
    tMean_3 = tMean_3 / iSize;
    for (int ij = 0; ij < iSize; ++ij)
    {
        m_matData[0][0] = MEAN(vSrc_1[ij].X(), tMean_1, vSrc_1[ij].X(), tMean_1) + m_matData[0][0];
        m_matData[0][1] = MEAN(vSrc_1[ij].X(), tMean_1, vSrc_1[ij].Y(), tMean_2) + m_matData[0][1];
        m_matData[0][2] = MEAN(vSrc_1[ij].X(), tMean_1, vSrc_1[ij].Z(), tMean_3) + m_matData[0][2];
        m_matData[1][0] = MEAN(vSrc_1[ij].Y(), tMean_2, vSrc_1[ij].X(), tMean_1) + m_matData[1][0];
        m_matData[1][1] = MEAN(vSrc_1[ij].Y(), tMean_2, vSrc_1[ij].Y(), tMean_2) + m_matData[1][1];
        m_matData[1][2] = MEAN(vSrc_1[ij].Y(), tMean_2, vSrc_1[ij].Z(), tMean_3) + m_matData[1][2];
        m_matData[2][0] = MEAN(vSrc_1[ij].Z(), tMean_3, vSrc_1[ij].X(), tMean_1) + m_matData[2][0];
        m_matData[2][1] = MEAN(vSrc_1[ij].Z(), tMean_3, vSrc_1[ij].Y(), tMean_2) + m_matData[2][1];
        m_matData[2][2] = MEAN(vSrc_1[ij].Z(), tMean_3, vSrc_1[ij].Z(), tMean_3) + m_matData[2][2];
    }
    return (*this)/(iSize - 1);
}

Rotation Rotation::Transpose()
{
    Rotation oResult;
    for (int ii = 0; ii < m_iRow; ++ii)
    {
        for (int ij = 0; ij < m_iCol; ++ij)
        {
            oResult[ij][ii] = m_matData[ii][ij];
        }
    }
    return oResult;
}

void Rotation::SetEye()
{
    m_matData.SetIdentityMatrix();
}

Matrix Rotation::Householder(Vector<double> &vecData)
{
    int iSize = vecData.Size();
    Matrix oMatResult(iSize,iSize);
    if (1 ==iSize)
    {
        oMatResult[0][0] = -1;
        return oMatResult;
    }
    Vector<double> vec_e(iSize);
    double dSigma = vecData.Norm2();
    if (vecData[0] < 0.0)
    {
        dSigma = dSigma * (-1);
    }
    vec_e[0] = dSigma;
    Vector<double> vec_nu = vecData + vec_e;
    oMatResult.SetIdentityMatrix();
    Matrix oMat(iSize,iSize);
    oMat.Dot(vec_nu,vec_nu);
    oMat.Dot(2/pow(vec_nu.Norm2(),2));
    oMatResult = oMatResult - oMat;
    return oMatResult;
}

Rotation Rotation::GetOBBDirectionVector(Rotation &rotData)
{
    VectorD3 ovd3 = rotData.GetColVector(0);
    Matrix oMat_H1 = Householder(ovd3.GetVectorValue());
    Matrix oMat_H1A1 = oMat_H1 * rotData.GetMatValue();
    Vector<double> vecTemp = oMat_H1A1.GetColVector(1,1);
    Matrix oMat_H2 = Householder(vecTemp);
    Rotation rotRot_H2;
    rotRot_H2.CombinationTransformMatrix(oMat_H2);
    oMat_H1A1 = rotRot_H2.GetMatValue() * oMat_H1A1;
    vecTemp = oMat_H1A1.GetColVector(2,2);
    Matrix oMat_H3 = Householder(vecTemp);
    Rotation rotRot_H3;
    rotRot_H3.CombinationTransformMatrix(oMat_H3);
    Rotation rot_Q;
    Matrix oMat = rotRot_H3.GetMatValue() * rotRot_H2.GetMatValue() * oMat_H1;
    rot_Q.ConversionMatToRot(oMat);
    return rot_Q;
}

//Rotation Rotation::RotateEular(double dGamma, double dBeta, double dAlpha,int iXAxis,int iYAxis, int ZAxis)
//{
//    double dElement0_0 = cos(dAlpha)* cos(dBeta);
//    double dElement0_1 =  cos(dAlpha)* sin(dBeta) * sin(dGamma) - sin(dAlpha) * cos(dGamma);
//    double dElement0_2 = cos(dAlpha)* sin(dBeta)*cos(dGamma) + sin(dAlpha) * sin(dGamma);
//    double dElement1_0 = sin(dAlpha) * cos(dBeta);
//    double dElement1_1 = sin(dAlpha) * sin(dBeta) * sin(dGamma) + cos(dAlpha) * cos(dGamma);
//    double dElemnet1_2 = sin(dAlpha)*sin(dBeta)*cos(dGamma) - cos(dAlpha)*sin(dGamma);
//    double
//    Vector3D v3dX(cos(dAlpha)* cos(dBeta),cos)
//}