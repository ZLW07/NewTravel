//
// Created by zlw on 2023/9/10.
//

#ifndef NEWTRAVEL_UT_STUABLI_KINEMATICS_H
#define NEWTRAVEL_UT_STUABLI_KINEMATICS_H

#include "StuabilKinematics/robot_stuabil_kinematics.h"
#include "gtest/gtest.h"

class TestStuabliKinematics : public ::testing::Test
{
public:
    TestStuabliKinematics(){};
    ~TestStuabliKinematics() {}

//private:
    StuRobotKinematics m_oStuRobotKinematics;
};

#endif // NEWTRAVEL_UT_STUABLI_KINEMATICS_H
