//
// Created by wei on 2023/3/3.
//

#ifndef NEWTRAVEL_PROTOCOL_H
#define NEWTRAVEL_PROTOCOL_H

#include "Math/math_rotation.h"
#include "Math/math_vector3d.h"

namespace zl
{
#define TRIANGLULAT_POINT_COUNT 3
struct TriangleData
{
    Vector3D avPoint[TRIANGLULAT_POINT_COUNT];
};
struct ModelDataElement
{
    std::vector<Vector3D> v3dNormalVector;
    std::vector<TriangleData> vecPoint;
    std::vector<Vector3D> TriangularPointCloud()
    {
        std::vector<Vector3D> vecData;
        for (int ii = 0; ii < v3dNormalVector.size(); ++ii)
        {
            for (int jj = 0; jj < TRIANGLULAT_POINT_COUNT; ++jj)
            {
//                vecData.push_back(Vector3D(vecPoint[ii].avPoint[jj][0] * 1000, vecPoint[ii].avPoint[jj][1] * 1000,
//                    vecPoint[ii].avPoint[jj][2] * 1000));
                vecData.push_back(vecPoint[ii].avPoint[jj]);
            }
        }
        return vecData;
    }
};

struct OBBElement
{
    Vector3D v3dCenterPoint;
    Rotation rotBaseVector;
    Vector3D v3dOBBLength;
};

} // namespace zl

#endif // NEWTRAVEL_PROTOCOL_H
