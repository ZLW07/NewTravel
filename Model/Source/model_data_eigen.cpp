//
// Created by wei on 2022/7/16.
//

#include "Model/model_data_eigen.h"
#include "Math/math_matrix4_eigen.h"
#include "Log/log.h"

bool ModelManagerE::ReadAscllSTlFileE(const char *cFileName, ModelDataElement &oModelData)
{
    Eigen::Vector3d v3dData;
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
                oModelData.vecPoint.push_back(v3dData);
                iIndex++;
            }
            else if (2 == iIndex)
            {
                oModelData.vecPoint.push_back(v3dData);
                iIndex++;
            }
            else if (3 == iIndex)
            {
                oModelData.vecPoint.push_back(v3dData);
                iIndex = 0;
            }
        }
        pCnt++;
    } while (!in.eof());
    return true;
}

bool ModelManagerE::LoadModelDataE(const char *cFileName, ModelDataElement &oModelData, OBBElement &oOBBData)
{
    if (!ReadAscllSTlFileE(cFileName, oModelData))
    {
        return false;
    }
    oOBBData = GetModelOBBDataVector(oModelData);
    return true;
}

OBBElement ModelManagerE::GetModelOBBDataVector(ModelDataElement &oDataBase)
{
    OBBElement oOBBData;
    RotationE rotRot;
    auto Point = oDataBase.vecPoint;
    rotRot.CovarianceMatrix(Point);
    oOBBData.rotBaseVector = oOBBData.rotBaseVector.GetOBBDirectionVector(rotRot);
    RotationE oTranspose = oOBBData.rotBaseVector.Inverse();
    std::vector<Eigen::Vector3d> vecUVWPoint;
    vecUVWPoint.resize(Point.size());
    Eigen::RowVector3d vd3Data;
    for (int ij = 0; ij < Point.size(); ++ij)
    {
        vd3Data = Eigen::RowVector3d(oDataBase.vecPoint[ij][0],oDataBase.vecPoint[ij][1],oDataBase.vecPoint[ij][2]);
        vecUVWPoint[ij]  =   vd3Data * oTranspose.GetData();
    }
    Vector3DE v3dT;
    auto MaxAndMinPoint = v3dT.GetCoordinateExtremum(vecUVWPoint);
    Vector3DE v3dLength(0.5 * (MaxAndMinPoint.second[0] - MaxAndMinPoint.first[0]),
                              0.5 * (MaxAndMinPoint.second[1] - MaxAndMinPoint.first[1]),
                              0.5 * (MaxAndMinPoint.second[2] - MaxAndMinPoint.first[2]));
    Vector3DE v3dCenterPoint_UVW(0.5 * (MaxAndMinPoint.first[0] + MaxAndMinPoint.second[0]),
                                       0.5 * (MaxAndMinPoint.first[1] + MaxAndMinPoint.second[1]),
                                       0.5 * (MaxAndMinPoint.first[2] + MaxAndMinPoint.second[2]));
    oOBBData.v3dOBBLength = v3dLength;
    oOBBData.v3dCenterPoint = oOBBData.rotBaseVector * v3dCenterPoint_UVW;
    return oOBBData;
}

