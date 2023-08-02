//
// Created by wei on 2022/7/16.
//

#include "../../Include/Model/model_data.h"
#include "../../Include/Log/log.h"
#include "../../Include/Math/math_matrix4.h"

namespace zl
{
bool ModelManager::ReadAscllSTlFile(const char *cFileName, ModelDataElement &oModelData)
{
    Vector3D v3dData;
    TriangleData oTriangleData;
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
                oModelData.v3dNormalVector.push_back(v3dData);
                iIndex++;
            }
            else if (1 == iIndex)
            {
                oTriangleData.avPoint[0] = v3dData;
                iIndex++;
            }
            else if (2 == iIndex)
            {
                oTriangleData.avPoint[1] = v3dData;
                iIndex++;
            }
            else if (3 == iIndex)
            {
                oTriangleData.avPoint[2] = v3dData;
                oModelData.vecPoint.push_back(oTriangleData);
                iIndex = 0;
            }
        }
        pCnt++;
    } while (!in.eof());
    return true;
}

bool ModelManager::LoadModelData(const char *cFileName, ModelDataElement &oModelData, OBBElement &oOBBData)
{
    if (!ReadAscllSTlFile(cFileName, oModelData))
    {
        return false;
    }
    auto oData = oModelData.TriangularPointCloud();
    oOBBData = GetOBBData(oData);
    return true;
}

#define MEAN(data_1, mean_1, data_3, mean_2) (data_1 - mean_1) * (data_3 - mean_2)

Rotation ModelManager::CovarianceMatrix(std::vector<Vector3D> &vSrc_1)
{
    Rotation oRot;
    int iSize = vSrc_1.size();
    double tMean_1 = 0.0;
    double tMean_2 = 0.0;
    double tMean_3 = 0.0;
    for (int jj = 0; jj < iSize; jj++)
    {
        tMean_1 = tMean_1 + vSrc_1[jj].X();
        tMean_2 = tMean_2 + vSrc_1[jj].Y();
        tMean_3 = tMean_3 + vSrc_1[jj].Z();
    }
    tMean_1 = tMean_1 / iSize;
    tMean_2 = tMean_2 / iSize;
    tMean_3 = tMean_3 / iSize;
    for (int ij = 0; ij < iSize; ++ij)
    {
        oRot(0, 0) = MEAN(vSrc_1[ij].X(), tMean_1, vSrc_1[ij].X(), tMean_1) + oRot(0, 0);
        oRot(0, 1) = MEAN(vSrc_1[ij].X(), tMean_1, vSrc_1[ij].Y(), tMean_2) + oRot(0, 1);
        oRot(0, 2) = MEAN(vSrc_1[ij].X(), tMean_1, vSrc_1[ij].Z(), tMean_3) + oRot(0, 2);
        oRot(1, 0) = MEAN(vSrc_1[ij].Y(), tMean_2, vSrc_1[ij].X(), tMean_1) + oRot(1, 0);
        oRot(1, 1) = MEAN(vSrc_1[ij].Y(), tMean_2, vSrc_1[ij].Y(), tMean_2) + oRot(1, 1);
        oRot(1, 2) = MEAN(vSrc_1[ij].Y(), tMean_2, vSrc_1[ij].Z(), tMean_3) + oRot(1, 2);
        oRot(2, 0) = MEAN(vSrc_1[ij].Z(), tMean_3, vSrc_1[ij].X(), tMean_1) + oRot(2, 0);
        oRot(2, 1) = MEAN(vSrc_1[ij].Z(), tMean_3, vSrc_1[ij].Y(), tMean_2) + oRot(2, 1);
        oRot(2, 2) = MEAN(vSrc_1[ij].Z(), tMean_3, vSrc_1[ij].Z(), tMean_3) + oRot(2, 2);
    }
    return (oRot / (iSize - 1));
}

