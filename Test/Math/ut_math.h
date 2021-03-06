//
// Created by wei on 2022/4/19.
//

#ifndef NEWTRAVEL_UT_MATH_H
#define NEWTRAVEL_UT_MATH_H

#include "Log/log.h"
#include "Math/math_linear_algebra.h"
#include "Math/math_matrix.h"
#include "Math/math_matrix4d.h"
#include "Math/math_rotation.h"
#include "Math/math_vector3d.h"
#include <iostream>
#include "Eigen/Eigen"
#include "Math/math_rotation_eigen.h"

#include "gtest/gtest.h"

class TestMath : public ::testing::Test
{
public:
    TestMath() = default;
    ~TestMath() {}

private:
};

TEST_F(TestMath, TestVector3DOperate)
{
    Matrix4D oTran;
    Vector3D v3dData1(1, 0, 0);
    Vector3D v3dData2(0, 1, 0);
    Vector3D v3dData3(0, 0, 1);
    EXPECT_EQ(0, v3dData1.Dot(v3dData2));
    EXPECT_EQ(1, v3dData1.Cross(v3dData2)[2]);
    EXPECT_FLOAT_EQ(90, v3dData1.GetVectorAngleDeg(v3dData2));
}

TEST_F(TestMath, TestTransForm)
{
    Vector3D v3dData1(2, -1, 0);
    Vector3D v3dData2(-1, 2, -1);
    Vector3D v3dData3(0, -1, 2);
    Vector3D v3dData4(1, 3, 1);
    Vector3D v3dData5(1, 0, 8);
    Rotation rotData(v3dData1, v3dData2, v3dData3);
    Matrix4D oTrans(rotData, v3dData5);
    ZLOG << oTrans;
    Vector3D v3dResult = oTrans * v3dData4;
    ZLOG << v3dResult;

    Matrix oMat(2,2);
    oMat[0][1] = 1.0;
    oMat[1][1] = 1.0;
    ZLOG << rotData;
    rotData.CombinationTransformMatrix(oMat);
    ZLOG << rotData;
    ZLOG << rotData.Transpose();

    Rotation rotRation;
    rotRation.SetEye();
    Vector3D v3dPose(1, 0, 0);
    Matrix4D transMat{rotRation,v3dPose};
    v3dPose[0] = 5;
    Matrix4D transMat1{rotRation,v3dPose};
    ZLOG  << transMat*transMat1;
}

TEST_F(TestMath, TestInv)
{
    Vector3D v3dData1(2, -1, 0);
    Vector3D v3dData2(-1, 2, -1);
    Vector3D v3dData3(0, -1, 2);
    Vector3D v3dData4(1, 3, 1);
    Vector3D v3dData5(1, 0, 8);
    Rotation rotData(v3dData1, v3dData2, v3dData3);
    Matrix4D oTrans(rotData, v3dData5);
    Matrix4D oInv;
    oInv.Inv(oTrans);
    // {0.75 0.5 0.25 -2.75} {0.5 1 0.5 -4.5} {0.25 0.5 0.75 -6.25} {0 0 0 1}
    ZLOG << oInv;
}

TEST_F(TestMath, TestVector)
{
    std::vector<Vector3D> vecSrc;
    Vector3D v3d(3.7,1.7,3.5);
    vecSrc.push_back(v3d);
    v3d.Clear();
    v3d = {4.1,3.8,5.2};
    vecSrc.push_back(v3d);
    v3d.Clear();
    v3d = { 4.7,2.9,2.1};
    vecSrc.push_back(v3d);
    v3d.Clear();
    v3d = {  5.2,2.8,6.0};
    vecSrc.push_back(v3d);
    v3d.Clear();
    auto aResult = v3d.GetCoordinateExtremum(vecSrc);
    ZLOG << aResult.first;    //  3.7 1.7 2.1
    ZLOG << aResult.second;   //  5.2 3.8 6
}

TEST_F(TestMath, TestOBB)
{
    std::vector<Vector3D> vecSrc;
    Vector3D v3d(3.7,1.7,3.5);
    vecSrc.push_back(v3d);
    v3d.Clear();
    v3d = {4.1,3.8,5.2};
    vecSrc.push_back(v3d);
    v3d.Clear();
    v3d = { 4.7,2.9,2.1};
    vecSrc.push_back(v3d);
    v3d.Clear();
    v3d = {  5.2,2.8,6.0};
    vecSrc.push_back(v3d);
    v3d.Clear();
    Rotation rot;
    rot.Cov(vecSrc);
//    {0.435833 0.166667 0.333333} {0.166667 0.74 0.52} {0.333333 0.52 3.04667}
    ZLOG << rot;
    auto result = rot.GetOBBDirectionVector(rot);
//    {-0.760026 -0.290641 -0.581282} {0.491677 -0.842044 -0.221846} {0.424987 0.454412 -0.782877}
    ZLOG << result;
}

TEST_F(TestMath, TestOBB_E)
{
    std::vector<Eigen::Vector3d> vecSrc;
    Eigen::Vector3d v3d(3.7,1.7,3.5);
    vecSrc.push_back(v3d);
    v3d = {4.1,3.8,5.2};
    vecSrc.push_back(v3d);
    v3d = { 4.7,2.9,2.1};
    vecSrc.push_back(v3d);
    v3d = {  5.2,2.8,6.0};
    vecSrc.push_back(v3d);
    RotationE rot;
    rot.CovarianceMatrix(vecSrc);
//    {0.435833 0.166667 0.333333} {0.166667 0.74 0.52} {0.333333 0.52 3.04667}
    ZLOG << rot;
    auto result = rot.GetOBBDirectionVector(rot);
//    {-0.760026 -0.290641 -0.581282} {0.491677 -0.842044 -0.221846} {0.424987 0.454412 -0.782877}
    ZLOG << result;
}

