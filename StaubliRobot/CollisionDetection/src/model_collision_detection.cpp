//
// Created by wei on 2023/5/10.
//

#include "CollisionDetection/model_cillision_detection.h"
#include "Kinematics/modern_robotics.h"
namespace zl
{
CollisionDetection::CollisionDetection()
{
    m_vecPQPModel.resize(7);
    m_pStuabilKine = std::make_shared<StuRobotKinematics>();
    BuildCollisionDetectionPair();
    InitCollisionDetectionData();
}

void CollisionDetection::BuildCollisionDetectionPair()
{
    std::vector<std::string> vecCollisionLink_1;
    vecCollisionLink_1.emplace_back("Link_5");
    vecCollisionLink_1.emplace_back("Link_6");
    vecCollisionLink_1.emplace_back("Link_7");
    m_mapCollisionDetectionPair.insert(std::pair<std::string, std::vector<std::string>>("Link_1", vecCollisionLink_1));

    std::vector<std::string> vecCollisionLink_2;
    vecCollisionLink_2.emplace_back("Link_5");
    vecCollisionLink_2.emplace_back("Link_6");
    vecCollisionLink_2.emplace_back("Link_7");
    m_mapCollisionDetectionPair.insert(std::pair<std::string, std::vector<std::string>>("Link_2", vecCollisionLink_2));

    std::vector<std::string> vecCollisionLink_5;
    vecCollisionLink_5.emplace_back("Link_1");
    vecCollisionLink_5.emplace_back("Link_2");
    m_mapCollisionDetectionPair.insert(std::pair<std::string, std::vector<std::string>>("Link_5", vecCollisionLink_5));

    std::vector<std::string> vecCollisionLink_6;
    vecCollisionLink_6.emplace_back("Link_1");
    vecCollisionLink_6.emplace_back("Link_2");
    m_mapCollisionDetectionPair.insert(std::pair<std::string, std::vector<std::string>>("Link_6", vecCollisionLink_6));

    std::vector<std::string> vecCollisionLink_7;
    vecCollisionLink_7.emplace_back("Link_1");
    vecCollisionLink_7.emplace_back("Link_2");
    m_mapCollisionDetectionPair.insert(std::pair<std::string, std::vector<std::string>>("Link_7", vecCollisionLink_7));
    Eigen::Matrix4d matLink1;
    matLink1 <<
        1,0,0,0,
        0,0,1,0,
        0,-1,0,-0.375,
        0,0,0,1;

    m_mInitTrans["Link_1"] = matLink1;
    Eigen::Matrix4d matLink2;
    matLink2 <<
             1,0,0,0,
        0,0,1,0,
        0,-1,0,0,
        0,0,0,1;
    m_mInitTrans["Link_2"] = matLink2;
    Eigen::Matrix4d matLink3;
    matLink3 << 1,0,0,0,
        0,0,1,0,
        0,-1,0,0,
        0,0,0,1;
    m_mInitTrans["Link_3"] = matLink3;
    Eigen::Matrix4d matLink4;
    matLink4 << 1,0,0,0,
        0,0,1,0.020,
        0,-1,0,0.4,
        0,0,0,1;
    m_mInitTrans["Link_4"] = matLink4;

    Eigen::Matrix4d matLink5;
    matLink5 << 1,0,0,0,
        0,1,0,0.020,
        0,0,1,0.4,
        0,0,0,1;
    m_mInitTrans["Link_5"] = matLink5;

    Eigen::Matrix4d matLink6;
    matLink6 << 1,0,0,0,
        0,0,-1,0.020,
        0,1,0,0.85,
        0,0,0,1;
    m_mInitTrans["Link_6"] = matLink6;

    Eigen::Matrix4d matLink7;
    matLink7 << 1, 0, 0, 0,
        0, 1, 0, 0.020,
        0, 0, 1, 0.92,
        0, 0, 0, 1;
    m_mInitTrans["Link_7"] = matLink7;
}

void CollisionDetection::InitCollisionDetectionData()
{
    for (int ii = 0; ii < 7; ++ii)
    {
        m_vecPQPModel.at(ii) = new PQP_Model();
        if (!ModelManager::BuildPQPModel(
                m_vecPQPModel.at(ii), "../../StaubliRobot/Data/RobotModel/" + std::to_string(ii + 1) + ".STL"))
        {
            ZLOG_ERR << "Failed to load robot model";
            return;
        }
    }
    m_mapPQPModel["Link_1"] = new PQP_Model();
    m_mapPQPModel["Link_1"] = m_vecPQPModel.at(0);

    m_mapPQPModel["Link_2"] = new PQP_Model();
    m_mapPQPModel["Link_2"] = m_vecPQPModel.at(1);

    m_mapPQPModel["Link_3"] = new PQP_Model();;
    m_mapPQPModel["Link_3"] = m_vecPQPModel.at(2);

    m_mapPQPModel["Link_4"] = new PQP_Model();
    m_mapPQPModel["Link_4"] = m_vecPQPModel.at(3);

    m_mapPQPModel["Link_5"] = new PQP_Model();
    m_mapPQPModel["Link_5"] = m_vecPQPModel.at(4);

    m_mapPQPModel["Link_6"] = new PQP_Model();
    m_mapPQPModel["Link_6"] = m_vecPQPModel.at(5);

    m_mapPQPModel["Link_7"] = new PQP_Model();
    m_mapPQPModel["Link_7"] = m_vecPQPModel.at(6);

    m_mapLinkData["Link_1"] = 0;
    m_mapLinkData["Link_2"] = 1;
    m_mapLinkData["Link_3"] = 2;
    m_mapLinkData["Link_4"] = 3;
    m_mapLinkData["Link_5"] = 4;
    m_mapLinkData["Link_6"] = 5;
    m_mapLinkData["Link_7"] = 6;
}

bool CollisionDetection::IsCollision(Eigen::Vector<double, 6> &vecTheta)
{
    std::vector<Eigen::Matrix4d> outJointTrans;
    auto result = m_pStuabilKine->ForwardKinematics(vecTheta,outJointTrans);
    for (const auto &iter : m_mapCollisionDetectionPair)
    {
        std::string sLinkName = iter.first;
        auto oTrans = outJointTrans.at(m_mapLinkData[sLinkName]);
        oTrans = oTrans * m_mInitTrans[sLinkName];
        double R1[3][3];
        Matrix4dToRotation(oTrans, R1);
        double dT1[3];
        Matrix4dToTranslate(oTrans, dT1);
        for (auto sOtherLinkName : iter.second)
        {
            auto oTrans2 = outJointTrans.at(m_mapLinkData[sOtherLinkName]);
            oTrans2 = oTrans2*m_mInitTrans[sOtherLinkName];
            double R2[3][3];
            Matrix4dToRotation(oTrans2, R2);
            double T2[3];
            Matrix4dToTranslate(oTrans2, T2);
            PQP_CollideResult cres;
            PQP_Collide(
                &cres, R1, dT1, m_mapPQPModel[sLinkName], R2, T2, m_mapPQPModel[sOtherLinkName], PQP_FIRST_CONTACT);
            if (cres.Colliding())
            {
//                ZLOG_ERR << "The pose is collision" <<sLinkName << " and " << sOtherLinkName ;
//                ZLOG_ERR << "The pose is " << vecTheta;
                return true;
            }
        }
    }
    return false;
}

void CollisionDetection::Matrix4dToTranslate(Eigen::Matrix4d &oMat, double *dResult)
{
    for (int ii = 0; ii < 3; ++ii)
    {
        dResult[ii] = oMat(ii, 3);
    }
}

void CollisionDetection::Matrix4dToRotation(Eigen::Matrix4d &oMat, double dResult[3][3])
{
    for (int ii = 0; ii < 3; ++ii)
    {
        for (int jj = 0; jj < 3; ++jj)
        {
            dResult[ii][jj] = oMat(ii, jj);
        }
    }
}

} // namespace zl