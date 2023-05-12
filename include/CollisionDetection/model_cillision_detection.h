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
    CollisionDetection()
    {
        m_vecPQPModel.resize(7);
    }
    ~CollisionDetection(){}
    void BuildCollisionDetectionPair();
    void InitCollisionDetectionData();
    bool CheckCollision(std::vector<double> dTheta);
private:
    std::map<std::string,std::vector<std::string>> m_mapCollisionDetectionPair;
    std::map<std::string,PQP_Model> m_mapPQPModel;
    std::vector<PQP_Model> m_vecPQPModel;
};


}
#endif // NEWTRAVEL_MODEL_COLLISION_DETECTION_H
