//
// Created by wei on 2022/4/2.
//

#ifndef NEWTRAVEL_MATH_TRANSFROMATION_MATRIX_H
#define NEWTRAVEL_MATH_TRANSFROMATION_MATRIX_H

#include "Math/math_matrix.h"

class TransformMatrix
{
    friend  std::ostream &operator<<(std::ostream &os, TransformMatrix &transData);
public:
    TransformMatrix();
    Vector<double> GetRowVector(unsigned int iRow);
    Vector<double> GetColVector(unsigned int iCol);
public:
    Vector<double> &operator[](int iIndex);
    TransformMatrix operator*(TransformMatrix &tansData);
private:
    Matrix m_matData;
    int m_iRow;
    int m_iCol;
};

#endif // NEWTRAVEL_MATH_TRANSFROMATION_MATRIX_H
