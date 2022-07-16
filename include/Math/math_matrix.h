//
// Created by zw on 2021/10/16.
//

#ifndef NEWTRAVEL_MATH_MATRIX_H
#define NEWTRAVEL_MATH_MATRIX_H

#include "Log/log.h"

#include <iostream>
#include <vector>
#include <cmath>

#define MEAN(data_1, mean_1,data_3,mean_2)  (data_1 - mean_1)*(data_3 - mean_2)

template<typename T>
class Vector
{
    friend std::ostream &operator<<(std::ostream &os,const Vector<T> &vData)
    {
        for (int ii = 0; ii < vData.m_iVecSize; ii++)
        {
            os << vData.m_vecData[ii] << " ";
        }
        return os;
    }
public:
    explicit Vector(int iSize = 1);
    double Norm2()
    {
            double dResult = 0.0;
            for (int ii = 0; ii < m_iVecSize; ++ii)
            {
                dResult = dResult + pow(m_vecData[ii],2);
            }
            return sqrt(dResult);
    }
    Vector(const Vector<T> &vecData):m_iVecSize(vecData.m_iVecSize)
    {
        m_vecData.resize(m_iVecSize);
        m_vecData.assign(vecData.m_vecData.begin(),vecData.m_vecData.end());
    }

    int Size()
    {
        return m_vecData.size();
    }

    void Clear()
    {
        m_iVecSize = 0;
        m_vecData.clear();
    }

    ~Vector();

public:
    T &operator[](int iIndex)
    {
        if (iIndex > m_iVecSize)
        {
            ZLOG << " The index is out of range; The limit size is " << m_iVecSize << "; expect index is " << iIndex;
            exit(-1);
        }
        return m_vecData.at(iIndex);
    }

    Vector<T> &operator=(Vector<T> vecData)
    {
        m_iVecSize = vecData.m_iVecSize;
        m_vecData = vecData.m_vecData;
        return *this;
    }

    Vector<T> operator+(Vector<T> vecData)
    {
        if (m_iVecSize != vecData.Size())
        {
            ZLOG << " The size is not match;  m_iVecSize: " << m_iVecSize ;
            exit(1);
        }
        Vector<T> vecResult(m_iVecSize);
        for (int ii = 0; ii < m_iVecSize; ++ii)
        {
            vecResult[ii] = m_vecData[ii] + vecData[ii];
        }
        return vecResult;
    }


    Vector<T> &operator*(T tData)
    {
        Vector<T> vecResult(m_iVecSize);
        for (int ii = 0; ii < m_iVecSize; ++ii)
        {
            vecResult[ii] = m_vecData[ii] + tData;
        }
        return vecResult;
    }


    Vector<T> push_back(T tData)
    {
            m_vecData.push_back(tData);
            m_iVecSize++;
            return *this;
    }

    T operator*(Vector<T> vecData)
    {
        if (this->m_iVecSize != vecData.m_iVecSize)
        {
            ZLOG << "the size is not match";
            exit(1);
        }
        T tTemp;
        for (int ii = 0; ii < m_iVecSize;ii++)
        {
            T dDirData = m_vecData[ii] * vecData[ii];
            if (0 == ii)
            {
                tTemp = dDirData;
            }
            else
            {
                tTemp = tTemp + dDirData;
            }
        }
        return tTemp;
    }

private:
    std::vector<T> m_vecData;
    int m_iVecSize;
};


class Matrix
{
    friend  std::ostream &operator<<(std::ostream &os, Matrix &matData);
public:
    explicit Matrix(int iRow, int iCol);
    Matrix(const Matrix &matData);
    ~Matrix();
    int GetRowSize() const;
    int GetColSize() const;
    void SetIdentityMatrix();
public:
    Vector<double> &operator[](int iIndex);
    Matrix &operator+(Matrix &matData);
    Matrix &operator-(Matrix &matData);
    Matrix &operator=(const Matrix &matData);
    Matrix operator*(Matrix &matData);
    Matrix Dot(Vector<double> &vecData_1, Vector<double> vecData_2);
    Matrix Dot(double dData);
    Vector<double> GetColVector(int iCol, int iIndexRow = 0);
    Vector<double> GetRowVector(int iRow, int iIndexCol = 0);
public:
private:
    int m_iRow;
    int m_iCol;
    std::vector<Vector<double>> m_matData;
};

#endif // NEWTRAVEL_MATH_MATRIX_H
