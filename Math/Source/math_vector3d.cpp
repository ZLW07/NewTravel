//
// Created by wei on 2022/7/16.
//
#include "Log/log.h"
#include "Math/math_vector3d.h"

namespace zl
{
Vector3D::Vector3D()
{
    m_v3d = Eigen::Vector3d::Zero();
}

Vector3D::Vector3D(double dData_0, double dData_1, double dData_2)
{
    m_v3d = Eigen::Vector3d{dData_0, dData_1, dData_2};
}

Vector3D::Vector3D(Eigen::Vector3d v3dData)
{
    m_v3d = v3dData;
}

Vector3D::~Vector3D() {}

std::ostream &operator<<(std::ostream &os, Vector3D &oVector3DE)
{
    os << oVector3DE.GetData();
    return os;
}

double &Vector3D::operator[](int iIndex)
{
    return m_v3d[iIndex];
}

Eigen::Vector3d &Vector3D::GetData()
{
    return m_v3d;
}

double &Vector3D::X()
{
    return m_v3d.x();
}

double &Vector3D::Y()
{
    return m_v3d.y();
}

double &Vector3D::Z()
{
    return m_v3d.z();
}

std::pair<Vector3D, Vector3D> Vector3D::GetCoordinateExtremum(std::vector<Vector3D> &vecData)
{
    double dMin_X = vecData[0][0];
    double dMin_Y = vecData[0][1];
    double dMin_Z = vecData[0][2];
    double dMax_X = vecData[0][0];
    double dMax_Y = vecData[0][1];
    double dMax_Z = vecData[0][2];

    for (int ii = 0; ii < vecData.size(); ++ii)
    {
        if (dMin_X > vecData[ii][0])
        {
            dMin_X = vecData[ii][0];
        }
        if (dMax_X < vecData[ii][0])
        {
            dMax_X = vecData[ii][0];
        }

        if (dMin_Y > vecData[ii][1])
        {
            dMin_Y = vecData[ii][1];
        }
        if (dMax_Y < vecData[ii][1])
        {
            dMax_Y = vecData[ii][1];
        }

        if (dMin_Z > vecData[ii][2])
        {
            dMin_Z = vecData[ii][2];
        }
        if (dMax_Z < vecData[ii][2])
        {
            dMax_Z = vecData[ii][2];
        }
    }
    Vector3D v3dMin(dMin_X, dMin_Y, dMin_Z);
    Vector3D v3dMax(dMax_X, dMax_Y, dMax_Z);
    return std::make_pair(v3dMin, v3dMax);
}
}