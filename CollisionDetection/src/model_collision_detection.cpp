//
// Created by wei on 2023/5/10.
//

#include "CollisionDetection/model_cillision_detection.h"
#include "RobotModel/modern_robotics.h"
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
    for (int ii = 0; ii < 7; ++ii)
    {
        if (!ModelManager::BuildPQPModel(m_vecPQPModel.at(ii), "../../Data/RobotModel/" + std::to_string(ii + 1) + ".STL"))
        {
            return;
        }
    }

    m_mapPQPModel["Joint_1"] = m_vecPQPModel.at(0);
    m_mapPQPModel["Joint_2"] = m_vecPQPModel.at(1);
    m_mapPQPModel["Joint_3"] = m_vecPQPModel.at(2);
    m_mapPQPModel["Joint_4"] = m_vecPQPModel.at(3);
    m_mapPQPModel["Joint_5"] = m_vecPQPModel.at(4);
    m_mapPQPModel["Joint_6"] = m_vecPQPModel.at(5);
    m_mapPQPModel["Joint_7"] = m_vecPQPModel.at(6);


}
bool CollisionDetection::CheckCollision(std::vector<double> dTheta)
{
    std::vector<Eigen::Matrix4d> outJointTrans;
    Eigen::Matrix<double,6,6> oSlist;
    oSlist << 0, 0, 0, 0, 0, 0,
              0, 1, 1, 0, 1, 0,
              1, 0, 0, 1, 0, 1,
              0, 0, 0, 0, 0, 0,
             0, 0, 20,20,20,20,
            0,  0,400,850,850,850;
    Eigen::Vector<double,6> vecTheta;
    Eigen::Matrix4d InitTransform;
    InitTransform << 1, 0, 0, 0 ,
        0, 1, 0, 1 ,
        0, 0, 1,845,
        0, 0, 0,1;
    auto result = zl::Kinematics::FKinSpace(outJointTrans,InitTransform,oSlist,vecTheta);
    return false;
}
} // namespace zl