//
// Created by wei on 2023/6/5.
//

#ifndef NEWTRAVEL_TRAJECTORY_GENERATION_RRT_H
#define NEWTRAVEL_TRAJECTORY_GENERATION_RRT_H

#include "CollisionDetection/model_cillision_detection.h"
#include <random>

namespace zl
{
class RobotPose
{
public:
    double dAngle[6];
    RobotPose() = default;
    ~RobotPose() = default;
    friend std::ostream &operator<<(std::ostream &os, const RobotPose &oRobotPose)
    {
        return os << " { " << oRobotPose.dAngle[0] << " " << oRobotPose.dAngle[1]
           << " " << oRobotPose.dAngle[2] << " " << oRobotPose.dAngle[3]
           << " " << oRobotPose.dAngle[4] << " " << oRobotPose.dAngle[5] << " }";

    }
    Eigen::Vector<double, 6> ToEigenVector()
    {
        Eigen::Vector<double, 6> oVec;
        for (int ii = 0; ii < 6; ++ii)
        {
            oVec[ii] = dAngle[ii];
        }
        return oVec;
    }
};

class RRTNode
{
public:
    RobotPose m_oCurrentPose;
    RRTNode *m_pParentNode;
    std::vector<RRTNode *> m_vecChildrenNode;
    double m_dDistanceToRootNode;
    RRTNode() = default;
    ~RRTNode() = default;
    // 判断两个姿态是否相等
    bool isEqual(const RobotPose &other) const;
    RRTNode *operator=(const RobotPose &oRobotPose)
    {
        RRTNode *pRRTNode = new RRTNode();
        pRRTNode->m_pParentNode = m_pParentNode;
        pRRTNode->m_oCurrentPose = m_oCurrentPose;
        pRRTNode->m_dDistanceToRootNode = m_dDistanceToRootNode;
        for (int ii = 0; ii < m_vecChildrenNode.size(); ++ii)
        {
            pRRTNode->m_vecChildrenNode.push_back(m_vecChildrenNode.at(ii));
        }
        return pRRTNode;
    }
};

class RRTPlanner
{
public:
    RRTPlanner(const RobotPose &oStartPose, const RobotPose &oTargetPose, double dStepSize, int iMaxIterations);
    ~RRTPlanner();

    bool Plan(std::vector<Eigen::Vector<double, 6>> &vecPath);

//private:
    RobotPose GetRandomNode(const RobotPose &oReferencePose);
    bool IsValid(const RobotPose &a, const RobotPose &b);
    RRTNode *GetNearestNode(const RobotPose &pPose);
    RobotPose NewConfig(const RRTNode &oA, const RobotPose &oB, const double &dStepSize);
    bool Extend(RRTNode *pNode);
    void Rewire(RRTNode *pNode);
    double GetDistance(const RobotPose &a, const RobotPose &b);
    void Clear();
    void ClearNode(RRTNode *oNode);
    double RandAngle(int i, double dJointValue);

    double GetGoalDistanceCost(const RobotPose &oRobotPose);
    bool IsReachAble(const RobotPose &a, const RobotPose &b);
    void GetNearestChileNode(RRTNode *pRRTNode,const RobotPose &oPose, double &dDistance,RRTNode *outRRTNode);
    void RewireChildrenNode(std::vector<RRTNode *> &vecRRTNode, RRTNode *pNode);
    void GePath(RRTNode *pRRTNode, std::vector<Eigen::Vector<double, 6>> &vecPath);
    void SmoothPath(std::vector<Eigen::Vector<double, 6>> &vecPath);
private:
    RRTNode *m_pRootNode;
    RobotPose m_oStartPose;
    RobotPose m_oTargetPose;
    double m_dStepSize;
    int m_iMaxIterations;
    CollisionDetection m_oCollisionDetection;
};
} // namespace zl
#endif // NEWTRAVEL_TRAJECTORY_GENERATION_RRT_H
