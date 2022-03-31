//
// Created by zw on 2021/10/16.
//

#include "Math/math_matrix.h"

template <typename T> void Vector<T>::SetSize(int iSize)
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

template <typename T> Vector<T>::Vector(int iSize)
{
    m_iVecSize = iSize;
    for (int ii = 0; (ii < m_iVecSize) && (m_iVecSize > 0); ii++)
    {
        m_vecData.push_back(0.0);
    }
}

template <typename T> Vector<T>::~Vector() = default;

template <typename T> T &Vector<T>::operator[](int iIndex)
{
    if (iIndex > m_iVecSize)
    {
        ZLOG << " The index is out of range; The limit size is " << m_iVecSize << "; expect index is " << iIndex;
        exit(-1);
    }
    return m_vecData[iIndex];
}

template <typename T> Vector<T> &Vector<T>::operator=(Vector<T> vecSrc)
{
    m_iVecSize = vecSrc.m_iVecSize;
    m_vecData = vecSrc.m_vecData;
    return *this;
}

template <typename T> std::ostream &operator<<(std::ostream &os, const Vector<T> &vData)
{
    for (int ii = 0; ii < vData.m_iVecSize; ii++)
    {
        os << vData.m_vecData[ii] << " ";
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
    std::vector<Vector<double>> vData(m_iRow, Vector<double>(m_iCol));
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

Vector<double> &Matrix::operator[](int iIndex)
{
    if (iIndex > m_iRow)
    {
        ZLOG << " The index is out of range; The limit size is " << m_iRow << "; expect index is " << iIndex;
        exit(-1);
    }
    return m_matData[iIndex];
}

Matrix &Matrix::operator=(const Matrix &matData)
{
    m_iCol = matData.GetColSize();
    m_iRow = matData.GetRowSize();
    m_matData = matData.m_matData;
    return *this;
}

Matrix &Matrix::operator+(Matrix &matData)
{
    int iRow = matData.GetRowSize();
    int iCol = matData.GetColSize();
    if ((m_iRow == iRow) && (m_iCol == iCol))
    {
        for (int ii = 0; ii < m_iRow; ii++)
        {
            for (int jj = 0; jj < m_iCol; ++jj)
            {
                m_matData[ii][jj] += matData.m_matData[ii][jj];
            }
        }
    }
    else
    {
        ZLOG << "The size is not match; the expect size is " << m_iRow << "; " << m_iCol << "; the actuall size is "
             << iRow << "; " << iCol;
    }
    return *this;
}

Matrix &Matrix::operator-(Matrix &matData)
{
    int iRow = matData.GetRowSize();
    int iCol = matData.GetColSize();
    if ((m_iRow == iRow) && (m_iCol == iCol))
    {
        for (int ii = 0; ii < m_iRow; ii++)
        {
            for (int jj = 0; jj < m_iCol; ++jj)
            {
                m_matData[ii][jj] -= matData.m_matData[ii][jj];
            }
        }
    }
    else
    {
        ZLOG << "The size is not match; the expect size is " << m_iRow << "; " << m_iCol << "; the actuall size is "
             << iRow << "; " << iCol;
    }
    return *this;
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