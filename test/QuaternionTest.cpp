/// Copyright (c) 2026 Jose Ilitzky

#include <cmath>
#include <gtest/gtest.h>
#include <Vec23/Quaternion.h>

using namespace Vec23;

TEST(QuaternionTest, Conjugate)
{
    Quaternion q = { 2.0f, -1.0f, 1.0f, 3.0f };
    q.Conjugate();
    EXPECT_TRUE(q.IsNearlyEqual({ 2.0f, 1.0f, -1.0f, -3.0f }));
}

TEST(QuaternionTest, DefaultConstructor)
{
    Quaternion q;
    EXPECT_FLOAT_EQ(q.w, 1.0f);
    EXPECT_FLOAT_EQ(q.x, 0.0f);
    EXPECT_FLOAT_EQ(q.y, 0.0f);
    EXPECT_FLOAT_EQ(q.z, 0.0f);
}

TEST(QuaternionTest, Dot)
{
}

TEST(QuaternionTest, EqualsOperator)
{
    Quaternion q = { 1.0f, 2.0f, 3.0f, 4.0f };
    EXPECT_TRUE(q == q);
}

TEST(QuaternionTest, FromAxisAngle)
{
    Vector3 axis(0, 1, 0);
    auto q = Quaternion::FromAxisAngle(axis, 90.0f);
    EXPECT_TRUE(q.IsNearlyEqual({ 0.707106f, 0, 0.707106f, 0 }));
}

TEST(QuaternionTest, Inverse)
{
}

TEST(QuaternionTest, IsNormalized)
{
}

TEST(QuaternionTest, Length)
{
}

TEST(QuaternionTest, LengthSquared)
{
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

TEST(QuaternionTest, Normalize)
{
}

TEST(QuaternionTest, ParameterConstructor)
{
    Quaternion q(1.0f, 2.0f, 3.0f, 4.0f);
    EXPECT_DOUBLE_EQ(q.w, 1.0f);
    EXPECT_DOUBLE_EQ(q.x, 2.0f);
    EXPECT_DOUBLE_EQ(q.y, 3.0f);
    EXPECT_DOUBLE_EQ(q.z, 4.0f);
}

TEST(QuaternionTest, RotateVector)
{
}

TEST(QuaternionTest, ToEuler)
{
}

TEST(QuaternionTest, ToAxisAngle)
{
}
