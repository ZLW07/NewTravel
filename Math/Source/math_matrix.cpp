//
// Created by zw on 2021/10/16.
//

#include "Math/math_matrix.h"

void Vector::SetSize(int iSize)
{
    if (iSize > 0)
    {
        m_iVecSize = iSize;
        for (int ii = 0; (ii < m_iVecSize) && (m_iVecSize > 0); ii++)
        {
            m_vecData.push_back(0.0);
        }
    }
}

Vector::Vector(int iSize)
{
    m_iVecSize = iSize;
    for (int ii = 0; (ii < m_iVecSize) && (m_iVecSize > 0); ii++)
    {
        m_vecData.push_back(0.0);
    }
}

Vector::~Vector() = default;

 double &Vector::operator[](int iIndex)
{
    if (iIndex > m_iVecSize)
    {
        ZLOG << " The index is out of range; The limit size is " << m_iVecSize << "; expect index is " << iIndex;
        exit(-1);
    }
    return m_vecData[iIndex];
}

Vector &Vector::operator=(Vector vecSrc)
{
    m_iVecSize = vecSrc.m_iVecSize;
    m_vecData = vecSrc.m_vecData;
    return *this;
}

std::ostream &operator<<(std::ostream &os,const Vector & vData)
{
    for (int ii = 0; ii < vData.m_iVecSize; ii++)
    {
        os << vData.m_vecData[ii];
    }
    return os;
}


Matrix::Matrix(int iRow, int iCol)
{
    m_iRow = iRow;
    if (iCol < 1)
    {
        ZLOG << " The parament set wrong, it shouble greater than 1";
        exit(-1);
    }
    m_iCol = iCol;
    std::vector<Vector> vData(m_iRow, Vector(m_iCol));
    m_matData = vData;
}

int Matrix::GetRowSize() const
{
    return m_iRow;
}

int Matrix::GetColSize() const
{
    return m_iCol;
}

Matrix::~Matrix() = default;

 Vector &Matrix::operator[](int iIndex)
{
    if (iIndex > m_iRow)
    {
        ZLOG << " The index is out of range; The limit size is " << m_iRow << "; expect index is " << iIndex;
        exit(-1);
    }
    return m_matData[iIndex];
}

std::ostream &operator<<(std::ostream &os, Matrix &matData)
{
    int iRow = matData.GetRowSize();
    int iCol = matData.GetColSize();
    int iTemp = matData.GetColSize() - 1;
    for (int ii = 0; ii < iRow; ii++)
    {
        os << "{";

        for (int jj = 0; jj < iCol; jj++)
        {
            os << matData[ii][jj];
            if (iTemp != jj)
            {
                os << " ";
            }
        }
        os << "} ";
    }
    return os;
}