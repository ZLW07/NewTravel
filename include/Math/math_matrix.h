//
// Created by zw on 2021/10/16.
//

#ifndef NEWTRAVEL_MATH_MATRIX_H
#define NEWTRAVEL_MATH_MATRIX_H
#include <iostream>
#include <vector>

class Vector
{
public:
    Vector();
    ~Vector();
    double &operator[](int iIndex);
    static void SetSize(int iSize);
private:
    double *m_pVec;
    static int m_iVecSize;
};

class Matrix
{
public:
    Matrix(int iRow, int iCol = 0);
    ~Matrix();
    Vector &operator[](int iIndex);
private:
    Vector *m_pVector;
    int m_iHeight;
};

#endif // NEWTRAVEL_MATH_MATRIX_H
