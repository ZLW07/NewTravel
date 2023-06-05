//
// Created by wei on 2023/6/5.
//

#include "TrajectoryGeneration/trajectory_generation_rrt.h"

namespace zl
{
RRTPlanner::RRTPlanner(const RobotPose &oStartPose, const RobotPose &oTargetPose, double dStepSize, int iMaxIterations)
    : m_oStartPose(oStartPose), m_oTargetPose(oTargetPose), m_dStepSize(dStepSize), m_iMaxIterations(iMaxIterations)
{
    m_pRootNode = new RRTNode();
    m_pRootNode->m_oCurrentPose = oStartPose;
    m_pRootNode->m_pParentNode = nullptr;
    m_pRootNode->m_dDistanceToRootNode = 0.0;
}

RRTPlanner::~RRTPlanner()
{
    Clear();
}

bool RRTPlanner::IsValid(const RobotPose &oPose)
{
    const double pi = M_PI;
    // 判断每个关节的角度是否在 [-pi, pi] 的范围内
    for (int ii = 0; ii < 6; ++ii)
    {
        if (oPose.dAngle[ii] < -pi || oPose.dAngle[ii] > pi)
        {
            return false;
        }
    }
    // 如果所有关节角度都在 [-pi, pi] 的范围内，则该姿态有效
    return true;
}

RRTNode *RRTPlanner::GetNearestNode(const RobotPose &pPose)
{
    RRTNode *nearest_node = m_pRootNode;
    double min_distance = GetDistance(nearest_node->m_oCurrentPose, pPose);
    double cur_distance = 0.0;
    // 递归地寻找距离目标姿态最近的树节点
    for (RRTNode *node : nearest_node->m_vecChildrenNode)
    {
        cur_distance = GetDistance(node->m_oCurrentPose, pPose);
        if (cur_distance < min_distance)
        {
            min_distance = cur_distance;
            nearest_node = node;
        }
    }
    return nearest_node;
}

RobotPose RRTPlanner::NewConfig(const RRTNode &oA, const RobotPose &oB, const double &dStepSize)
{
    RobotPose pose;
    const double pi = M_PI;
    // 在两个姿态之间进行线性插值，生成一个新姿态
    double dist = GetDistance(oA.m_oCurrentPose, oB);
    double ratio = dStepSize / dist;
    for (int ii = 0; ii < 6; ++ii)
    {
        pose.dAngle[ii] = (1 - ratio) * oA.m_oCurrentPose.dAngle[ii] + oB.dAngle[ii];
    }

    // 对旋转部分进行球面线性插值
    Eigen::Quaterniond q_a, q_b, q_c;
    q_a = Eigen::AngleAxisd(oA.m_oCurrentPose.dAngle[0], Eigen::Vector3d::UnitZ()) *
          Eigen::AngleAxisd(oA.m_oCurrentPose.dAngle[1], Eigen::Vector3d::UnitY()) *
          Eigen::AngleAxisd(oA.m_oCurrentPose.dAngle[2], Eigen::Vector3d::UnitY()) *
          Eigen::AngleAxisd(oA.m_oCurrentPose.dAngle[3], Eigen::Vector3d::UnitY()) *
          Eigen::AngleAxisd(oA.m_oCurrentPose.dAngle[4], Eigen::Vector3d::UnitZ()) *
          Eigen::AngleAxisd(oA.m_oCurrentPose.dAngle[5], Eigen::Vector3d::UnitY());
    q_b = Eigen::AngleAxisd(oB.dAngle[0], Eigen::Vector3d::UnitZ()) *
          Eigen::AngleAxisd(oB.dAngle[1], Eigen::Vector3d::UnitY()) *
          Eigen::AngleAxisd(oB.dAngle[2], Eigen::Vector3d::UnitY()) *
          Eigen::AngleAxisd(oB.dAngle[3], Eigen::Vector3d::UnitY()) *
          Eigen::AngleAxisd(oB.dAngle[4], Eigen::Vector3d::UnitZ()) *
          Eigen::AngleAxisd(oB.dAngle[5], Eigen::Vector3d::UnitY());
    q_c = q_a.slerp(ratio, q_b);
    Eigen::AngleAxisd aa(q_c);
    pose.dAngle[0] = aa.axis()(2) * aa.angle();
    pose.dAngle[1] = aa.axis()(1) * aa.angle();
    pose.dAngle[2] = aa.axis()(1) * aa.angle();
    pose.dAngle[3] = aa.axis()(1) * aa.angle();
    pose.dAngle[4] = aa.axis()(2) * aa.angle();
    pose.dAngle[5] = aa.axis()(1) * aa.angle();
    return pose;
}

RobotPose RRTPlanner::GetRandomNode()
{
    RobotPose pose;
    // 随机生成关节角度
    for (int i = 0; i < 6; ++i)
    {
        pose.dAngle[i] = RandAngle(i);
    }
    return pose;
}

double RRTPlanner::RandAngle(int i)
{
    double angle_min[6] = {-2.35619, -1.5708, -2.35619, -2.35619, -2.35619, -6.28319};
    double angle_max[6] = {2.35619, 1.39626, 2.0944, 2.35619, 2.35619, 6.28319};
    double r = (double)rand() / RAND_MAX;
    return angle_min[i] + r * (angle_max[i] - angle_min[i]);
}

void RRTPlanner::ClearNode(RRTNode *oNode)
{
    for (RRTNode *child : oNode->m_vecChildrenNode)
    {
        ClearNode(child);
    }
    delete oNode;
}

void RRTPlanner::Clear()
{
    ClearNode(m_pRootNode);
}

double RRTPlanner::GetDistance(const RobotPose &a, const RobotPose &b)
{
    double dist = 0.0;
    for (int i = 0; i < 6; ++i)
    {
        dist += std::pow(a.dAngle[i] - b.dAngle[i], 2);
    }
    return std::sqrt(dist);
}

bool RRTPlanner::Extend(RRTNode *pNode)
{
    RRTNode *nearest_node = nullptr;
    RRTNode *new_node = nullptr;
    RobotPose new_pose;

    // 随机采样一个姿态
    new_pose = GetRandomNode();

    // 寻找距离随机姿态最近的树节点
    nearest_node = GetNearestNode(new_pose);

    // 在两个节点之间插入新节点
    new_pose = NewConfig(*nearest_node, pNode->m_oCurrentPose, m_dStepSize);
    new_node = new RRTNode();
    new_node->m_oCurrentPose = new_pose;
    new_node->m_pParentNode = nearest_node;
    new_node->m_dDistanceToRootNode =
        nearest_node->m_dDistanceToRootNode + GetDistance(new_node->m_oCurrentPose, nearest_node->m_oCurrentPose);

    // 若新节点无效，则删除该节点
    if (!IsValid(new_node->m_oCurrentPose))
    {
        delete new_node;
        return false;
    }

    // 将新节点添加到树中
    nearest_node->m_vecChildrenNode.push_back(new_node);

    // 从新节点重新向根节点回溯，并递归计算子树内节点的代价函数
    Rewire(new_node);

    // 如果当前节点已经在目标节点附近，则生成最短路径
    if (new_node->isEqual(m_oTargetPose))
    {
        return true;
    }
    return false;
}

void RRTPlanner::Rewire(RRTNode *pNode)
{
    for (RRTNode *node : pNode->m_vecChildrenNode)
    {
        node->m_dDistanceToRootNode =
            pNode->m_dDistanceToRootNode + GetDistance(node->m_oCurrentPose, pNode->m_oCurrentPose);

        // 如果当前节点到新节点的路径更短，则更新父节点
        if (node->m_dDistanceToRootNode >
            pNode->m_dDistanceToRootNode + GetDistance(node->m_oCurrentPose, pNode->m_oCurrentPose))
        {
            node->m_pParentNode = pNode;
            node->m_dDistanceToRootNode =
                pNode->m_dDistanceToRootNode + GetDistance(node->m_oCurrentPose, pNode->m_oCurrentPose);
        }
        // 递归地计算子树内节点的代价函数
        Rewire(node);
    }
}

bool RRTPlanner::Plan()
{
    srand(time(NULL));

    RRTNode *nearest_node = nullptr;
    RRTNode *new_node = nullptr;
    RobotPose rand_pose, new_pose;
    double min_cost;
    int i = 0;

    while (i < m_iMaxIterations)
    {
        // 随机采样一个姿态
        rand_pose = GetRandomNode();
        // 若随机姿态无效，则重新采样
        if (!IsValid(rand_pose))
        {
            continue;
        }
        // 寻找距离随机姿态最近的树节点
        nearest_node = GetNearestNode(rand_pose);
        // 在两个节点之间插入新节点
        new_pose = NewConfig(*nearest_node, rand_pose, m_dStepSize);
        new_node = new RRTNode();
        new_node->m_oCurrentPose = new_pose;
        new_node->m_pParentNode = nearest_node;
        new_node->m_dDistanceToRootNode =
            nearest_node->m_dDistanceToRootNode + GetDistance(new_node->m_oCurrentPose, nearest_node->m_oCurrentPose);

        // 若新节点无效，则删除该节点，重新采样随机姿态
        if (!IsValid(new_node->m_oCurrentPose))
        {
            delete new_node;
            continue;
        }

        // 将新节点添加到树中
        nearest_node->m_vecChildrenNode.push_back(new_node);

        // 从新节点重新向根节点回溯，并递归计算子树内节点的代价函数
        Rewire(new_node);
        // 如果当前节点已经在目标节点附近，则生成最短路径
        if (new_node->isEqual(m_oTargetPose))
        {
            return true;
        }
        i++;
    }
    // 迭代次数达到最大值，无法规划出路径
    ZLOG_ERR << "Failed to plan a trajectory";
    return false;
}


} // namespace zl