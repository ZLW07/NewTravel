//
// Created by zw on 2021/10/16.
//

#ifndef NEWTRAVEL_MATH_MATRIX_H
#define NEWTRAVEL_MATH_MATRIX_H

#include <iostream>
#include <vector>
#include <math.h>
#include <iomanip>

#include "Log/log.h"

class CheckZero
    {
    public:
        bool NearZero(const double &dData)
        {
            if (std::abs(dData) < 1e-6)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    };


class Se3Matrix;
class Matrix : public CheckZero
{
    friend std::ostream &operator<<(std::ostream &out, Matrix &oMatrix);
public:
    Matrix(int iRow, int iCol);
    Matrix(int iRow, int iCol, double dInitialValue);
    ~Matrix();
    void Initial();
    int GetRow();
    int GetCol();
    Matrix(const Matrix &oMatrix);

    double* operator[](int iIndex) const;
    Matrix operator* (const Matrix &oMatrix);
    Matrix &operator=(const Matrix &oMatrix);
    void operator*(double dData);
    double Norm2();
    Matrix SetEyeMatrix(int iSize);

private:
    int m_iRow;
    int m_iCol;
    double **m_pVector;
};

#endif // NEWTRAVEL_MATH_MATRIX_H
