//
// Created by wei on 2023/6/5.
//

#ifndef NEWTRAVEL_TRAJECTORY_GENERATION_RRT_H
#define NEWTRAVEL_TRAJECTORY_GENERATION_RRT_H

#include "CollisionDetection/model_cillision_detection.h"

#include <random>
#include <memory>

namespace zl
{
class RobotJoints
{
public:
    double m_dAngle[6]{};
    ~RobotJoints() = default;
    friend std::ostream &operator<<(std::ostream &os, const RobotJoints &oRobotPose)
    {
        return os << " { " << oRobotPose.m_dAngle[0] << " " << oRobotPose.m_dAngle[1]
           << " " << oRobotPose.m_dAngle[2] << " " << oRobotPose.m_dAngle[3]
           << " " << oRobotPose.m_dAngle[4] << " " << oRobotPose.m_dAngle[5] << " }";

    }

    bool operator==(const RobotJoints &oRobotPose)
    {
        for (int ii = 0; ii < 6; ++ii)
        {
            if(std::fabs(m_dAngle[ii] - oRobotPose.m_dAngle[ii]) >0.0000001)
            {
                return false;
            }
        }
        return true;
    }

    Eigen::Vector<double, 6> ToEigenVector()
    {
        Eigen::Vector<double, 6> oVec;
        for (int ii = 0; ii < 6; ++ii)
        {
            oVec[ii] = m_dAngle[ii];
        }
        return oVec;
    }

    RobotJoints()
    {
        for (double & ii : m_dAngle)
        {
            ii = 0.0;
        }
    }
};

class RRTNode
{
public:
    RobotJoints m_oCurrentPose;
    std::shared_ptr<RRTNode> m_pParentNode;
    std::vector<std::shared_ptr<RRTNode> > m_vecChildrenNode;
    double m_dDistanceToRootNode;
    RRTNode() = default;
    ~RRTNode() = default;
    // 判断两个姿态是否相等
    bool IsEqual(const RobotJoints &other) const;
};

class RRTPlanner
{
public:
    RRTPlanner(const RobotJoints &oStartPose, const RobotJoints &oTargetPose, double dStepSize, int iMaxIterations);
    ~RRTPlanner();

    bool Plan(std::vector<Eigen::Vector<double, 6>> &vecPath);
    std::vector<RobotJoints> GetAllGenerateJoints()
    {
        return m_vecAllPoints;
    }
public:
    static double GetDistance(const RobotJoints &a, const RobotJoints &b);
private:
    RobotJoints GetRandomNode(const RobotJoints &oReferencePose);
    std::shared_ptr<RRTNode>  GetNearestNode(const RobotJoints &pPose);
    void Rewire(std::shared_ptr<RRTNode> pNode);

    void Clear();
    void ClearNode(std::shared_ptr<RRTNode> oNode);
    double RandAngle(int i, double dJointValue);
    bool IsReachAble(const RobotJoints &a, const RobotJoints &b);
    void GetNearestChileNode(std::shared_ptr<RRTNode> &pRRTNode,const RobotJoints &oPose, double &dDistance,std::shared_ptr<RRTNode> &outRRTNode);
    void RewireChildrenNode(std::vector<std::shared_ptr<RRTNode> > &vecRRTNode, std::shared_ptr<RRTNode> pNode);
    void GePath(std::shared_ptr<RRTNode> pRRTNode, std::vector<Eigen::Vector<double, 6>> &vecPath);
    void SmoothPath(std::vector<Eigen::Vector<double, 6>> &vecPath);
    void AddGenerateJoints(RobotJoints oRobotJoints)
    {
        if(m_vecAllPoints.end() == std::find(m_vecAllPoints.begin(),m_vecAllPoints.end(),oRobotJoints))
        {
            m_vecAllPoints.push_back(oRobotJoints);
        }
    }

private:
    std::shared_ptr<RRTNode> m_pRootNode;
    RobotJoints m_oStartPose;
    RobotJoints m_oTargetPose;
    int m_iMaxIterations;
    CollisionDetection m_oCollisionDetection;
    std::vector<RobotJoints> m_vecAllPoints;
};
} // namespace zl
#endif // NEWTRAVEL_TRAJECTORY_GENERATION_RRT_H
