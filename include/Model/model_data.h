//
// Created by wei on 2022/7/16.
//

#ifndef NEWTRAVEL_MODEL_DATA_H
#define NEWTRAVEL_MODEL_DATA_H

#include "Eigen/Eigen"
#include "protocol.h"
#include "Math/math_matrix4.h"
#include "Math/math_vector3d.h"
#include "Math/math_rotation.h"
#include <fstream>
namespace zl
{
class ModelManager
{
public:
    ModelManager(){};
    ~ModelManager(){};
    bool LoadModelData(const char *cFileName, ModelDataElement &oModelData, OBBElement &oOBBData);

public:
    static bool IsColliding(OBBElement &OBB_A, OBBElement &OBB_B, Matrix4 &trans2_1, double tolerance = 0.000001);
     static OBBElement GetOBBData(std::vector<Vector3D> &oDataBase);
    static Rotation CovarianceMatrix(std::vector<Vector3D> &vSrc_1);
private:
    bool ReadAscllSTlFile(const char *cFileName, ModelDataElement &oModelData);
private:
};
}
#endif // NEWTRAVEL_MODEL_DATA_H