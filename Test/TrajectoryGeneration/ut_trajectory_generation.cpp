//
// Created by wei on 2023/6/5.
//

#include "ut_trajectory_generation.h"

namespace zl
{
TEST_F(UTTrajectoryGeneration, VecToSO3Test)
{
    RobotPose start_pose, goal_pose;
    start_pose.dAngle[0] = 0.0;
    start_pose.dAngle[1] = 0.0;
    start_pose.dAngle[2] = 0.0;
    start_pose.dAngle[3] = 0.0;
    start_pose.dAngle[4] = 0.0;
    start_pose.dAngle[5] = 0.0;
    goal_pose.dAngle[0] = 1.0;
    goal_pose.dAngle[1] = 1.0;
    goal_pose.dAngle[2] = 1.0;
    goal_pose.dAngle[3] = 1.0;
    goal_pose.dAngle[4] = 1.0;
    goal_pose.dAngle[5] = 1.0;
    // 定义RRTPlanner实例
    RRTPlanner planner(start_pose, goal_pose, 0.1, 1000);
    // 进行规划
    bool success = planner.Plan();
    ZLOG_INFO << "The result is " << success;
}
}