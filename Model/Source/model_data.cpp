//
// Created by wei on 2022/4/11.
//
#include <fstream>

#include "Model/model_data.h"

ModelManager::ModelManager() {}

ModelManager::~ModelManager() {}

bool ModelManager::LoadModelData(const char *cFileName, std::vector<ModelDataBase> &ModelData)
{
    return ReadAscllSTlFile(cFileName, ModelData);
}

CollisionDectionData ModelManager::GetModelDataVector(std::vector<ModelDataBase> &ModelData)
{

}

bool ModelManager::IsColliding(const CollisionDectionData &oCollisionData)
{
    int iSize = oCollisionData.vecModelNormalVector.size();
    Vector3D v3dTemp;
    Vector3D v3dTemp1;
    Vector3D v3dSurfacePoint1Side1Vector;
    Vector3D v3dSurfacePoint1Side2Vector;
    double dRad = 0.0;
    double dSurfacePoint1SideRad = 0.0;
    double dTargetToSurfacePoint1Side1Rag = 0.0;
    double dTargetToSurfacePoint1Side2Rag = 0.0;
    double dSurfacePoint2SideRad = 0.0;
    double dTargetToSurfacePoint2Side1Rag = 0.0;
    double dTargetToSurfacePoint2Side2Rag = 0.0;
    for (int ii = 0; ii < iSize; ++ii)
    {
        v3dTemp = oCollisionData.vecModelNormalVector.at(ii);
        v3dTemp1= oCollisionData.oSurfacePoint_1.vecTargetPoint.at(ii);
        if (v3dTemp1.Norm() < g_dMaxCheckLength)
        {
            return true;
        }
        dRad = v3dTemp.GetVectorAngleRad(v3dTemp1);
        v3dSurfacePoint1Side1Vector = oCollisionData.oSurfacePoint_1.vecSide_1Vector.at(ii);
        v3dSurfacePoint1Side2Vector = oCollisionData.oSurfacePoint_1.vecSide_2Vector.at(ii);
        double dTargetToSide1Length = 0.0;
        double dTargetToSide2Length = 0.0;
        double dPointVectorLength = v3dTemp1.Norm();
        if ((fabs((dRad - g_dRightAngle)) < g_dNearZero))
        {
            dSurfacePoint1SideRad = v3dSurfacePoint1Side1Vector.GetVectorAngleRad(v3dSurfacePoint1Side2Vector);
            dTargetToSurfacePoint1Side1Rag = v3dTemp1.GetVectorAngleRad(v3dSurfacePoint1Side1Vector);
            dTargetToSurfacePoint1Side2Rag = v3dTemp1.GetVectorAngleRad(v3dSurfacePoint1Side2Vector);
            Vector3D v3dSurfacePoint2Side1 = oCollisionData.oSurfacePoint_2.vecSide_1Vector.at(ii);
            Vector3D v3dSurfacePoint2Side2 = oCollisionData.oSurfacePoint_2.vecSide_2Vector.at(ii);
            Vector3D v3dPointToSurfacePoint2 = oCollisionData.oSurfacePoint_2.vecTargetPoint.at(ii);
            dSurfacePoint2SideRad = v3dSurfacePoint2Side1.GetVectorAngleRad(v3dSurfacePoint2Side2);
            dTargetToSurfacePoint2Side1Rag = v3dPointToSurfacePoint2.GetVectorAngleRad(v3dSurfacePoint2Side1);
            dTargetToSurfacePoint2Side2Rag = v3dPointToSurfacePoint2.GetVectorAngleRad(v3dSurfacePoint2Side2);
            if ((dSurfacePoint1SideRad >= dTargetToSurfacePoint1Side1Rag) && (dSurfacePoint1SideRad >= dTargetToSurfacePoint1Side2Rag)
                 && (dSurfacePoint2SideRad > dTargetToSurfacePoint2Side1Rag) && (dSurfacePoint2SideRad > dTargetToSurfacePoint2Side2Rag))
            {
                dTargetToSide1Length = dPointVectorLength * sin(dTargetToSurfacePoint1Side1Rag);
                dTargetToSide2Length = dPointVectorLength * sin(dTargetToSurfacePoint1Side2Rag);
                if((dTargetToSide1Length <= g_dMaxCheckLength) && (dTargetToSide2Length <= g_dMaxCheckLength))
                {
                    return true;
                }
            }
        }
        else
        {
            double dPointToSurfaceLength = dPointVectorLength *cos(dRad);
            if (fabs(dPointToSurfaceLength) <= g_dMaxCheckLength)
            {
                return  true;
            }
        }
    }
    return false;

}

bool ModelManager::ReadAscllSTlFile(const char *cFileName, std::vector<ModelDataBase> &ModelData)
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
                oDataBase.v3dNormalVector = v3dData;
                iIndex++;
            }
            else if (1 == iIndex)
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
                ModelData.push_back(oDataBase);
                iIndex = 0;
            }
        }
        pCnt++;
    } while (!in.eof());
    return true;
}
