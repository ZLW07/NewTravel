//
// Created by wei on 2022/4/2.
//

#include "Math/math_transfromation_matrix.h"

TransformMatrix::TransformMatrix() : m_matData(4, 4)
{
    m_matData[3][0] = 0.0;
    m_matData[3][1] = 0.0;
    m_matData[3][2] = 0.0;
    m_matData[3][3] = 1.0;
    m_iRow = (this->m_matData).GetRowSize();
    m_iCol = (this->m_matData).GetColSize();
}

TransformMatrix::TransformMatrix(Rotation rotData, Vector3D v3dData) : m_matData(4, 4)
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

Rotation TransformMatrix::GetRotation()
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

Vector3D TransformMatrix::GetTranslate()
{
    Vector3D oResult;
    for (int iRow = 0; iRow < 3; ++iRow)
    {
        oResult[iRow] = m_matData[iRow][3];
    }
    return oResult;
}

void TransformMatrix::SwapRow(int iSrcRow, int iDirRow)
{
    double dValue = 0.0;
    for (int ii = 0; ii < m_iCol; ++ii)
    {
        dValue = m_matData[iSrcRow][ii];
        m_matData[iSrcRow][ii] = m_matData[iDirRow][ii];
        m_matData[iDirRow][ii] = dValue;
    }
}

void TransformMatrix::SetEye()
{
    m_matData.SetEye();
}

bool TransformMatrix::Inv(TransformMatrix &transMat)
{
    SetEye(); //创建单位矩阵
    //下来进行自上而下的初等行变换，使得矩阵 a.mat 变成单位上三角矩阵
    for (int i = 0; i < m_iCol; i++) //注意这里要 i<=m，和之前的上三角矩阵有不同
    { //因为要判断最后一行化为上三角矩阵的最后一行最后一列元素是否为 0
        //寻找第 i 列不为零的元素
        int k;
        for (k = i; k < m_iRow; k++)
        {
            if (fabs(transMat[k][i]) < 1e-10) //满足这个条件时，认为这个元素不为0
            {
                ZLOG << "不可逆！";
                return false;
            }
            break;
        }
        if (k < m_iRow) //说明第 i 列有不为0的元素
        {
            if (k != i) //说明第 i 行 第 i 列元素为零，需要和其他行交换
            {
                //交换第 i 行和第 k 行所有元素
                transMat.SwapRow(k,i);
                SwapRow(k,i);

            }
            double b = transMat[i][i]; //倍数
            //将矩阵 a.mat 的主对角线元素化为 1
            for (int j = k; j < m_iCol; j++) //从第一个元素开始
            {
                transMat[i][j] =  transMat[i][j]/ b;
                m_matData[i][j] = m_matData[i][j]/ b;
            }
            for (int ij = k + 1; ij < m_iRow; ij++)
            {
                b = -transMat[ij][i];
                for (int jj = k; jj < m_iCol; jj++)
                {
                    transMat[ij][jj] = b * transMat[k][ij] + ; //第 i 行 b 倍加到第 j 行
                    m_matData[jj][i] = b * m_matData[i][k];
                }
            }
        }
        else
        {
            ZLOG << "不可逆！";
            return false;
        }
    }

    //下面进行自下而上的行变换，将 a.mat 矩阵化为单位矩阵
    for (int i = m_iRow; i > 1; i--)
    {
        for (int j = i - 1; j >= 1; j--)
        {
            double b = -transMat[j][i];
            transMat[j][i] = 0; //实际上是通过初等行变换将这个元素化为 0,
            for (int k = 0; k < m_iCol; k++)
            { //通过相同的初等行变换来变换右边矩阵
                m_matData[j][k] += b * m_matData[i][k];
            }
        }
    }
    return true;
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

TransformMatrix TransformMatrix::operator*(TransformMatrix &transData)
{
    TransformMatrix transDirData;
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

Vector3D TransformMatrix::operator*(Vector3D &v3dData)
{
    Rotation rotTempResult = GetRotation();
    Vector3D v3dTempResult = GetTranslate();
    Vector3D v3dResult = rotTempResult * v3dData + v3dTempResult;
    return v3dResult;
}