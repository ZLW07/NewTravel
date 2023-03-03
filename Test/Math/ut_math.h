//
// Created by wei on 2022/4/19.
//

#ifndef NEWTRAVEL_UT_MATH_H
#define NEWTRAVEL_UT_MATH_H

#include "Eigen/Eigen"
#include "Log/log.h"
#include "Math/math_rotation.h"
#include "Math/math_vector3d.h"
#include <iostream>

#include "gtest/gtest.h"

namespace zl
{
class TestMath : public ::testing::Test
{
public:
    TestMath() = default;
    ~TestMath() {}

private:
};

TEST_F(TestMath, TestOBB_E)
{
    std::vector<Eigen::Vector3d> vecSrc;
    Eigen::Vector3d v3d(3.7, 1.7, 3.5);
    vecSrc.push_back(v3d);
    v3d = {4.1, 3.8, 5.2};
    vecSrc.push_back(v3d);
    v3d = {4.7, 2.9, 2.1};
    vecSrc.push_back(v3d);
    v3d = {5.2, 2.8, 6.0};
    vecSrc.push_back(v3d);
    Rotation rot;
    rot.CovarianceMatrix(vecSrc);
    //    {0.435833 0.166667 0.333333} {0.166667 0.74 0.52} {0.333333 0.52 3.04667}
    ZLOG << rot;
    auto result = rot.GetOBBDirectionVector(rot);
    //    {-0.760026 -0.290641 -0.581282} {0.491677 -0.842044 -0.221846} {0.424987 0.454412 -0.782877}
    ZLOG << result;
}
}
#endif // NEWTRAVEL_UT_MATH_H
