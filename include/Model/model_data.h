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

#include "PQP/PQP.h"

#include <fstream>
namespace zl
{
class ModelManager
{
public:
    ModelManager(){};
    ~ModelManager(){};
public:
    static bool LoadModelData(const char *cFileName, ModelDataElement &oModelData, OBBElement &oOBBData);
    static bool IsColliding(OBBElement &OBB_A, OBBElement &OBB_B, Matrix4 &trans2_1, double tolerance = 0.000001);
    static int IsColliding(PQP_CollideResult &oResult,Matrix4 &trans_1,PQP_Model &oModel_1,Matrix4 &trans_2,PQP_Model &oModel_2);
    static OBBElement GetOBBData(std::vector<Vector3D> &oDataBase);
    static Rotation CovarianceMatrix(std::vector<Vector3D> &vSrc_1);
    static bool BuildPQPModel(PQP_Model *vPQPModel, std::string cFileName);
private:
    static bool ReadAscllSTlFile(const char *cFileName, ModelDataElement &oModelData);
private:
};
}
#endif // NEWTRAVEL_MODEL_DATA_H