//
// Created by wei on 2022/4/11.
//

#ifndef NEWTRAVEL_MODEL_DATA_H
#define NEWTRAVEL_MODEL_DATA_H

#include "Math/math_vector3d.h"


struct ModelDataBase
{
    Vector3D v3dNormalVector;
    Vector3D v3dCoordinate_1;
    Vector3D v3dCoordinate_2;
    Vector3D v3dCoordinate_3;
};

struct CollisionDectionData
{
    std::vector<Vector3D> vecTargetPoint;
    std::vector<Vector3D> vecModelNormalVector;
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
