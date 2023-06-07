//
// Created by wei on 2023/6/5.
//

#include "ut_trajectory_generation.h"

namespace zl
{
TEST_F(UTTrajectoryGeneration, RandAngle)
{
    RobotPose start_pose, goal_pose;
    RRTPlanner planner(start_pose, goal_pose, 0.1, 1000);
    for (int ii = 0; ii < 100; ++ii)
    {
        for (int jj = 0; jj < 6; ++jj)
        {
            ZLOG_INFO << jj << ": " << planner.RandAngle(jj, start_pose.dAngle[jj]);
        }
    }
}

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
    RRTPlanner planner(start_pose, goal_pose, 0.0017, 100);
    // 进行规划
    std::vector<Eigen::Vector<double, 6>> vecPath;
    bool success = planner.Plan(vecPath);
    ZLOG_INFO << "The result is " << success;
    for (int ii = 0; ii < vecPath.size(); ++ii)
    {
        ZLOG_INFO << vecPath.at(ii)[0] << ", " << vecPath.at(ii)[1] << ", " << vecPath.at(ii)[2] << ", "
                  << vecPath.at(ii)[3] << ", " << vecPath.at(ii)[4] << ", " <<vecPath.at(ii)[5]  ;
    }
}
} // namespace zl