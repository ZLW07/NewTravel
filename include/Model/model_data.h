//
// Created by wei on 2022/4/11.
//

#ifndef NEWTRAVEL_MODEL_DATA_H
#define NEWTRAVEL_MODEL_DATA_H

#include "Math/math_vector3d.h"
#include "Math/math_linear_algebra.h"

const double g_dRightAngle = 1.5707963;
const double g_dNearZero = 0.0001;
const double g_dMaxCheckLength = 1.5;

struct ModelDataBase
{
    std::vector<Vector3D> v3dNormalVector;
    std::vector<Vector3D> vecPoint;
};

struct OBBData
{
    Vector3D v3dCenterPoint;
    Rotation rotBaseVector;
    Vector3D v3dOBBLength;
};

struct DetectionBase
{
    std::vector<Vector3D> vecTargetPoint;
    std::vector<Vector3D> vecSide_1Vector;
    std::vector<Vector3D> vecSide_2Vector;
    std::vector<Vector3D> vecSide_3Vector;
};

struct CollisionDectionData
{
    std::vector<Vector3D> vecModelNormalVector;
    DetectionBase oSurfacePoint_1;
    DetectionBase oSurfacePoint_2;


};

class ModelManager
{
public:
    ModelManager();
    ~ModelManager();
    bool LoadModelData(const char* cFileName, OBBData &oOBBData);
    CollisionDectionData GetModelDataVector(std::vector<ModelDataBase> &ModelData);
    bool IsColliding(const OBBData &OOBB_1, const OBBData &OBB_2);
private:
    bool ReadAscllSTlFile(const char* cFileName,OBBData &oOBBData);
private:
};

#endif // NEWTRAVEL_MODEL_DATA_H
