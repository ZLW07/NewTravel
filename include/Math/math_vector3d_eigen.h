//
// Created by wei on 2022/7/16.
//

#ifndef NEWTRAVEL_MATH_VECTOR3D_EIGEN_H
#define NEWTRAVEL_MATH_VECTOR3D_EIGEN_H

#endif // NEWTRAVEL_MATH_VECTOR3D_EIGEN_H
#include "Eigen/Eigen"

class Vector3DE
{
    friend  std::ostream &operator<<(std::ostream &os, Vector3DE &oVector3DE);
public:
    Vector3DE();
    Vector3DE(double dData_0, double dData_1,double dData_2);
    ~Vector3DE();
    std::pair<Vector3DE, Vector3DE> GetCoordinateExtremum(std::vector<Eigen::Vector3d> &vecData);

public:
    double &operator[](int iIndex);
    Eigen::Vector3d &GetData();
    double &X();
    double &Y();
    double &Z();

private:
    Eigen::Vector3d m_v3d;

};
