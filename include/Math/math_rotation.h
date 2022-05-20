//
// Created by wei on 2022/4/23.
//

#ifndef NEWTRAVEL_MATH_ROTATION_H
#define NEWTRAVEL_MATH_ROTATION_H

#include "Math/math_matrix.h"
#include "Math/math_vector3d.h"

class Rotation
{
    friend  std::ostream &operator<<(std::ostream &os, Rotation &rotData);
public:
    Rotation();
    Rotation(Vector3D &v3dColData_1,Vector3D &v3dColData_2,Vector3D &v3dColData_3);
    Rotation(const Rotation &rotData);
    ~Rotation()= default;
    Vector3D operator*(Vector3D &v3dData);
    Rotation operator/(double dData);
    Rotation operator/(int dData);
    Vector<double> &operator[](int iIndex);
public:
    Rotation CombinationTransformMatrix(Matrix &srcMat);
    VectorD3 GetColVector(unsigned int iCol);
    Vector3D GetRowVector(unsigned int iRow);
    Vector<double> GetColVector(unsigned int uiBeginRow, unsigned int iCol);
    Rotation Dot(VectorD3 &vd3Data, Vector3D &v3dData);
    double Dot(Vector3D &vd3Data, VectorD3 &v3dData);
    Matrix &GetMatValue();
    Rotation ConversionMatToRot(Matrix &matData);
    Rotation Cov(std::vector<Vector3D> &vSrc_1);
    Rotation Transpose();
    void SetEye();
public:
private:
    Matrix m_matData;
    int m_iRow;
    int m_iCol;
};

#endif // NEWTRAVEL_MATH_ROTATION_H
