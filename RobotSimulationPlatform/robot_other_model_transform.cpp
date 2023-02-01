//
// Created by wei on 2023/1/31.
//

#include "robot_other_model_transform.h"
#include "Log/log.h"
OtherModelTrans::OtherModelTrans(QWidget *parent) : QTextEdit(parent) {}

void OtherModelTrans::SetValue()
{
    emitValue();
}

void OtherModelTrans::emitValue()
{
    QString sValue = toPlainText();
    ZLOG << sValue.toStdString();
    std::string sTransValue = sValue.toStdString();
    QMatrix4x4 mat4Trans;
    mat4Trans.setToIdentity();
    QVector<std::string> vecRPY;
    std::string sRPY = sTransValue.substr(sTransValue.find('{'),std::string::npos);
    int iRPYIndex = sRPY.find('{');
    while (std::string::npos != iRPYIndex)
    {
        std::string sRPYValue = sRPY.substr(iRPYIndex + 1,sRPY.find_first_of('}') - iRPYIndex - 1);
        vecRPY.push_back(sRPYValue);
        sRPY = sRPY.substr(sRPY.find_first_of('}') + 1 ,std::string::npos);
        iRPYIndex = sRPY.find('{');
    }
    QVector4D vecRot;
    for (int i = 0; i < vecRPY.size(); ++i)
    {
        size_t iRPYIndex = vecRPY[i].find(',');
        int iIndex = 0;
        while (std::string::npos != iRPYIndex)
        {
            std::string sPPYValue = vecRPY[i].substr(0,iRPYIndex);
            vecRot[iIndex] = (strtod(sPPYValue.c_str(), nullptr));
            vecRPY[i] = vecRPY[i].substr(iRPYIndex + 1,std::string::npos);
            iRPYIndex = vecRPY[i].find(',');
            iIndex ++ ;
        }
        vecRot[iIndex] =  (strtod(vecRPY[i].c_str(), nullptr));
        mat4Trans.setColumn(i,vecRot);
    }
    QVector4D vecPose;
    if(std::string::npos != sTransValue.find("Vector3D("))
    {
        int iInd = 0;
        int iIndex = sTransValue.find("Vector3D(") + 9;
        std::string sPos = sTransValue.substr(iIndex,sTransValue.find_first_of(')') - iIndex);
        size_t iCount = sPos.find(',');
        while (std::string::npos != iCount)
        {
            std::string sPoseValue = sPos.substr(0,iCount);
            vecPose[iInd] = (strtod(sPoseValue.c_str(), nullptr));
            sPos = sPos.substr(iCount + 1,std::string::npos);
            iCount = sPos.find(',');
            iInd++;
        }
        vecPose[iInd] = (strtod(sPos.c_str(), nullptr));
        vecPose[3] = 1;
    }
    mat4Trans.setColumn(3,vecPose);
    emit SetValue(mat4Trans);
}

OtherModelTrans::~OtherModelTrans() {}
