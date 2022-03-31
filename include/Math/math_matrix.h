//
// Created by zw on 2021/10/16.
//

#ifndef NEWTRAVEL_MATH_MATRIX_H
#define NEWTRAVEL_MATH_MATRIX_H

#include "Log/log.h"

#include <iostream>
#include <vector>

class Vector
{
    friend  std::ostream &operator<<(std::ostream &os,const Vector & vData);
public:
    explicit Vector(int iSize = 1);
    ~Vector();
    double &operator[](int iIndex) ;
    Vector &operator=(Vector vecData);
    void SetSize(int iSize);
private:
    std::vector<double> m_vecData;
    int m_iVecSize;
};

class Matrix
{
    friend  std::ostream &operator<<(std::ostream &os, Matrix &matData);
public:
    explicit Matrix(int iRow, int iCol = 1);
    ~Matrix();
    Vector &operator[](int iIndex);
    int GetRowSize() const;
    int GetColSize() const;

private:
    int m_iRow;
    int m_iCol;
    std::vector<Vector> m_matData;
};

#endif // NEWTRAVEL_MATH_MATRIX_H
