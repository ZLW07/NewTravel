////
//// Created by zw on 2021/10/16.
////

#ifndef NEWTRAVEL_MATH_VECTOR3D_H
#define NEWTRAVEL_MATH_VECTOR3D_H

#include <vector>

#include "Math/math_matrix.h"

class Vector6D
{
public:
    Vector6D();
    Vector6D(double dData1, double dData2, double dData3, double dData4, double dData5, double dData6);
    double &operator[](unsigned int iIndex);

private:
    Matrix m_oV6D;
};

class VectorD3;

class Vector3D
{
    friend std::ostream &operator<<(std::ostream &out, Vector3D &oVector3D);
public:
    Vector3D();
    ~Vector3D();
    Vector3D(double dData1, double dData2, double dData3);
    Vector3D(const Vector3D &oVector3D);

    double &operator[](unsigned int uiIndex) const;
    double &operator*(const Vector3D &oVector3D);
    Vector3D &operator*(const double &dData);
    Vector3D &operator+(const Vector3D &dData);
    Vector3D &GetVectorCross(const Vector3D &oVector3D);
    Matrix GetSkewSymmetric();
    Vector6D GetScrewAxis(Vector3D &v3dPoint, Vector3D &v3dDirection, double dPitch);
    double Nom2();
private:
    Matrix m_oV3D;
};

class VectorD3
    {
    friend std::ostream &operator<<(std::ostream &out, VectorD3 &oVectorD3);
    public:
        VectorD3();
        ~VectorD3();
        VectorD3(double dData1, double dData2, double dData3);
        VectorD3(const VectorD3 &oVectorD3);
        double &operator[](unsigned int uiIndex) const;
        double operator*(Vector3D &oVector3D);
    private:
        Matrix m_oVD3;
    };

#endif // NEWTRAVEL_MATH_VECTOR3D_H
