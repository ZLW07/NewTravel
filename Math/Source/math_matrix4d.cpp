//
// Created by wei on 2022/4/2.
//

#include "Math/math_matrix4d.h"

Matrix4D::Matrix4D() : m_matData(4, 4)
{
    m_matData[3][0] = 0.0;
    m_matData[3][1] = 0.0;
    m_matData[3][2] = 0.0;
    m_matData[3][3] = 1.0;
    m_iRow = (this->m_matData).GetRowSize();
    m_iCol = (this->m_matData).GetColSize();
}

Matrix4D::Matrix4D(Rotation rotData, Vector3D v3dData) : m_matData(4, 4)
{
    for (int iRow = 0; iRow < 3; ++iRow)
    {
        for (int iCol = 0; iCol < 3; ++iCol)
        {
            m_matData[iRow][iCol] = rotData[iRow][iCol];
        }
        m_matData[iRow][3] = v3dData[iRow];
    }
    m_matData[3][0] = 0.0;
    m_matData[3][1] = 0.0;
    m_matData[3][2] = 0.0;
    m_matData[3][3] = 1.0;
    m_iRow = 4;
    m_iCol = 4;
}

Vector<double> Matrix4D::GetRowVector(unsigned int iRow)
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

Vector<double> Matrix4D::GetColVector(unsigned int iCol)
{
    if (iCol > m_iRow)
    {
        ZLOG << " The index is out of range; The limit size is " << m_iCol << "; expect index is " << iCol;
        exit(-1);
    }
    Vector<double> vecDirData(4);
    for (int ii = 0; ii < m_iRow; ii++)
    {
        vecDirData[ii] = (*this)[ii][iCol];
    }
    return vecDirData;
}

Rotation Matrix4D::GetRotation()
{
    Rotation oResult;
    for (int iRow = 0; iRow < 3; iRow++)
    {
        for (int iCol = 0; iCol < 3; iCol++)
        {
            oResult[iRow][iCol] = m_matData[iRow][iCol];
        }
    }
    return oResult;
}

Vector3D Matrix4D::GetPose()
{
    Vector3D oResult;
    for (int iRow = 0; iRow < 3; ++iRow)
    {
        oResult[iRow] = m_matData[iRow][3];
    }
    return oResult;
}

void Matrix4D::SwapRow(int iSrcRow, int iDirRow)
{
    double dValue = 0.0;
    for (int ii = 0; ii < m_iCol; ++ii)
    {
        dValue = m_matData[iSrcRow][ii];
        m_matData[iSrcRow][ii] = m_matData[iDirRow][ii];
        m_matData[iDirRow][ii] = dValue;
    }
}

void Matrix4D::SetIndentyMatrix()
{
    m_matData.SetIdentityMatrix();
}

bool Matrix4D::Inv(Matrix4D transMat)
{
    SetIndentyMatrix(); //创建单位矩阵
    //下来进行自上而下的初等行变换，使得矩阵 a.mat 变成单位上三角矩阵
    for (int ii = 0; ii < m_iCol; ii++) //注意这里要 i<=m，和之前的上三角矩阵有不同
    { //因为要判断最后一行化为上三角矩阵的最后一行最后一列元素是否为 0
      //寻找第 i 列不为零的元素
        int ij = ii;
        while (ij < m_iRow)
        {
            if (fabs(transMat[ij][ii]) > 1e-10) //满足这个条件时，认为这个元素不为0
            {
                break;
            }
            ij++;
        }
        if (ij >= m_iRow)
        {
            ZLOG << " there is no inv";
            return false;
        }
        if (ij != ii) //说明第 i 行 第 i 列元素为零，需要和其他行交换
        {
            //交换第 i 行和第 k 行所有元素
            transMat.SwapRow(ij, ii);
            SwapRow(ij, ii);
        }
        double b = transMat[ii][ii]; //倍数
        //将矩阵 a.mat 的主对角线元素化为 1
        for (int jj = ij; jj < m_iCol; jj++) //从第一个元素开始
        {
            transMat[ii][jj] = transMat[ii][jj] / b;
        }
        for (int jj = 0; jj < m_iCol; ++jj)
        {
            m_matData[ii][jj] = m_matData[ii][jj] / b;
        }
        for (int a = 0; a < m_iRow; a++)
        {
            if (a != ii)
            {
                b = -transMat[a][ii];
                for (int bb = ii; bb < m_iCol; bb++)
                {
                    transMat[a][bb] = b * transMat[ii][bb] + transMat[a][bb]; //第 i 行 b 倍加到第 j 行
                }
                for (int cc = 0; cc < m_iCol; ++cc)
                {
                    m_matData[a][cc] = b * m_matData[ii][cc] + m_matData[a][cc];
                }
            }
        }
    }
    return true;
}

std::ostream &operator<<(std::ostream &os, Matrix4D &transData)
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

Vector<double> &Matrix4D::operator[](int iIndex)
{
    if ((iIndex > m_iRow) || (iIndex < 0))
    {
        ZLOG << " The index is out of range; The limit size is " << m_iRow << "; expect index is " << iIndex;
        exit(-1);
    }
    return m_matData[iIndex];
}

Matrix4D Matrix4D::operator*(Matrix4D &transData)
{
    Matrix4D transDirData;
    for (int ii = 0; ii < m_iRow; ii++)
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

Vector3D Matrix4D::operator*(Vector3D &v3dData)
{
    Rotation rotTempResult = GetRotation();
    Vector3D v3dTempResult = GetPose();
    Vector3D v3dResult = rotTempResult * v3dData + v3dTempResult;
    return v3dResult;
}