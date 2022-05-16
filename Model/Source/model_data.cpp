//
// Created by wei on 2022/4/11.
//
#include <fstream>

#include "Model/model_data.h"

ModelManager::ModelManager() {}

ModelManager::~ModelManager() {}

bool ModelManager::LoadModelData(const char* cFileName, OBBData &oOBBData)
{
    return ReadAscllSTlFile(cFileName, oOBBData);
}

CollisionDectionData ModelManager::GetModelDataVector(std::vector<ModelDataBase> &ModelData) {}

bool ModelManager::IsColliding(const OBBData &OOBB_1, const OBBData &OBB_2)
{
    return false;
}

bool ModelManager::ReadAscllSTlFile(const char *cFileName, OBBData &oOBBData)
{
    Vector3D v3dData;
    ModelDataBase oDataBase;
    int i = 0, j = 0, cnt = 0, pCnt = 4;
    char a[100];
    char str[100];
    int iIndex = 0;
    std::ifstream in;
    in.open(cFileName, std::ios::in);
    if (!in)
        return false;
    do
    {
        i = 0;
        cnt = 0;
        in.getline(a, 100, '\n');
        while (a[i] != '\0')
        {
            if (!islower((int)a[i]) && !isupper((int)a[i]) && a[i] != ' ')
                break;
            cnt++;
            i++;
        }

        while (a[cnt] != '\0')
        {
            str[j] = a[cnt];
            cnt++;
            j++;
        }
        str[j] = '\0';
        j = 0;
        if (sscanf(str, "%lf%lf%lf", &v3dData[0], &v3dData[1], &v3dData[2]) == 3)
        {
            if (0 == iIndex)
            {
                oDataBase.v3dNormalVector.push_back(v3dData);
                iIndex++;
            }
            else if (1 == iIndex)
            {
                oDataBase.vecPoint.push_back(v3dData);
                iIndex++;
            }
            else if (2 == iIndex)
            {
                oDataBase.vecPoint.push_back(v3dData);
                iIndex++;
            }
            else if (3 == iIndex)
            {
                oDataBase.vecPoint.push_back(v3dData);
                iIndex = 0;
            }
        }
        pCnt++;
    } while (!in.eof());
    Rotation rotRot;
    rotRot.Cov(oDataBase.vecPoint);
    oOBBData.rotBaseVector = GetOBBDirectionVector(rotRot);
    std::vector<Vector3D> vecUVWPoint;
    vecUVWPoint.resize(oDataBase.vecPoint.size());
    for (int ij = 0; ij < oDataBase.vecPoint.size(); ++ij)
    {
        for (int jj = 0; jj < 3.; ++jj)
        {
            vecUVWPoint[ij][jj] = oDataBase.vecPoint[ij].GetVectorValue() * rotRot.GetColVector(jj).GetVectorValue();
        }
    }
    return true;
}
