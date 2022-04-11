//
// Created by wei on 2022/4/11.
//
#include <fstream>

#include "Model/model_data.h"

ModelData::ModelData() {}

ModelData::~ModelData() {}

bool ModelData::ReadAscllSTlFile(const char *cFileName)
{
    Vector3D v3dData;
    ModelDataBase oDataBase;
    int i = 0, j = 0, cnt = 0, pCnt = 4;
    char a[100];
    char str[100];
    double x = 0, y = 0, z = 0;
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
                oDataBase.v3dNormalVector = v3dData;
                iIndex++;
            }
            else if(1 == iIndex)
            {
                oDataBase.v3dCoordinate_1 = v3dData;
                iIndex++;
            }
            else if (2 == iIndex)
            {
                oDataBase.v3dCoordinate_2 = v3dData;
                iIndex++;
            }
            else if (3 == iIndex)
            {
                oDataBase.v3dCoordinate_3 = v3dData;
                m_vModelData.push_back(oDataBase);
                iIndex =0;
            }
        }
        pCnt++;
    } while (!in.eof());
    return true;
}

std::vector<ModelDataBase> ModelData::GetPointCoordinateValue()
{
    return m_vModelData;
}