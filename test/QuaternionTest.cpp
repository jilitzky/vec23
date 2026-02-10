/// Copyright (c) 2026 Jose Ilitzky

#include <cmath>
#include <gtest/gtest.h>
#include <Vec23/Quaternion.h>

using namespace Vec23;

TEST(QuaternionTest, DefaultConstructorIsIdentity)
{
    Quaternion q;
    EXPECT_FLOAT_EQ(q.w, 1.0f);
    EXPECT_FLOAT_EQ(q.x, 0.0f);
    EXPECT_FLOAT_EQ(q.y, 0.0f);
    EXPECT_FLOAT_EQ(q.z, 0.0f);
}

TEST(QuaternionTest, FromAxisAngle)
{
    Vector3 axis(0, 1, 0);
    auto q = Quaternion::FromAxisAngle(axis, 90.0f);
    EXPECT_TRUE(q.IsNearlyEqual({ 0.707106f, 0, 0.707106f, 0 }));
}

TEST(QuaternionTest, MultiplicationAssignmentOperator)
{
    auto q = Quaternion::Identity();
    Quaternion rotation(0.5f, 0.5f, 0.5f, 0.5f);
    q *= rotation;
    EXPECT_TRUE(q.IsNearlyEqual(rotation));
}

TEST(QuaternionTest, MultiplicationOperator)
{
    auto qX = Quaternion::FromAxisAngle({ 1, 0, 0 }, 90.0f);
    auto qY = Quaternion::FromAxisAngle({ 0, 1, 0 }, 90.0f);
    Quaternion result = qY * qX;
    EXPECT_TRUE(result.IsNearlyEqual({ 0.5f, 0.5f, 0.5f, -0.5f }));
}

TEST(QuaternionTest, ParameterConstructor)
{
    TQuaternion<double> q(1.0, 2.0, 3.0, 4.0);
    EXPECT_DOUBLE_EQ(q.w, 1.0);
    EXPECT_DOUBLE_EQ(q.x, 2.0);
    EXPECT_DOUBLE_EQ(q.y, 3.0);
    EXPECT_DOUBLE_EQ(q.z, 4.0);
}
