//
// Created by wei on 2022/4/11.
//
#include <fstream>

#include "Model/model_data.h"

ModelManager::ModelManager() {}

ModelManager::~ModelManager() {}

bool ModelManager::LoadModelData(const char *cFileName, OBBData &oOBBData)
{
    ModelDataBase oModelData;
    if (!ReadAscllSTlFile(cFileName, oModelData))
    {
        return false;
    }
    oOBBData = GetModelDataVector(oModelData);
    return true;
}

OBBData ModelManager::GetModelDataVector(ModelDataBase &oDataBase)
{
    OBBData oOBBData;
    Rotation rotRot;
    auto Point = oDataBase.vecPoint;
    rotRot.Cov(Point);
    oOBBData.rotBaseVector = GetOBBDirectionVector(rotRot);
    Rotation oTranspose = oOBBData.rotBaseVector.Transpose();
    std::vector<Vector3D> vecUVWPoint;
    vecUVWPoint.resize(Point.size());
    for (int ij = 0; ij < Point.size(); ++ij)
    {
        for (int jj = 0; jj < 3.; ++jj)
        {
            vecUVWPoint[ij][jj] = oDataBase.vecPoint[ij].GetVectorValue() * oTranspose.GetColVector(jj).GetVectorValue();
        }
    }
    Vector3D v3dT;
    auto MaxAndMinPoint = v3dT.GetCoordinateExtremum(vecUVWPoint);
    Vector3D v3dLength(0.5 * (MaxAndMinPoint.second[0] - MaxAndMinPoint.first[0]),
        0.5 * (MaxAndMinPoint.second[1] - MaxAndMinPoint.first[1]),
        0.5 * (MaxAndMinPoint.second[2] - MaxAndMinPoint.first[2]));
    Vector3D v3dCenterPoint_UVW(0.5 * (MaxAndMinPoint.first[0] + MaxAndMinPoint.second[0]),
        0.5 * (MaxAndMinPoint.first[1] + MaxAndMinPoint.second[1]),
        0.5 * (MaxAndMinPoint.first[2] + MaxAndMinPoint.second[2]));
    oOBBData.v3dOBBLength = v3dLength;
    oOBBData.v3dCenterPoint = oOBBData.rotBaseVector * v3dCenterPoint_UVW;
    return oOBBData;
}

bool ModelManager::IsColliding(const OBBData &OOBB_1, const OBBData &OBB_2)
{
    return false;
}

bool ModelManager::ReadAscllSTlFile(const char *cFileName, ModelDataBase &ModelData)
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
    return true;
}
