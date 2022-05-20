//
// Created by wei on 2022/4/2.
//

#ifndef NEWTRAVEL_MATH_TRANSFROMATION_MATRIX_H
#define NEWTRAVEL_MATH_TRANSFROMATION_MATRIX_H

#include "Math/math_matrix.h"
#include "Math/math_rotation.h"

class TransformMatrix
{
    friend  std::ostream &operator<<(std::ostream &os, TransformMatrix &transData);
public:
    TransformMatrix();
    TransformMatrix(Rotation rotData,Vector3D v3dData);
    Vector<double> GetRowVector(unsigned int iRow);
    Vector<double> GetColVector(unsigned int iCol);
public:
    Vector<double> &operator[](int iIndex);
    TransformMatrix operator*(TransformMatrix &tansData);
    Vector3D operator*(Vector3D &v3dData);
    Rotation GetRotation();
    Vector3D GetPoseTranslate();
    void SwapRow(int iSrcRow, int iDirRow);
    void SetEye();
    bool Inv(TransformMatrix transMat);
private:
    Matrix m_matData;
    int m_iRow;
    int m_iCol;
};

#endif // NEWTRAVEL_MATH_TRANSFROMATION_MATRIX_H
