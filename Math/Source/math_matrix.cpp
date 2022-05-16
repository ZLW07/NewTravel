//
// Created by zw on 2021/10/16.
//

#include "Math/math_matrix.h"
template <typename T> Vector<T>::Vector(int iSize)
{
    m_iVecSize = iSize;
    m_vecData.resize(m_iVecSize, 0.0);
}

template <typename T> Vector<T>::~Vector() = default;

Matrix::Matrix(int iRow, int iCol)
{
    m_iRow = iRow;
    m_iCol = iCol;
    std::vector<Vector<double>> vData(m_iRow, Vector<double>(m_iCol));
    m_matData = vData;
}

Matrix::Matrix(const Matrix &matData)
{
    m_iRow = matData.m_iRow;
    m_iCol = matData.m_iCol;
    m_matData.assign(matData.m_matData.begin(), matData.m_matData.end());
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

void Matrix::SetEye()
{
    for (int ii = 0; ii < m_iRow; ++ii)
    {
        m_matData[ii][ii] = 1.0;
    }
}

Vector<double> &Matrix::operator[](int iIndex)
{
    return m_matData.at(iIndex);
}

Matrix &Matrix::operator=(const Matrix &matData)
{
    m_iCol = matData.GetColSize();
    m_iRow = matData.GetRowSize();
    m_matData.assign(matData.m_matData.begin(), matData.m_matData.end());
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

Matrix Matrix::operator*(Matrix &matData)
{
    if ((this->m_iCol != matData.m_iRow))
    {
        ZLOG << "The size is not match";
        exit(1);
    }
    Matrix oMat(m_iRow, matData.m_iCol);
    for (int ii = 0; ii < m_iRow; ++ii)
    {
        for (int ij = 0; ij < matData.m_iCol; ++ij)
        {
            oMat[ii][ij] = this->GetRowVector(ii) * matData.GetRowVector(ij);
        }
    }
    return oMat;
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

Matrix Matrix::Dot(Vector<double> &vecData_1, Vector<double> vecData_2)
{
    int iRow = vecData_1.Size();
    int iCol = vecData_2.Size();
    for (int ii = 0; ii < iRow; ++ii)
    {
        for (int ij = 0; ij < iCol; ++ij)
        {
            m_matData[ii][ij] = vecData_1[ii] * vecData_2[ij];
        }
    }
    return *this;
}

Matrix Matrix::Dot(double dData)
{
    for (int ii = 0; ii < m_iRow; ++ii)
    {
        for (int ij = 0; ij < m_iCol; ++ij)
        {
            m_matData[ii][ij] = m_matData[ii][ij] * dData;
        }
    }
    return *this;
}

Vector<double> Matrix::GetRowVector(int iRow, int iIndexCol)
{
    Vector<double> vecResult(this->m_iCol - iIndexCol);
    for (int ii = iIndexCol; ii < this->m_iCol; ++ii)
    {
        vecResult[ii] = m_matData[iRow][ii];
    }
    return vecResult;
}

Vector<double> Matrix::GetColVector(int iCol, int iIndexRow)
{
    Vector<double> vecResult(this->m_iRow - iIndexRow);
    for (int ii = iIndexRow; ii < this->m_iCol; ++ii)
    {
        vecResult[ii - iIndexRow] = m_matData[ii][iCol];
    }
    return vecResult;
}