bool ModelManagerE::IsColliding(OBBElement &OBB_A, OBBElement &OBB_B, Matrix4E &transOBB)
{
    Matrix4E transBB1(OBB_A.rotBaseVector, OBB_A.v3dCenterPoint);
    Matrix4E transBB2(OBB_B.rotBaseVector, OBB_B.v3dCenterPoint);
    Matrix4E oInvTransBB1 = transBB1.Inv();
    Matrix4E tranBaseBToA = oInvTransBB1 * transOBB * transBB2;
    RotationE rotBToA = tranBaseBToA.GetRotation();
    Vector3DE v3dBToAPose = tranBaseBToA.GetPose();
    double dRa = 0.0;
    double dRb = 0.0;
    double dT = 0.0;
    // test axes L = A0 ; A1; A2
    for (int ii = 0; ii < 3; ++ii)
    {
        dRa = OBB_A.v3dOBBLength[ii];
        dRb = (OBB_B.v3dOBBLength[0] * fabs(rotBToA[ii][0]) + OBB_B.v3dOBBLength[1] * fabs(rotBToA[ii][1]) +
               OBB_B.v3dOBBLength[2] * fabs(rotBToA[ii][2]));
        if (std::fabs(v3dBToAPose[ii]) > (dRa + dRb))
        {
            return false;
        }
    }

    // test axes L = B0 ; B1; B2
    for (int ij = 0; ij < 3; ++ij)
    {
        dRa = (OBB_A.v3dOBBLength[0] * fabs(rotBToA[0][ij]) + OBB_A.v3dOBBLength[1] * fabs(rotBToA[1][ij]) +
               OBB_A.v3dOBBLength[2] * fabs(rotBToA[2][ij]));
        dRb = OBB_B.v3dOBBLength[ij];
        if (std::fabs(v3dBToAPose[0] * rotBToA[0][ij] + v3dBToAPose[1] * rotBToA[1][ij] +
                      v3dBToAPose[2] * rotBToA[2][ij]) > (dRa + dRb))
        {
            return false;
        }
    }

    // u0_A X u0_B  1
    dT = fabs(v3dBToAPose.Z() * rotBToA[1][0] - v3dBToAPose.Y() * rotBToA[2][0]);
    dRa = OBB_A.v3dOBBLength[1] * fabs(rotBToA[2][0]) + OBB_A.v3dOBBLength[2] * fabs(rotBToA[1][0]);
    dRb = OBB_B.v3dOBBLength[1] * fabs(rotBToA[0][2]) + OBB_B.v3dOBBLength[2] * fabs(rotBToA[0][1]);
    if (dT > (dRa + dRb))
    {
        return false;
    }

    // u0_A X u1_B  2
    dT = fabs(v3dBToAPose.Z() * rotBToA[1][1] - v3dBToAPose.Y() * rotBToA[2][1]);
    dRa = OBB_A.v3dOBBLength[1] * fabs(rotBToA[2][1]) + OBB_A.v3dOBBLength[2] * fabs(rotBToA[1][1]);
    dRb = OBB_B.v3dOBBLength.X() * fabs(rotBToA[0][2]) + OBB_B.v3dOBBLength.Z() * fabs(rotBToA[0][0]);
    if (dT > (dRa + dRb))
    {
        return false;
    }

    // u0_A X u2_B  3
    dT = fabs(v3dBToAPose.Z() * rotBToA[1][2] - v3dBToAPose.Y() * rotBToA[2][2]);
    dRa = OBB_A.v3dOBBLength.Y() * fabs(rotBToA[2][2]) + OBB_A.v3dOBBLength.Z() * fabs(rotBToA[1][2]);
    dRb = OBB_B.v3dOBBLength.X() * fabs(rotBToA[0][1]) + OBB_B.v3dOBBLength.Y() * fabs(rotBToA[0][0]);
    if (dT > (dRa + dRb))
    {
        return false;
    }

    // u1_A X u0_B   4
    dT = fabs(v3dBToAPose.X() * rotBToA[2][0] - v3dBToAPose.Z() * fabs(rotBToA[0][0]));
    dRa = OBB_A.v3dOBBLength.X() * fabs(rotBToA[2][0]) + OBB_A.v3dOBBLength.Z() * fabs(rotBToA[0][0]);
    dRb = OBB_B.v3dOBBLength.Y() * fabs(rotBToA[1][2]) + OBB_B.v3dOBBLength.Z() * fabs(rotBToA[1][1]);
    if (dT > (dRa + dRb))
    {
        return false;
    }

    // u1_A X u1_B  5
    dT = fabs(v3dBToAPose.X() * fabs(rotBToA[2][1]) - v3dBToAPose.Z() * fabs(rotBToA[0][1]));
    dRa = OBB_A.v3dOBBLength.X() * fabs(rotBToA[2][1]) + OBB_A.v3dOBBLength.Z() * fabs(rotBToA[0][1]);
    dRb = OBB_B.v3dOBBLength.X() * fabs(rotBToA[1][2]) + OBB_B.v3dOBBLength.Z() * fabs(rotBToA[1][0]);
    if (dT > (dRa + dRb))
    {
        return false;
    }

    // u1_A X u2_B  6
    dT = fabs(v3dBToAPose.X() * rotBToA[2][2] - v3dBToAPose.Z() * rotBToA[0][2]);
    dRa = OBB_A.v3dOBBLength.X() * fabs(rotBToA[2][2] + OBB_A.v3dOBBLength.Z() * fabs(rotBToA[0][2]));
    dRb = OBB_B.v3dOBBLength.X() * fabs(rotBToA[1][1]) + OBB_B.v3dOBBLength.Y() * fabs(rotBToA[1][0]);
    if (dT > (dRa + dRb))
    {
        return false;
    }

    // u2_A X u0_B  7
    dT = fabs(v3dBToAPose.Y() * rotBToA[0][0] - v3dBToAPose.X() * rotBToA[1][0]);
    dRa = OBB_A.v3dOBBLength.X() * fabs(rotBToA[1][0]) + OBB_A.v3dOBBLength.Y() * fabs(rotBToA[0][0]);
    dRb = OBB_B.v3dOBBLength.Y() * fabs(rotBToA[2][2]) + OBB_B.v3dOBBLength.Z() * fabs(rotBToA[2][1]);
    if (dT > (dRa + dRb))
    {
        return false;
    }

    // u2_A X u1_B  8
    dT = fabs(v3dBToAPose.Y() * rotBToA[0][2] - v3dBToAPose.X() * rotBToA[1][1]);
    dRa = OBB_A.v3dOBBLength.X() * fabs(rotBToA[1][1]) + OBB_A.v3dOBBLength.Y() * fabs(rotBToA[0][1]);
    dRb = OBB_B.v3dOBBLength.X() * fabs(rotBToA[2][2]) + OBB_B.v3dOBBLength.Z() * fabs(rotBToA[2][0]);
    if (dT > (dRa + dRb))
    {
        return false;
    }

    // u2_A X u2_B  9
    dT = fabs(v3dBToAPose.Y() * rotBToA[0][2] - v3dBToAPose.X() * rotBToA[1][2]);
    dRa = OBB_A.v3dOBBLength.X() * fabs(rotBToA[1][2]) + OBB_A.v3dOBBLength.Y() * fabs(rotBToA[0][2]);
    dRb = OBB_B.v3dOBBLength.X() * fabs(rotBToA[2][1]) + OBB_B.v3dOBBLength.Y() * fabs(rotBToA[2][0]);
    if (dT > (dRa + dRb))
    {
        return false;
    }
    return true;
}