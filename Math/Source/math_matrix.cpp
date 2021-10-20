//
// Created by zw on 2021/10/16.
//

#include "Math/math_matrix.h"

void Matrix::Initial()
{
    m_pVector = new double *[m_iRow];
    for (int ii = 0; ii < m_iRow; ii++)
    {
        m_pVector[ii] = new double[m_iCol];
    }
}

Matrix::Matrix(int iRow, int iCol)
{
    m_iRow = iRow;
    m_iCol = iCol;
    Initial();
    for (int ii = 0; ii < m_iRow; ii++)
    {
        for (int jj = 0; jj < m_iCol; jj++)
        {
            m_pVector[ii][jj] = 0.0;
        }
    }
}

Matrix::Matrix(int iRow, int iCol, double dInitialValue)
{
    m_iRow = iRow;
    m_iCol = iCol;
    Initial();
    for (int ii = 0; ii < m_iRow; ii++)
    {
        for (int jj = 0; jj < m_iCol; jj++)
        {
            m_pVector[ii][jj] = dInitialValue;
        }
    }
}

Matrix::~Matrix()
{
    for (int ii = 0; ii < m_iRow; ii++)
    {
        if (m_pVector[ii])
        {
            delete[] m_pVector[ii];
            m_pVector[ii] = nullptr;
        }
    }
    if (m_pVector)
    {
        delete[] m_pVector;
        m_pVector = nullptr;
    }
}

Matrix::Matrix(const Matrix &oMatrix)
{
    if (this == &oMatrix)
    {
        return;
    }
    if (m_iRow != oMatrix.m_iRow || m_iCol != oMatrix.m_iCol)
    {
        for (int ii = 0; ii < m_iRow; ii++)
        {
            if (m_pVector[ii])
            {
                delete[] m_pVector[ii];
                m_pVector[ii] = nullptr;
            }
        }
        if (m_pVector)
        {
            delete[] m_pVector;
            m_pVector = nullptr;
        }

        m_iRow = oMatrix.m_iRow;
        m_iCol = oMatrix.m_iCol;
        Initial();
    }
    for (int ii = 0; ii < m_iRow; ii++)
    {
        for (int jj = 0; jj < m_iCol; jj++)
        {
            m_pVector[ii][jj] = oMatrix[ii][jj];
        }
    }
}

double *Matrix::operator[](int iIndex) const
{
    if (iIndex > m_iRow)
    {
        ZLOG << " The input size is out of max index";
        ZLOG << " The max index is " << (m_iRow - 1);
        ZLOG << " The input index is " << iIndex;
        exit(-1);
    }
    return m_pVector[iIndex];
}

int Matrix::GetRow()
{
    return m_iRow;
}

int Matrix::GetCol()
{
    return m_iCol;
}

std::ostream &operator<<(std::ostream &out, Matrix &oMatrix)
{
    out << "The Matrix is \n" ;
    for (int ii = 0; ii < oMatrix.m_iRow; ii++)
    {
        for (int jj = 0; jj < oMatrix.m_iCol; jj++)
        {
            double dValue = oMatrix[ii][jj];
            if (std::abs(dValue) < 1e-3)
            {
                out << std::setw(5) << 0.0;
            }
            else
            {
                out << std::setw(5) << dValue;
            }

        }
        out << std::endl;
    }
    return out;
}

Matrix Matrix::operator*(const Matrix &oMatrix)
{
    Matrix oResultMatrix(m_iRow, oMatrix.m_iCol);
    if (m_iCol != oMatrix.m_iRow)
    {
        exit(-1);
    }
    for (int jj = 0; jj < m_iRow; jj++)
    {
        int iMaxCol = oMatrix.m_iCol;
        for (int ij = 0; ij < iMaxCol; ij++)
        {
            double dValue = 0.0;
            for (int ii = 0; ii < m_iCol; ii++)
            {
                dValue = m_pVector[jj][ii] * oMatrix[ii][ij] + dValue;
            }
            oResultMatrix[jj][ij] = dValue;
        }
    }
    return oResultMatrix;
}

Matrix &Matrix::operator=(const Matrix &oMatrix)
{
    if (this == &oMatrix)
    {
        return *this;
    }
    if (m_iRow != oMatrix.m_iRow || m_iCol != oMatrix.m_iCol)
    {
        for (int ii = 0; ii < m_iRow; ii++)
        {
            if (m_pVector[ii])
            {
                delete[] m_pVector[ii];
                m_pVector[ii] = nullptr;
            }
        }
        if (m_pVector)
        {
            delete[] m_pVector;
            m_pVector = nullptr;
        }

        m_iRow = oMatrix.m_iRow;
        m_iCol = oMatrix.m_iCol;
        Initial();
    }
    for (int ii = 0; ii < m_iRow; ii++)
    {
        for (int jj = 0; jj < m_iCol; jj++)
        {
            m_pVector[ii][jj] = oMatrix[ii][jj];
        }
    }
    return *this;
}

double Matrix::Norm2()
{
    double dValue = 0.0;
    for (unsigned ii = 0; ii < m_iCol; ii++)
    {
        for (unsigned jj = 0; jj < m_iRow; jj++)
        {
            dValue = pow((*this)[jj][ii], 2) + dValue;
        }
    }
    dValue = pow(dValue, 0.5);
    return dValue;
}

Matrix Matrix::SetEyeMatrix(int iSize)
{
    Matrix oResultMat(iSize,iSize);
    for (int ii = 0; ii < iSize; ii++)
    {
        oResultMat[ii][ii] = 1.0;
    }
    return oResultMat;
}
