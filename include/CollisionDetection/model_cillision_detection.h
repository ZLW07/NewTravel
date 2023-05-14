//
// Created by wei on 2023/5/10.
//

#ifndef NEWTRAVEL_MODEL_COLLISION_DETECTION_H
#define NEWTRAVEL_MODEL_COLLISION_DETECTION_H
#include <map>
#include <iostream>

#include "Model/model_data.h"

namespace zl
{
struct CollisionDetectionData
{
    PQP_Model m_oPQPModel;
    Eigen::Matrix4d m_transTransToBase;
};

class CollisionDetection
{
public:
    CollisionDetection();
    ~CollisionDetection(){}
    bool IsCollision(Eigen::Vector<double,6> &vecTheta);
private:
    void BuildCollisionDetectionPair();
    void InitCollisionDetectionData();
    void Matrix4dToRotation(Eigen::Matrix4d &oMat,double dResult[3][3]);
    void Matrix4dToTranslate(Eigen::Matrix4d &oMat, double *dResult);
private:
    std::map<std::string,std::vector<std::string>> m_mapCollisionDetectionPair;
    std::map<std::string,PQP_Model> m_mapPQPModel;
    std::map<std::string,int> m_mapLinkData;
    std::vector<PQP_Model> m_vecPQPModel;
};


}
#endif // NEWTRAVEL_MODEL_COLLISION_DETECTION_H