OBBElement ModelManager::GetOBBData(std::vector<Vector3D> &oDataBase)
{
    OBBElement oOBBData;
    Rotation rotRot = CovarianceMatrix(oDataBase);
    oOBBData.rotBaseVector = oOBBData.rotBaseVector.GetOBBDirectionVector(rotRot);
    Rotation oTranspose = oOBBData.rotBaseVector.Inverse();
    std::vector<Vector3D> vecUVWPoint;
    vecUVWPoint.resize(oDataBase.size());
    Eigen::RowVector3d vd3Data;
    for (int ij = 0; ij < oDataBase.size(); ++ij)
    {
        vd3Data = Eigen::RowVector3d(oDataBase[ij][0], oDataBase[ij][1], oDataBase[ij][2]);
        vecUVWPoint[ij].GetData() = vd3Data * oTranspose.GetData();
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

bool ModelManager::IsColliding(OBBElement &OBB_A, OBBElement &OBB_B, Matrix4 &transOBB, double tolerance)
{
    Matrix4 transBB1(OBB_A.rotBaseVector, OBB_A.v3dCenterPoint);
    Matrix4 transBB2(OBB_B.rotBaseVector, OBB_B.v3dCenterPoint);
    Matrix4 oInvTransBB1 = transBB1.Inv();
    Matrix4 tranBaseBToA = oInvTransBB1 * transOBB * transBB2;
    Rotation rotBToA = tranBaseBToA.GetRotation();
    Vector3D v3dBToAPose = tranBaseBToA.GetPose();
    double dRa = 0.0;
    double dRb = 0.0;
    double dT = 0.0;
    // test axes L = A0 ; A1; A2
    bool bIsColliding = false;
    for (int ii = 0; ii < 3; ++ii)
    {
        dRa = OBB_A.v3dOBBLength[ii];
        dRb = (OBB_B.v3dOBBLength[0] * fabs(rotBToA[ii][0]) + OBB_B.v3dOBBLength[1] * fabs(rotBToA[ii][1]) +
               OBB_B.v3dOBBLength[2] * fabs(rotBToA[ii][2]));
        if (std::fabs(v3dBToAPose[ii]) > (dRa + dRb + tolerance))
        {
            return bIsColliding;
        }
    }

    // test axes L = B0 ; B1; B2
    for (int ij = 0; ij < 3; ++ij)
    {
        dRa = (OBB_A.v3dOBBLength[0] * fabs(rotBToA[0][ij]) + OBB_A.v3dOBBLength[1] * fabs(rotBToA[1][ij]) +
               OBB_A.v3dOBBLength[2] * fabs(rotBToA[2][ij]));
        dRb = OBB_B.v3dOBBLength[ij];
        if (std::fabs(v3dBToAPose[0] * rotBToA[0][ij] + v3dBToAPose[1] * rotBToA[1][ij] +
                      v3dBToAPose[2] * rotBToA[2][ij]) > (dRa + dRb + tolerance))
        {
            return bIsColliding;
        }
    }

    // u0_A X u0_B  1
    dT = fabs(v3dBToAPose.Z() * rotBToA[1][0] - v3dBToAPose.Y() * rotBToA[2][0]);
    dRa = OBB_A.v3dOBBLength[1] * fabs(rotBToA[2][0]) + OBB_A.v3dOBBLength[2] * fabs(rotBToA[1][0]);
    dRb = OBB_B.v3dOBBLength[1] * fabs(rotBToA[0][2]) + OBB_B.v3dOBBLength[2] * fabs(rotBToA[0][1]);
    if (dT > (dRa + dRb + tolerance))
    {
        return bIsColliding;
    }

    // u0_A X u1_B  2
    dT = fabs(v3dBToAPose.Z() * rotBToA[1][1] - v3dBToAPose.Y() * rotBToA[2][1]);
    dRa = OBB_A.v3dOBBLength[1] * fabs(rotBToA[2][1]) + OBB_A.v3dOBBLength[2] * fabs(rotBToA[1][1]);
    dRb = OBB_B.v3dOBBLength.X() * fabs(rotBToA[0][2]) + OBB_B.v3dOBBLength.Z() * fabs(rotBToA[0][0]);
    if (dT > (dRa + dRb + tolerance))
    {
        return bIsColliding;
    }

    // u0_A X u2_B  3
    dT = fabs(v3dBToAPose.Z() * rotBToA[1][2] - v3dBToAPose.Y() * rotBToA[2][2]);
    dRa = OBB_A.v3dOBBLength.Y() * fabs(rotBToA[2][2]) + OBB_A.v3dOBBLength.Z() * fabs(rotBToA[1][2]);
    dRb = OBB_B.v3dOBBLength.X() * fabs(rotBToA[0][1]) + OBB_B.v3dOBBLength.Y() * fabs(rotBToA[0][0]);
    if (dT > (dRa + dRb + tolerance))
    {
        return bIsColliding;
    }

    // u1_A X u0_B   4
    dT = fabs(v3dBToAPose.X() * rotBToA[2][0] - v3dBToAPose.Z() * fabs(rotBToA[0][0]));
    dRa = OBB_A.v3dOBBLength.X() * fabs(rotBToA[2][0]) + OBB_A.v3dOBBLength.Z() * fabs(rotBToA[0][0]);
    dRb = OBB_B.v3dOBBLength.Y() * fabs(rotBToA[1][2]) + OBB_B.v3dOBBLength.Z() * fabs(rotBToA[1][1]);
    if (dT > (dRa + dRb + tolerance))
    {
        return bIsColliding;
    }

    // u1_A X u1_B  5
    dT = fabs(v3dBToAPose.X() * fabs(rotBToA[2][1]) - v3dBToAPose.Z() * fabs(rotBToA[0][1]));
    dRa = OBB_A.v3dOBBLength.X() * fabs(rotBToA[2][1]) + OBB_A.v3dOBBLength.Z() * fabs(rotBToA[0][1]);
    dRb = OBB_B.v3dOBBLength.X() * fabs(rotBToA[1][2]) + OBB_B.v3dOBBLength.Z() * fabs(rotBToA[1][0]);
    if (dT > (dRa + dRb + tolerance))
    {
        return bIsColliding;
    }

    // u1_A X u2_B  6
    dT = fabs(v3dBToAPose.X() * rotBToA[2][2] - v3dBToAPose.Z() * rotBToA[0][2]);
    dRa = OBB_A.v3dOBBLength.X() * fabs(rotBToA[2][2] + OBB_A.v3dOBBLength.Z() * fabs(rotBToA[0][2]));
    dRb = OBB_B.v3dOBBLength.X() * fabs(rotBToA[1][1]) + OBB_B.v3dOBBLength.Y() * fabs(rotBToA[1][0]);
    if (dT > (dRa + dRb + tolerance))
    {
        return bIsColliding;
    }

    // u2_A X u0_B  7
    dT = fabs(v3dBToAPose.Y() * rotBToA[0][0] - v3dBToAPose.X() * rotBToA[1][0]);
    dRa = OBB_A.v3dOBBLength.X() * fabs(rotBToA[1][0]) + OBB_A.v3dOBBLength.Y() * fabs(rotBToA[0][0]);
    dRb = OBB_B.v3dOBBLength.Y() * fabs(rotBToA[2][2]) + OBB_B.v3dOBBLength.Z() * fabs(rotBToA[2][1]);
    if (dT > (dRa + dRb + tolerance))
    {
        return bIsColliding;
    }

    // u2_A X u1_B  8
    dT = fabs(v3dBToAPose.Y() * rotBToA[0][2] - v3dBToAPose.X() * rotBToA[1][1]);
    dRa = OBB_A.v3dOBBLength.X() * fabs(rotBToA[1][1]) + OBB_A.v3dOBBLength.Y() * fabs(rotBToA[0][1]);
    dRb = OBB_B.v3dOBBLength.X() * fabs(rotBToA[2][2]) + OBB_B.v3dOBBLength.Z() * fabs(rotBToA[2][0]);
    if (dT > (dRa + dRb + tolerance))
    {
        return bIsColliding;
    }

    // u2_A X u2_B  9
    dT = fabs(v3dBToAPose.Y() * rotBToA[0][2] - v3dBToAPose.X() * rotBToA[1][2]);
    dRa = OBB_A.v3dOBBLength.X() * fabs(rotBToA[1][2]) + OBB_A.v3dOBBLength.Y() * fabs(rotBToA[0][2]);
    dRb = OBB_B.v3dOBBLength.X() * fabs(rotBToA[2][1]) + OBB_B.v3dOBBLength.Y() * fabs(rotBToA[2][0]);
    if (dT > (dRa + dRb + tolerance))
    {
        return bIsColliding;
    }
    return true;
}

int ModelManager::IsColliding(
    PQP_CollideResult &oResult, Matrix4 &trans_1, PQP_Model &oModel_1, Matrix4 &trans_2, PQP_Model &oModel_2)
{
    double aRot_1[3][3];
    double aRot_2[3][3];
    double aPose_1[3];
    double aPose_2[3];
    for (int ii = 0; ii < 3; ++ii)
    {
        for (int jj = 0; jj < 3; ++jj)
        {
            //            aRot_1[ii][jj] = trans_1[ii][jj];
            //            aRot_2[ii][jj] = trans_2[ii][jj];
        }
        //        aPose_1[ii]= trans_1[ii][3];
        //        aPose_2[ii]= trans_2[ii][3];
    }
    return PQP_Collide(&oResult, aRot_1, aPose_1, &oModel_1, aRot_2, aPose_2, &oModel_2);
}

bool ModelManager::BuildPQPModel(PQP_Model *pPQPModel, std::string cFileName)
{
    ModelDataElement oModelData;
    if (!ReadAscllSTlFile(cFileName.c_str(), oModelData))
    {
        return false;
    }
    std::vector<Vector3D> vSrc_1 = oModelData.TriangularPointCloud();
    ZLOG << "Start build model";
    pPQPModel->BeginModel(vSrc_1.size());
    int iIndex = 0;
    for (int ii = 0; ii < vSrc_1.size(); ++ii)
    {
        double p1[3] ={vSrc_1[ii].X(),vSrc_1[ii].Y(),vSrc_1[ii].Z()};
        double p2[3] ={vSrc_1[ii + 1].X(),vSrc_1[ii + 1].Y(),vSrc_1[ii + 1].Z()};
        double p3[3] ={vSrc_1[ii + 2].X(),vSrc_1[ii + 2].Y(),vSrc_1[ii + 2].Z()};
        pPQPModel->AddTri(p1, p2, p3, iIndex);
        ii = ii + 2;
        iIndex = iIndex + 1;
    }
    pPQPModel->EndModel();
    return true;
}

} // namespace zl