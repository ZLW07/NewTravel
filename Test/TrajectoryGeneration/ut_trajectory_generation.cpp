//
// Created by wei on 2023/6/5.
//

#include "ut_trajectory_generation.h"

namespace zl
{

TEST_F(UTTrajectoryGeneration, VecToSO3Test)
{
    RobotJoints start_pose, goal_pose;
    start_pose.m_dAngle[0] = 0.0;
    start_pose.m_dAngle[1] = 0.0;
    start_pose.m_dAngle[2] = 0.0;
    start_pose.m_dAngle[3] = 0.0;
    start_pose.m_dAngle[4] = 0.0;
    start_pose.m_dAngle[5] = 0.0;
    goal_pose.m_dAngle[0] = 1.0;
    goal_pose.m_dAngle[1] = 1.0;
    goal_pose.m_dAngle[2] = 1.0;
    goal_pose.m_dAngle[3] = 1.0;
    goal_pose.m_dAngle[4] = 1.0;
    goal_pose.m_dAngle[5] = 1.0;
    // 定义RRTPlanner实例
    RRTPlanner planner(start_pose, goal_pose, 0.0017, 100);
    // 进行规划
    std::vector<Eigen::Vector<double, 6>> vecPath;
    bool success = planner.Plan(vecPath);
    ZLOG_INFO << "The result is " << success << "the path size is " << vecPath.size();
    for (auto & ii : vecPath)
    {
        ZLOG_INFO << ii[0] << ", " << ii[1] << ", " << ii[2] << ", "
                  << ii[3] << ", " << ii[4] << ", " <<ii[5]  ;
    }
}
} // namespace zl