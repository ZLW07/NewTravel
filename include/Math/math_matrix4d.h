//
// Created by wei on 2022/4/2.
//

#ifndef NEWTRAVEL_MATH_MATRIX4D_H
#define NEWTRAVEL_MATH_MATRIX4D_H

#include "Math/math_matrix.h"
#include "Math/math_rotation.h"

class Matrix4D
{
    friend  std::ostream &operator<<(std::ostream &os, Matrix4D &transData);
public:
    Matrix4D();
    Matrix4D(Rotation rotData,Vector3D v3dData);
    Vector<double> GetRowVector(unsigned int iRow);
    Vector<double> GetColVector(unsigned int iCol);
public:
    Vector<double> &operator[](int iIndex);
    Matrix4D operator*(Matrix4D &tansData);
    Vector3D operator*(Vector3D &v3dData);
    Rotation GetRotation();
    Vector3D GetPose();
    void SwapRow(int iSrcRow, int iDirRow);
    void SetIndentyMatrix();
    bool Inv(Matrix4D transMat);
private:
    Matrix m_matData;
    int m_iRow;
    int m_iCol;
};

#endif // NEWTRAVEL_MATH_MATRIX4D_H
