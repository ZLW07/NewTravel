//
// Created by wei on 2022/5/15.
//
#include "Math/math_vector3d.h"

/*                                                        VectorD3 : [0;0;0]                                        */


VectorD3::VectorD3()
{
    m_vecD3 = Vector<double>(3);
}

VectorD3::VectorD3(const VectorD3 &v3dData)
{
    m_vecD3 = v3dData.m_vecD3;
}

VectorD3::VectorD3(double dData1, double dData2, double dData3)
{
    m_vecD3.push_back(dData1);
    m_vecD3.push_back(dData2);
    m_vecD3.push_back(dData2);
    m_vecD3.push_back(dData2);
}

double & VectorD3::operator[](int iIndex)
{
    if ((iIndex > 3) || (iIndex < 0))
    {
        ZLOG << " The index is out of range; the actual index is " << iIndex << "; the limit index is " << 3;
        exit(1);
    }
    return m_vecD3[iIndex];
}

std::ostream &operator<<(std::ostream &os, VectorD3 &vd3Data)
{
    for (int ii = 0; ii < 3; ++ii)
    {
        os << vd3Data[ii] << " ";
    }
    return os;
}

void VectorD3::Clear()
{
    m_vecD3.Clear();
}

Vector<double> &VectorD3::GetVectorValue()
{
    return m_vecD3;
}
VectorD3::~VectorD3() {}
