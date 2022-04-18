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

class ModelManager
{
public:
    ModelManager();
    ~ModelManager();
    bool LoadModelData(const char* cFileName, std::vector<ModelDataBase> &ModelData);
private:
    bool ReadAscllSTlFile(const char* cFileName,std::vector<ModelDataBase> &ModelData);
private:
};

#endif // NEWTRAVEL_MODEL_DATA_H
