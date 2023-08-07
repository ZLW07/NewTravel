//
// Created by wei on 2023/8/7.
//

#ifndef NEWTRAVEL_UT_STAUBLI_KINEMATICS_H
#define NEWTRAVEL_UT_STAUBLI_KINEMATICS_H

#include "StuabilKinematics/robot_stuabil_kinematics.h"

#include "gtest/gtest.h"

class TestStaubliKinematics : public ::testing::Test
{
public:
    TestStaubliKinematics(){};
    ~TestStaubliKinematics() {}

public:
    StuRobotKinematics m_oStuRobotKinematics;
};

#endif // NEWTRAVEL_UT_STAUBLI_KINEMATICS_H
