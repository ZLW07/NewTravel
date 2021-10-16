//
// Created by zw on 2021/10/16.
//

#include "Math/math_matrix.h"

int Vector::m_iVecSize = 1;

void Vector::SetSize(int iSize)
{
    if (iSize > 0)
    {
        m_iVecSize = iSize;
    }
}

Vector::Vector()
{
    m_pVec = new double[m_iVecSize];

    for (int ii = 0; ii < m_iVecSize; ii++)
    {
        m_pVec[ii] = 0.0;
    }
}

Vector::~Vector()
{
    if (m_pVec)
    {
        delete[] m_pVec;
        m_pVec = nullptr;
    }
}

double &Vector::operator[](int iIndex)
{
    if (iIndex >= m_iVecSize)
    {
        exit(-1);
    }
    return m_pVec[iIndex];
}

Matrix::Matrix(int iRow, int iCol)
{
    if (iCol > 0)
    {
        Vector::SetSize(iCol);
    }
    else
    {
        Vector::SetSize(iRow);
    }
    m_iHeight = iRow;
    m_pVector = new Vector[m_iHeight];
}

Matrix::~Matrix()
{
    if (m_pVector)
    {
        delete []m_pVector;
    }
}

Vector &Matrix::operator[](int iIndex)
{
    if (iIndex > m_iHeight)
    {
        exit(-1);
    }
    return m_pVector[iIndex];
}