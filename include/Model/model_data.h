//
// Created by wei on 2022/4/11.
//

#ifndef NEWTRAVEL_MODEL_DATA_H
#define NEWTRAVEL_MODEL_DATA_H

#include "Math/math_vector3d.h"
const double g_dRightAngle = 1.5707963;
const double g_dNearZero = 0.0001;
const double g_dMaxCheckLength = 1.5;

struct ModelDataBase
{
    Vector3D v3dNormalVector;
    Vector3D v3dCoordinate_1;
    Vector3D v3dCoordinate_2;
    Vector3D v3dCoordinate_3;
};

struct DetectionBase
{
    std::vector<Vector3D> vecTargetPoint;
    std::vector<Vector3D> vecSide_1Vector;
    std::vector<Vector3D> vecSide_2Vector;
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
    bool LoadModelData(const char* cFileName, std::vector<ModelDataBase> &ModelData);
    CollisionDectionData GetModelDataVector(Vector3D &V3dPoint,std::vector<ModelDataBase> &ModelData);
    bool IsColliding(const CollisionDectionData &oCollisionData);
private:
    bool ReadAscllSTlFile(const char* cFileName,std::vector<ModelDataBase> &ModelData);
private:
};

#endif // NEWTRAVEL_MODEL_DATA_H