bool JacbiCor(double * pMatrix,int nDim, double *pdblVects, double *pdbEigenValues, double dbEps,int nJt)
{
    for(int i = 0; i < nDim; i ++)
    {
        pdblVects[i*nDim+i] = 1.0f;
        for(int j = 0; j < nDim; j ++)
        {
            if(i != j)
                pdblVects[i*nDim+j]=0.0f;
        }
    }

    int nCount = 0;     //????????????
    while(1)
    {
        //???pMatrix????????????????????????????????????
        double dbMax = pMatrix[1];
        int nRow = 0;
        int nCol = 1;
        for (int i = 0; i < nDim; i ++)          //???
        {
            for (int j = 0; j < nDim; j ++)      //???
            {
                double d = fabs(pMatrix[i*nDim+j]);

                if((i!=j) && (d> dbMax))
                {
                    dbMax = d;
                    nRow = i;
                    nCol = j;
                }
            }
        }

        if(dbMax < dbEps)     //??????????????????
            break;

        if(nCount > nJt)       //????????????????????????
            break;

        nCount++;

        double dbApp = pMatrix[nRow*nDim+nRow];
        double dbApq = pMatrix[nRow*nDim+nCol];
        double dbAqq = pMatrix[nCol*nDim+nCol];

        //??????????????????
        double dbAngle = 0.5*atan2(-2*dbApq,dbAqq-dbApp);
        double dbSinTheta = sin(dbAngle);
        double dbCosTheta = cos(dbAngle);
        double dbSin2Theta = sin(2*dbAngle);
        double dbCos2Theta = cos(2*dbAngle);

        pMatrix[nRow*nDim+nRow] = dbApp*dbCosTheta*dbCosTheta +
                                  dbAqq*dbSinTheta*dbSinTheta + 2*dbApq*dbCosTheta*dbSinTheta;
        pMatrix[nCol*nDim+nCol] = dbApp*dbSinTheta*dbSinTheta +
                                  dbAqq*dbCosTheta*dbCosTheta - 2*dbApq*dbCosTheta*dbSinTheta;
        pMatrix[nRow*nDim+nCol] = 0.5*(dbAqq-dbApp)*dbSin2Theta + dbApq*dbCos2Theta;
        pMatrix[nCol*nDim+nRow] = pMatrix[nRow*nDim+nCol];

        for(int i = 0; i < nDim; i ++)
        {
            if((i!=nCol) && (i!=nRow))
            {
                int u = i*nDim + nRow;  //p
                int w = i*nDim + nCol;  //q
                dbMax = pMatrix[u];
                pMatrix[u]= pMatrix[w]*dbSinTheta + dbMax*dbCosTheta;
                pMatrix[w]= pMatrix[w]*dbCosTheta - dbMax*dbSinTheta;
            }
        }

        for (int j = 0; j < nDim; j ++)
        {
            if((j!=nCol) && (j!=nRow))
            {
                int u = nRow*nDim + j;  //p
                int w = nCol*nDim + j;  //q
                dbMax = pMatrix[u];
                pMatrix[u]= pMatrix[w]*dbSinTheta + dbMax*dbCosTheta;
                pMatrix[w]= pMatrix[w]*dbCosTheta - dbMax*dbSinTheta;
            }
        }

        //??????????????????
        for(int i = 0; i < nDim; i ++)
        {
            int u = i*nDim + nRow;      //p
            int w = i*nDim + nCol;      //q
            dbMax = pdblVects[u];
            pdblVects[u] = pdblVects[w]*dbSinTheta + dbMax*dbCosTheta;
            pdblVects[w] = pdblVects[w]*dbCosTheta - dbMax*dbSinTheta;
        }

    }

    //??????????????????????????????????????????????????????,????????????pMatrix????????????????????????
    std::map<double,int> mapEigen;
    for(int i = 0; i < nDim; i ++)
    {
        pdbEigenValues[i] = pMatrix[i*nDim+i];

        mapEigen.insert(std::make_pair( pdbEigenValues[i],i ) );
    }

    double *pdbTmpVec = new double[nDim*nDim];
    std::map<double,int>::reverse_iterator iter = mapEigen.rbegin();
    for (int j = 0; iter != mapEigen.rend(),j < nDim; ++iter,++j)
    {
        for (int i = 0; i < nDim; i ++)
        {
            pdbTmpVec[i*nDim+j] = pdblVects[i*nDim + iter->second];
        }

        //?????????????????????
        pdbEigenValues[j] = iter->first;
    }

    //???????????????
    for(int i = 0; i < nDim; i ++)
    {
        double dSumVec = 0;
        for(int j = 0; j < nDim; j ++)
            dSumVec += pdbTmpVec[j * nDim + i];
        if(dSumVec<0)
        {
            for(int j = 0;j < nDim; j ++)
                pdbTmpVec[j * nDim + i] *= -1;
        }
    }

    memcpy(pdblVects,pdbTmpVec,sizeof(double)*nDim*nDim);
    delete []pdbTmpVec;

    return 1;
}
#endif // NEWTRAVEL_UT_MATH_H
