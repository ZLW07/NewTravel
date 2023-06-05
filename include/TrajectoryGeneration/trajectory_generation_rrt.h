//
// Created by wei on 2023/6/5.
//

#ifndef NEWTRAVEL_TRAJECTORY_GENERATION_RRT_H
#define NEWTRAVEL_TRAJECTORY_GENERATION_RRT_H

#include "CollisionDetection/model_cillision_detection.h"

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
        return os << "Joint_0: " << oRobotPose.dAngle[0] << " Joint_1: " << oRobotPose.dAngle[1]
           << " Joint_2: " << oRobotPose.dAngle[2] << " Joint_3: " << oRobotPose.dAngle[3]
           << " Joint_4: " << oRobotPose.dAngle[4] << " Joint_5: " << oRobotPose.dAngle[5];

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
    bool isEqual(const RobotPose &other) const
    {
        for (int i = 0; i < 6; ++i)
        {
            if (fabs(m_oCurrentPose.dAngle[i] - other.dAngle[i]) > 1)
            {
                return false;
            }
        }
        return true;
    }
};

class RRTPlanner
{
public:
    RRTPlanner(const RobotPose &oStartPose, const RobotPose &oTargetPose, double dStepSize, int iMaxIterations);
    ~RRTPlanner();

    bool Plan();

private:
    RobotPose GetRandomNode();
    bool IsValid(const RobotPose &oPose);
    RRTNode *GetNearestNode(const RobotPose &pPose);
    RobotPose NewConfig(const RRTNode &oA, const RobotPose &oB, const double &dStepSize);
    bool Extend(RRTNode *pNode);
    void Rewire(RRTNode *pNode);
    double GetDistance(const RobotPose &a, const RobotPose &b);
    void Clear();
    void ClearNode(RRTNode *oNode);
    double RandAngle(int i);

protected:
    RRTNode *m_pRootNode;
    RobotPose m_oStartPose;
    RobotPose m_oTargetPose;
    double m_dStepSize;
    int m_iMaxIterations;
};
} // namespace zl
#endif // NEWTRAVEL_TRAJECTORY_GENERATION_RRT_H
