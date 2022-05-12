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
            dTempResult = m_matData[iRow][iCol] * v3dData[iCol] + dTempResult;
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