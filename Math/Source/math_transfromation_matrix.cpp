//
// Created by wei on 2022/4/2.
//

#include "Math/math_transfromation_matrix.h"

TransformMatrix::TransformMatrix() :m_matData(4,4)
{
    m_matData[3][0] = 0.0;
    m_matData[3][1] = 0.0;
    m_matData[3][2] = 0.0;
    m_matData[3][3] = 1.0;
    m_iRow = (this->m_matData).GetRowSize();
    m_iCol = (this->m_matData).GetColSize();
}

Vector<double> TransformMatrix::GetRowVector(unsigned int iRow)
{
    if (iRow > m_iCol)
    {
        ZLOG << " The index is out of range; The limit size is " << m_iCol << "; expect index is " << iRow;
        exit(-1);
    }
    Vector<double> vecDirData(4);
    for (int ii = 0; ii < m_iCol; ii++)
    {
        vecDirData[ii] = (*this)[iRow][ii];
    }
    return vecDirData;
}

Vector<double> TransformMatrix::GetColVector(unsigned int iCol)
{
    if (iCol > m_iRow)
    {
        ZLOG << " The index is out of range; The limit size is " << m_iCol << "; expect index is " << iCol;
        exit(-1);
    }
    Vector<double> vecDirData(4);
    for (int ii = 0; ii < m_iRow; ii++)
    {
        vecDirData[ii] = (*this)[iCol][ii];
    }
    return vecDirData;
}

std::ostream &operator<<(std::ostream &os, TransformMatrix &transData)
{
    int iTemp = 3;
    for (int ii = 0; ii < 4; ii++)
    {
        os << "{";
        for (int jj = 0; jj < 4; jj++)
        {
            os << transData.m_matData[ii][jj];
            if (iTemp != jj)
            {
                os << " ";
            }
        }
        os << "} ";
    }
    return os;
}

Vector<double> &TransformMatrix::operator[](int iIndex)
{
    if ((iIndex > m_iRow) || (iIndex < 0))
    {
        ZLOG << " The index is out of range; The limit size is " << m_iRow << "; expect index is " << iIndex;
        exit(-1);
    }
    return m_matData[iIndex];
}

TransformMatrix TransformMatrix::operator*( TransformMatrix &transData)
{
    TransformMatrix transDirData;
    for (int ii = 0;ii < m_iRow;ii++)
    {
        Vector<double> vecData1 = this->GetRowVector(ii);
        for (int jj = 0; jj < m_iCol; jj++)
        {
            Vector<double> vecData2 = transData.GetColVector(jj);
            transDirData[ii][jj] = vecData1 * vecData2;
        }
    }
    return transDirData;
}

