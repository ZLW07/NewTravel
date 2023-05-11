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
    CollisionDetection(){}
    ~CollisionDetection(){}
    void BuildCollisionDetectionPair();
    void InitCollisionDetectionData();
private:
    std::map<std::string,std::vector<std::string>> m_mapCollisionDetectionPair;
    std::map<std::string,CollisionDetectionData> m_mapPQPModel;
};


}
#endif // NEWTRAVEL_MODEL_COLLISION_DETECTION_H
