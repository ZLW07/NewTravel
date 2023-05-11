//
// Created by wei on 2023/5/10.
//

#include "model_cillision_detection.h"

namespace zl
{
void CollisionDetection::BuildCollisionDetectionPair()
{
    std::vector<std::string> vecCollisionJoint_1;
    vecCollisionJoint_1.push_back("Joint_5");
    vecCollisionJoint_1.push_back("Joint_6");
    vecCollisionJoint_1.push_back("Joint_7");
    m_mapCollisionDetectionPair.insert(
        std::pair<std::string, std::vector<std::string>>("Joint_1", vecCollisionJoint_1));

    std::vector<std::string> vecCollisionJoint_2;
    vecCollisionJoint_2.push_back("Joint_5");
    vecCollisionJoint_2.push_back("Joint_6");
    vecCollisionJoint_2.push_back("Joint_7");
    m_mapCollisionDetectionPair.insert(
        std::pair<std::string, std::vector<std::string>>("Joint_2", vecCollisionJoint_2));

    std::vector<std::string> vecCollisionJoint_5;
    vecCollisionJoint_5.push_back("Joint_1");
    vecCollisionJoint_5.push_back("Joint_2");
    m_mapCollisionDetectionPair.insert(
        std::pair<std::string, std::vector<std::string>>("Joint_5", vecCollisionJoint_5));

    std::vector<std::string> vecCollisionJoint_6;
    vecCollisionJoint_6.push_back("Joint_1");
    vecCollisionJoint_6.push_back("Joint_2");
    m_mapCollisionDetectionPair.insert(
        std::pair<std::string, std::vector<std::string>>("Joint_6", vecCollisionJoint_6));

    std::vector<std::string> vecCollisionJoint_7;
    vecCollisionJoint_7.push_back("Joint_1");
    vecCollisionJoint_7.push_back("Joint_2");
    m_mapCollisionDetectionPair.insert(
        std::pair<std::string, std::vector<std::string>>("Joint_7", vecCollisionJoint_7));
}

void CollisionDetection::InitCollisionDetectionData()
{
    CollisionDetectionData oCollisionDetectionJoint_1;
    if (!ModelManager::BuildPQPModel(oCollisionDetectionJoint_1.m_oPQPModel, "../../Data/RobotModel/1.STL"))
    {
        return ;
    }

    CollisionDetectionData oCollisionDetectionJoint_2;
    if (!ModelManager::BuildPQPModel(oCollisionDetectionJoint_1.m_oPQPModel, "../../Data/RobotModel/2.STL"))
    {
        return ;
    }

    CollisionDetectionData oCollisionDetectionJoint_3;
    if (!ModelManager::BuildPQPModel(oCollisionDetectionJoint_1.m_oPQPModel, "../../Data/RobotModel/3.STL"))
    {
        return ;
    }

    CollisionDetectionData oCollisionDetectionJoint_4;
    if (!ModelManager::BuildPQPModel(oCollisionDetectionJoint_1.m_oPQPModel, "../../Data/RobotModel/4.STL"))
    {
        return ;
    }

    CollisionDetectionData oCollisionDetectionJoint_5;
    if (!ModelManager::BuildPQPModel(oCollisionDetectionJoint_1.m_oPQPModel, "../../Data/RobotModel/5.STL"))
    {
        return ;
    }

    CollisionDetectionData oCollisionDetectionJoint_6;
    if (!ModelManager::BuildPQPModel(oCollisionDetectionJoint_1.m_oPQPModel, "../../Data/RobotModel/6.STL"))
    {
        return ;
    }

    CollisionDetectionData oCollisionDetectionJoint_7;
    if (!ModelManager::BuildPQPModel(oCollisionDetectionJoint_1.m_oPQPModel, "../../Data/RobotModel/7.STL"))
    {
        return ;
    }
    m_mapPQPModel["Joint_1"] = oCollisionDetectionJoint_1;
    m_mapPQPModel["Joint_2"] = oCollisionDetectionJoint_2;
    m_mapPQPModel["Joint_3"] = oCollisionDetectionJoint_3;
    m_mapPQPModel["Joint_4"] = oCollisionDetectionJoint_4;
    m_mapPQPModel["Joint_5"] = oCollisionDetectionJoint_5;
    m_mapPQPModel["Joint_6"] = oCollisionDetectionJoint_6;
    m_mapPQPModel["Joint_7"] = oCollisionDetectionJoint_7;
}
} // namespace zl