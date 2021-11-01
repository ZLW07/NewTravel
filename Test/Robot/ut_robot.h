//
// Created by zw on 2021/11/1.
//

#ifndef NEWTRAVEL_UT_ROBOT_H
#define NEWTRAVEL_UT_ROBOT_H

#include "gtest/gtest.h"

#include "Robot/robot_six_axis.h"
#include "Robot/robot_six_axis_screw_array.h"

class RobotTest : public ::testing::Test
{
public:
    RobotTest();
    ~RobotTest();

private:
};

RobotTest::RobotTest(){};
RobotTest::~RobotTest(){};

TEST_F(RobotTest, SixAxisArray)
{
    Vector6D oVec6D(1, 2, 3, 4, 5, 6);
    Axis6ScrewAry oSixAxisVec6DAry;
    oSixAxisVec6DAry.PushBack(oVec6D);
    oSixAxisVec6DAry.PushBack(oVec6D);
    ZLOG << oSixAxisVec6DAry;
}

TEST_F(RobotTest, Axis6Math)
{
    Vector6D oVec6D1(0, 0, 1, 4, 0,    0);
    Vector6D oVec6D2(0, 0, 0, 0, 1,    0);
    Vector6D oVec6D3(0, 0, -1, -6, 0,    -0.1);
    Axis6ScrewAry oSixAxisVec6DAry;
    oSixAxisVec6DAry.PushBack(oVec6D1);
    oSixAxisVec6DAry.PushBack(oVec6D2);
    oSixAxisVec6DAry.PushBack(oVec6D3);
    Vector6D oVec6DTheta(1.5708,3.000000,3.1415926,0.0,0.0,0.0);
    RotateMat oRat(1);
    oRat[0][0] = -1;
    oRat[2][2] = -1;
    Vector3D oV3d(0,6,2);
    Se3Matrix oSe3(oRat,oV3d);
    Axis6Se3 oAxis6;
    oAxis6.GetKinSpace(oSe3,oSixAxisVec6DAry,oVec6DTheta);
    /*  expect result:
     * -0.0000    1.0000         0          -5.0000
     *  1.0000    0.0000         0          4.0000
     *  0         0             -1.0000     1.6858
     *  0         0             0           1.0000
     */
    ZLOG << oSe3;
}

#endif // NEWTRAVEL_UT_ROBOT_H
