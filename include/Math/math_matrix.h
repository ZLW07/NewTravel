//
// Created by zw on 2021/10/16.
//

#ifndef NEWTRAVEL_MATH_MATRIX_H
#define NEWTRAVEL_MATH_MATRIX_H

#include "Log/log.h"

#include <iostream>
#include <vector>

template<typename T>
class Vector;

template<typename T>
std::ostream &operator<<(std::ostream &os,const Vector<T> &vData);

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
    Vector(const Vector<T> &vecData):m_iVecSize(vecData.m_iVecSize)
    {
        this->m_vecData = vecData.m_vecData;
    }
    ~Vector();
public:
    T &operator[](int iIndex) ;
    Vector<T> &operator=(Vector<T> vecData);

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
    explicit Matrix(int iRow, int iCol = 1);
    ~Matrix();
    int GetRowSize() const;
    int GetColSize() const;
public:
    Vector<double> &operator[](int iIndex);
    Matrix &operator+(Matrix &matData);
    Matrix &operator-(Matrix &matData);
    Matrix &operator=(const Matrix &matData);
private:
    int m_iRow;
    int m_iCol;
    std::vector<Vector<double>> m_matData;
};

#endif // NEWTRAVEL_MATH_MATRIX_H
