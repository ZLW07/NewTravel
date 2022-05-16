//
// Created by zw on 2021/10/16.
//

#ifndef NEWTRAVEL_MATH_VECTOR3D_H
#define NEWTRAVEL_MATH_VECTOR3D_H

#include <math.h>
#include <vector>

#include "Math/math_matrix.h"

class VectorD3;

class Vector3D
{
    friend std::ostream &operator<<(std::ostream &os, Vector3D &v3dData);
public:
    Vector3D();
    Vector3D(double dData1, double dData2, double dData3);
    Vector3D(const Vector3D &v3dData);
    Matrix GetSkewSymmetricMatrix();
    double X();
    double Y();
    double Z();
public:
    double &operator[](int iIndex);
    Vector3D operator+(Vector3D &v3dData);
    Vector3D operator-( Vector3D &v3dData);
    bool operator==(Vector3D &v3dData) ;
    Vector3D Scale(double dData);
    double Dot(Vector3D &v3dData);
    Vector3D Cross(Vector3D &v3dData);
    double Norm();
    double GetVectorAngleRad(Vector3D &v3dData);
    double GetVectorAngleDeg(Vector3D &v3dData);
    void Clear();
    Vector<double> &GetVectorValue();
    std::pair<Vector3D,Vector3D> GetCoordinateExtremum(std::vector<Vector3D> &vecData);

private:
    Vector<double> m_vecV3D;
};


class VectorD3
{
    friend std::ostream &operator<<(std::ostream &os, VectorD3 &v3dData);
public:
    VectorD3();
    VectorD3(double dData1, double dData2, double dData3);
    VectorD3(const VectorD3 &v3dData);
    double &operator[](int iIndex);
public:
    void Clear();
    Vector<double> &GetVectorValue();
private:
    Vector<double> m_vecD3;
};

#endif // NEWTRAVEL_MATH_VECTOR3D_H
