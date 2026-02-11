/// Copyright (c) 2026 Jose Ilitzky

#include <cmath>
#include <gtest/gtest.h>
#include <Vec23/Quaternion.h>

using namespace Vec23;

static constexpr float kToleranceEpsilon = TToleranceEpsilon<float>;
TEST(QuaternionTest, Conjugate)
{
    Quaternion q(2.0f, -1.0f, 1.0f, 3.0f);
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
    Quaternion q1(1.0f, 2.0f, 3.0f, 4.0f);
    Quaternion q2(4.0f, 3.0f, 2.0f, 1.0f);
    EXPECT_NEAR(q1.Dot(q2), 20.f, kToleranceEpsilon);
}

TEST(QuaternionTest, EqualsOperator)
{
    Quaternion q(1.0f, 2.0f, 3.0f, 4.0f);
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
    Quaternion q(1.0f, 0.0f, 1.0f, 0.0f);
    q.Inverse();
    EXPECT_TRUE(q.IsNearlyEqual({ 0.5f, 0.0f, -0.5f, 0.0f }));
}

TEST(QuaternionTest, IsNormalized)
{
    Quaternion q1(1.0f, 2.0f, 3.0f, 4.0f);
    EXPECT_FALSE(q1.IsNormalized());

    Quaternion q2(0.0f, 0.0f, 1.0f, 0.0f);
    EXPECT_TRUE(q2.IsNormalized());
}

TEST(QuaternionTest, Length)
{
    Quaternion q(1.0f, 1.0f, 1.0f, 1.0f);
    EXPECT_NEAR(q.Length(), 2.0f, kToleranceEpsilon);
    EXPECT_NEAR(q.LengthSquared(), 4.0f, kToleranceEpsilon);
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
    auto qX = Quaternion::FromAxisAngle({ 1.0f, 0.0f, 0.0f }, 90.0f);
    auto qY = Quaternion::FromAxisAngle({ 0.0f, 1.0f, 0.0f }, 90.0f);
    Quaternion result = qY * qX;
    EXPECT_TRUE(result.IsNearlyEqual({ 0.5f, 0.5f, 0.5f, -0.5f }));
}

TEST(QuaternionTest, Normalize)
{
    Quaternion q(0.0f, 0.0f, 2.0f, 0.0f);
    q.Normalize();
    EXPECT_TRUE(q.IsNearlyEqual({ 0.0f, 0.0f, 1.0f, 0.0f }));
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
    Vector3 v(1, 0, 0);
    auto q = Quaternion::FromAxisAngle({ 0.0f, 1.0f, 0.0f }, 90.0f);
    Vector3 result = q.RotateVector(v);
    EXPECT_TRUE(result.IsNearlyEqual({ 0.0f, 0.0f, -1.0f }));
}

TEST(QuaternionTest, ToEuler)
{
}

TEST(QuaternionTest, ToAxisAngle)
{
}
