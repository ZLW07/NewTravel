//
// Created by wei on 2023/5/10.
//

#include "CollisionDetection/model_cillision_detection.h"
#include "Kinematics//modern_robotics.h"
namespace zl
{

CollisionDetection::CollisionDetection()
{
    m_vecPQPModel.resize(7);
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
}

void CollisionDetection::InitCollisionDetectionData()
{
    for (int ii = 0; ii < 7; ++ii)
    {
        if (!ModelManager::BuildPQPModel(m_vecPQPModel.at(ii),
                "../../Data/RobotModel/" + std::to_string(ii + 1) + ".STL"))
        {
            return;
        }
    }
    m_mapPQPModel["Link_1"] = m_vecPQPModel.at(0);
    m_mapPQPModel["Link_2"] = m_vecPQPModel.at(1);
    m_mapPQPModel["Link_3"] = m_vecPQPModel.at(2);
    m_mapPQPModel["Link_4"] = m_vecPQPModel.at(3);
    m_mapPQPModel["Link_5"] = m_vecPQPModel.at(4);
    m_mapPQPModel["Link_6"] = m_vecPQPModel.at(5);
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
    Eigen::Matrix<double, 6, 6> oSlist;
    oSlist << 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, -375, -775, 20, -1225, 20, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0;
    //    Eigen::Vector<double,6> vecTheta;
    Eigen::Matrix4d InitTransform;
    InitTransform << 1, 0, 0, 0, 0, 1, 0, 20, 0, 0, 1, 1295, 0, 0, 0, 1;
    auto result = zl::Kinematics::FKinSpace(outJointTrans, InitTransform, oSlist, vecTheta);

    for (const auto &iter : m_mapCollisionDetectionPair)
    {
        std::string sLinkName = iter.first;
        auto oTrans = outJointTrans.at(m_mapLinkData[sLinkName]);
        double R1[3][3];
        Matrix4dToRotation(oTrans,R1);
        double dT1[3];
        Matrix4dToTranslate(oTrans,dT1);
        for (auto sOtherLinkName : iter.second)
        {

            auto oTrans2 = outJointTrans.at(m_mapLinkData[sOtherLinkName]);
            double R2[3][3];
            Matrix4dToRotation(oTrans2,R2);
            double T2[3];
            Matrix4dToTranslate(oTrans2,T2);

            PQP_CollideResult cres;
            PQP_Collide(&cres, R1, dT1, &m_mapPQPModel[sLinkName], R2, T2, &m_mapPQPModel[sOtherLinkName], PQP_ALL_CONTACTS);
            if (cres.Colliding())
            {
                ZLOG_ERR << "The pose is collision";
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
        dResult[ii] = oMat(3, ii);
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