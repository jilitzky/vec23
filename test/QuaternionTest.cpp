/// Copyright (c) 2026 Jose Ilitzky

#include <cmath>
#include <gtest/gtest.h>
#include <Vec23/Quaternion.h>

using namespace Vec23;

// TODO: Improve the way the tests are written

TEST(QuaternionTest, DefaultConstructorIsIdentity)
{
    TQuaternion<float> q;
    EXPECT_FLOAT_EQ(q.w, 1.0f);
    EXPECT_FLOAT_EQ(q.x, 0.0f);
    EXPECT_FLOAT_EQ(q.y, 0.0f);
    EXPECT_FLOAT_EQ(q.z, 0.0f);
}

TEST(QuaternionTest, ParameterConstructor)
{
    TQuaternion<double> q(1.0, 2.0, 3.0, 4.0);
    EXPECT_DOUBLE_EQ(q.w, 1.0);
    EXPECT_DOUBLE_EQ(q.x, 2.0);
    EXPECT_DOUBLE_EQ(q.y, 3.0);
    EXPECT_DOUBLE_EQ(q.z, 4.0);
}

TEST(QuaternionTest, FromAxisAngle)
{
    TVector3<float> axis(0, 0, 1);
    auto q = TQuaternion<float>::FromAxisAngle(axis, 90.0f);
    TQuaternion<float> expected(0.70710678f, 0, 0, 0.70710678f);
    EXPECT_TRUE(q.IsNearlyEqual(expected));
}

// TODO: Investigate why this test is failing
TEST(QuaternionTest, MultiplicationOperator)
{
    // Rotate 90 deg X, then 90 deg Y
    auto qX = TQuaternion<float>::FromAxisAngle({ 1, 0, 0 }, 90.0f);
    auto qY = TQuaternion<float>::FromAxisAngle({ 0, 1, 0 }, 90.0f);
    TQuaternion<float> result = qY * qX; // Applying X then Y
    EXPECT_TRUE(result.IsNearlyEqual(TQuaternion<float>(0.5f, 0.5f, 0.5f, -0.5f)));
}

TEST(QuaternionTest, MultiplicationAssignmentOperator)
{
    TQuaternion<float> q(1, 0, 0, 0); // Identity
    TQuaternion<float> rot(0.5f, 0.5f, 0.5f, 0.5f);
    q *= rot;
    EXPECT_TRUE(q.IsNearlyEqual(rot));
}