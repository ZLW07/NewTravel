//
// Created by wei on 2023/6/5.
//

#include "TrajectoryGeneration/trajectory_generation_rrt.h"

namespace zl
{
bool RRTNode::IsEqual(const RobotJoints &other) const
{
    {
        for (int i = 0; i < 6; ++i)
        {
            if (fabs(m_oCurrentPose.m_dAngle[i] - other.m_dAngle[i]) > 0.1)
            {
                return false;
            }
        }
        return true;
    }
}

RRTPlanner::RRTPlanner(const RobotJoints &oStartPose, const RobotJoints &oTargetPose, double dStepSize,
    int iMaxIterations)
    : m_oStartPose(oStartPose), m_oTargetPose(oTargetPose), m_iMaxIterations(iMaxIterations),
      m_oCollisionDetection(CollisionDetection())
{
    m_pRootNode = std::make_shared<RRTNode>();
    m_pRootNode->m_oCurrentPose = oStartPose;
    m_pRootNode->m_pParentNode = nullptr;
    m_pRootNode->m_dDistanceToRootNode = 0;
    m_vecAllPoints.clear();
}

RRTPlanner::~RRTPlanner()
{
    Clear();
}

std::shared_ptr<RRTNode> RRTPlanner::GetNearestNode(const RobotJoints &pPose)
{\
    std::shared_ptr<RRTNode> pRRTNode(new RRTNode());
    if (m_pRootNode->m_vecChildrenNode.empty())
    {
        pRRTNode = m_pRootNode;
        return pRRTNode;
    }

    double cur_distance = std::numeric_limits<double>::infinity();
    double min_distance = GetDistance(m_pRootNode->m_oCurrentPose, pPose);
    if (cur_distance > min_distance)
    {
        cur_distance = min_distance;
        pRRTNode = m_pRootNode;
    }

    for (int i = 0; i < m_pRootNode->m_vecChildrenNode.size(); ++i)
    {
        GetNearestChileNode(m_pRootNode, pPose, cur_distance, pRRTNode);
    }
    return pRRTNode;
}

RobotJoints RRTPlanner::GetRandomNode(const RobotJoints &oReferencePose)
{
    RobotJoints pose{};
    bool bStatus = true;
    while (bStatus)
    {
        for (int i = 0; i < 6; ++i)
        {
            pose.m_dAngle[i] = RandAngle(i, oReferencePose.m_dAngle[i]);
        }
        for (int ii = 0; ii < 6; ++ii)
        {
            if (pose.m_dAngle[ii] < m_oTargetPose.m_dAngle[ii] && pose.m_dAngle[ii] > m_oStartPose.m_dAngle[ii])
            {
                bStatus = false;
            }
        }
    }
    return pose;
}

double RRTPlanner::RandAngle(int i, double dJointValue)
{
    std::random_device oRdNumber;
    std::mt19937 oGenerate(oRdNumber());
    std::uniform_real_distribution<> oDis(0, 1);
    double dRandNum = oDis(oGenerate);
    double dAngel = 0.0;
    if (dRandNum < 0.3)
    {
        dAngel = m_oStartPose.m_dAngle[i] + dRandNum * (m_oTargetPose.m_dAngle[i] - m_oStartPose.m_dAngle[i]);
    }
    else
    {
        dAngel = dJointValue + dRandNum * (m_oTargetPose.m_dAngle[i] - dJointValue);
    }
    return dAngel;
}

void RRTPlanner::ClearNode(std::shared_ptr<RRTNode> oNode)
{
    for (const std::shared_ptr<RRTNode> &child : oNode->m_vecChildrenNode)
    {
        ClearNode(child);
    }
}

void RRTPlanner::Clear()
{
    ClearNode(m_pRootNode);
}

double RRTPlanner::GetDistance(const RobotJoints &a, const RobotJoints &b)
{
    double dist = 0.0;
    for (int i = 0; i < 6; ++i)
    {
        dist += std::pow(a.m_dAngle[i] - b.m_dAngle[i], 2);
    }
    return std::sqrt(dist);
}

void RRTPlanner::RewireChildrenNode(std::vector<std::shared_ptr<RRTNode>> &vecRRTNode, std::shared_ptr<RRTNode> pNode)
{
    for (auto &ii : vecRRTNode)
    {
        if (ii->IsEqual(pNode->m_oCurrentPose))
        {
            return;
        }
        double dDistance = GetDistance(ii->m_oCurrentPose, pNode->m_oCurrentPose);
        if (dDistance < pNode->m_dDistanceToRootNode)
        {
            if (IsReachAble(ii->m_oCurrentPose, pNode->m_oCurrentPose))
            {
                if (pNode->m_pParentNode != nullptr)
                {
//                    ZLOG_INFO << "Current parent node pose is " << pNode->m_pParentNode->m_oCurrentPose;
                    pNode->m_pParentNode = ii;
                    pNode->m_dDistanceToRootNode = dDistance;
//                    ZLOG_INFO << "Change the parent node, the parent node pose is  " << ii->m_oCurrentPose << "; current is " << pNode->m_oCurrentPose;
                }
            }
        }
        // 递归地计算子树内节点的代价函数
        if (!ii->m_vecChildrenNode.empty())
        {
            RewireChildrenNode(ii->m_vecChildrenNode, pNode);
        }
    }
}

void RRTPlanner::Rewire(std::shared_ptr<RRTNode> pNode)
{
//    ZLOG_INFO << "Enter rewire: " << pNode->m_oCurrentPose;
    RewireChildrenNode(m_pRootNode->m_vecChildrenNode, pNode);
}

bool RRTPlanner::Plan(std::vector<Eigen::Vector<double, 6>> &vecPath)
{
    RobotJoints rand_pose, new_pose;
    int i = 0;
    while (i < m_iMaxIterations)
    {
        // 随机采样一个姿态
        std::shared_ptr<RRTNode> new_node(new RRTNode());
        if (0 == i)
        {
            rand_pose = GetRandomNode(m_oStartPose);
        }
        else
        {
            rand_pose = GetRandomNode(new_pose);
        }
        AddGenerateJoints(rand_pose);
        // 寻找距离随机姿态最近的树节点
        auto nearest_node = GetNearestNode(rand_pose);
//        ZLOG_INFO << " The nearest is:  " << nearest_node->m_oCurrentPose;
        // 在两个节点之间插入新节点
        new_pose = rand_pose;
        new_node->m_oCurrentPose = new_pose;
        new_node->m_pParentNode = nearest_node;
        new_node->m_dDistanceToRootNode =
            nearest_node->m_dDistanceToRootNode + GetDistance(new_node->m_oCurrentPose, nearest_node->m_oCurrentPose);

        // 若新节点无效，则删除该节点，重新采样随机姿态
        if (!IsReachAble(nearest_node->m_oCurrentPose, new_node->m_oCurrentPose))
        {
            ZLOG << "======================" << new_node->m_oCurrentPose;
            continue;
        }
//        ZLOG_INFO << " the pose is reachable: " << new_node->m_oCurrentPose;
        Rewire(new_node);
        if (new_node->IsEqual(m_oTargetPose))
        {
            nearest_node->m_vecChildrenNode.push_back(new_node);
            std::shared_ptr<RRTNode> pTargetNode(new RRTNode());
            pTargetNode->m_pParentNode = new_node;
            pTargetNode->m_oCurrentPose = m_oTargetPose;
            // 从新节点重新向根节点回溯，并递归计算子树内节点的代价函数
            Rewire(pTargetNode);
            nearest_node->m_vecChildrenNode.at(nearest_node->m_vecChildrenNode.size() - 1)
                ->m_vecChildrenNode.push_back(pTargetNode);
            ZLOG_INFO << " Add ok: " << pTargetNode->m_oCurrentPose << "; "
                      << nearest_node->m_vecChildrenNode.at(nearest_node->m_vecChildrenNode.size() - 1)->m_oCurrentPose;
            GePath(pTargetNode, vecPath);
            // 如果当前节点已经在目标节点附近，则生成最短路径
//            SmoothPath(vecPath);
            return true;
        }
        // 将新节点添加到树中
        nearest_node->m_vecChildrenNode.push_back(new_node);

        ZLOG_INFO << " Add ok: " << new_node->m_oCurrentPose << "; " << new_node->m_pParentNode->m_oCurrentPose;
        // 从新节点重新向根节点回溯，并递归计算子树内节点的代价函数
        i++;
    }
    // 迭代次数达到最大值，无法规划出路径
    ZLOG_ERR << "Failed to plan a trajectory";
    return false;
}

bool RRTPlanner::IsReachAble(const RobotJoints &a, const RobotJoints &b)
{
    double dDistance = GetDistance(a, b);
    int iStep = int(dDistance / 0.1);
    std::vector<Eigen::Vector<double, 6>> vecTheta;
    Eigen::Vector<double, 6> Joints;
    // from target to start point
    for (int ij = 0; ij < iStep; ++ij)
    {
        for (int ii = 0; ii < 6; ++ii)
        {
            Joints[ii] = b.m_dAngle[ii] - 0.1 * ij;
        }
        vecTheta.push_back(Joints);
    }

    // add start point
    if ((b.m_dAngle[0] - a.m_dAngle[0] - 0.1 * iStep) > 1e-5)
    {
        for (int ii = 0; ii < 6; ++ii)
        {
            Joints[ii] = a.m_dAngle[ii];
        }
    }
    vecTheta.push_back(Joints);

    for (auto &jj : vecTheta)
    {
        std::cout << std::flush;
        if (m_oCollisionDetection.IsCollision(jj))
        {
            return false;
        }
    }
//    ZLOG_INFO << " Is ok pose: " << b;
    return true;
}

void RRTPlanner::GetNearestChileNode(std::shared_ptr<RRTNode> &pRRTNode, const RobotJoints &oPose, double &dDistance,
    std::shared_ptr<RRTNode> &outRRTNode)
{
    for (auto &ii : pRRTNode->m_vecChildrenNode)
    {
        GetNearestChileNode(ii, oPose, dDistance, outRRTNode);
    }
    double min_distance = GetDistance(pRRTNode->m_oCurrentPose, oPose);
    if (min_distance < dDistance)
    {
        dDistance = min_distance;
        outRRTNode = pRRTNode;
    }
}

void RRTPlanner::GePath(std::shared_ptr<RRTNode> pRRTNode, std::vector<Eigen::Vector<double, 6>> &vecPath)
{
    Eigen::Vector<double, 6> vecJoint = pRRTNode->m_oCurrentPose.ToEigenVector();
    vecPath.push_back(vecJoint);
    if (pRRTNode->m_pParentNode == nullptr)
    {
        return;
    }
    GePath(pRRTNode->m_pParentNode, vecPath);
}

void RRTPlanner::SmoothPath(std::vector<Eigen::Vector<double, 6>> &vecPath)
{
    std::vector<Eigen::Vector<double, 6>> Path;
    double dDistance = 0.0;
    for (int ii = (int)vecPath.size() - 1; ii > 0; ii--)
    {

        Eigen::Vector<double, 6> vecDistance = vecPath.at(ii) - vecPath.at(ii - 1);

        for (int jj = 0; jj < 6; ++jj)
        {
            if (std::fabs(vecDistance[jj]) > 0.1)
            {
                if (dDistance < std::fabs(vecDistance[jj]))
                {
                    dDistance = std::fabs(vecDistance[jj]);
                }
            }
        }
        if (dDistance > 0.1)
        {
            int iStep = int(dDistance / 0.02);
            for (int ji = 0; ji < iStep; ++ji)
            {
                Eigen::Vector<double, 6> oJoint;
                for (int ij = 0; ij < 6; ++ij)
                {
                    double dStepDistance = vecDistance[ij] / iStep;
                    oJoint[ij] = vecPath.at(ii)[ij] - ji * dStepDistance;
                }
                Path.push_back(oJoint);
            }
        }
        else
        {
            Path = vecPath;
        }
    }
    if (dDistance > 0.1)
    {
        Path.push_back(m_oTargetPose.ToEigenVector());
    }
    vecPath = Path;
}

} // namespace zl