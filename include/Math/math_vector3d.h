//
// Created by wei on 2022/7/16.
//

#ifndef NEWTRAVEL_MATH_VECTOR3D_EIGEN_H
#define NEWTRAVEL_MATH_VECTOR3D_EIGEN_H


#include "Eigen/Eigen"

namespace zl
{
class Vector3D
{
    friend std::ostream &operator<<(std::ostream &os, Vector3D &oVector3DE);
public:
    Vector3D();
    Vector3D(double dData_0, double dData_1, double dData_2);
    Vector3D(Eigen::Vector3d v3dData);
    ~Vector3D();
    std::pair<Vector3D, Vector3D> GetCoordinateExtremum(std::vector<Vector3D> &vecData);

public:
    double &operator[](int iIndex);
    Eigen::Vector3d &GetData();
    double &X();
    double &Y();
    double &Z();

private:
    Eigen::Vector3d m_v3d;
};
}
#endif // NEWTRAVEL_MATH_VECTOR3D_EIGEN_H