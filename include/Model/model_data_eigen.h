//
// Created by wei on 2022/7/16.
//

#ifndef NEWTRAVEL_MODEL_DATA_EIGEN_H
#define NEWTRAVEL_MODEL_DATA_EIGEN_H

#endif // NEWTRAVEL_MODEL_DATA_EIGEN_H
#include <fstream>
#include "Eigen/Eigen"
#include "Math/math_rotation_eigen.h"
#include "Math/math_matrix4_eigen.h"

struct ModelDataElement
{
    std::vector<Eigen::Vector3d> v3dNormalVector;
    std::vector<Eigen::Vector3d> vecPoint;

};

struct OBBElement
{
    Vector3DE v3dCenterPoint;
    RotationE     rotBaseVector;
    Vector3DE v3dOBBLength;
};

class ModelManagerE
{
public:
    ModelManagerE(){};
    ~ModelManagerE(){};
    bool LoadModelDataE(const char* cFileName, ModelDataElement& oModelData, OBBElement &oOBBData);
    OBBElement GetModelOBBDataVector(ModelDataElement &oDataBase);
    bool IsColliding( OBBElement &OBB_A,  OBBElement &OBB_B, Matrix4E &trans2_1);
private:
    bool ReadAscllSTlFileE(const char *cFileName, ModelDataElement &oModelData);
private:
};