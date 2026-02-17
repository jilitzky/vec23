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
    Vector3 axis(0.0f, 1.0f, 0.0f);
    auto q = Quaternion::FromAxisAngle(axis, 90.0f);
    EXPECT_TRUE(q.IsNearlyEqual({ 0.707106781f, 0.0f, 0.707106781f, 0.0f }));
}

TEST(QuaternionTest, FromEulerCombined)
{
    auto q = Quaternion::FromEuler(45.0f, 45.0f, 45.0f);
    EXPECT_TRUE(q.IsNearlyEqual(Quaternion(0.8446232f, 0.1913417f, 0.4619398f, 0.1913417f)));
}

TEST(QuaternionTest, FromEulerPure)
{
    auto qRoll = Quaternion::FromEuler(90.0f, 0.0f, 0.0f);
    EXPECT_TRUE(qRoll.IsNearlyEqual(Quaternion(0.707106781f, 0.707106781f, 0.0f, 0.0f)));

    auto qPitch = Quaternion::FromEuler(0.0f, 90.0f, 0.0f);
    EXPECT_TRUE(qPitch.IsNearlyEqual(Quaternion(0.707106781f, 0.0f, 0.707106781f, 0.0f)));

    auto qYaw = Quaternion::FromEuler(0.0f, 0.0f, 90.0f);
    EXPECT_TRUE(qYaw.IsNearlyEqual(Quaternion(0.707106781f, 0.0f, 0.0f, 0.707106781f)));
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

TEST(QuaternionTest, Lerp)
{
    Quaternion begin = Quaternion::Identity();
    Quaternion end = Quaternion::FromAxisAngle({ 0.0f, 0.0f, 1.0f }, 90.0f);
    Quaternion lerp = Quaternion::Lerp(begin, end, 0.5f);
    Quaternion expected = Quaternion::FromAxisAngle({ 0.0f, 0.0f, 1.0f }, 45.0f);
    EXPECT_TRUE(lerp.IsNearlyEqual(expected));
    EXPECT_TRUE(lerp.IsNormalized());
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
    Vector3 v(1.0f, 0.0f, 0.0f);
    auto q = Quaternion::FromAxisAngle({ 0.0f, 1.0f, 0.0f }, 90.0f);
    Vector3 result = q.RotateVector(v);
    EXPECT_TRUE(result.IsNearlyEqual({ 0.0f, 0.0f, -1.0f }));
}

TEST(QuaternionTest, SlerpConstantVelocity)
{
    Quaternion q1 = Quaternion::Identity();
    Quaternion q2 = Quaternion::FromAxisAngle({ 1.0f, 0.0f, 0.0f }, 90.0f);
    Quaternion slerp = Quaternion::Slerp(q1, q2, 0.25f);
    Quaternion expected = Quaternion::FromAxisAngle({ 1.0f, 0.0f, 0.0f }, 22.5f);
    EXPECT_TRUE(slerp.IsNearlyEqual(expected, kToleranceEpsilon));
}

TEST(QuaternionTest, SlerpPrecisionSmallAngle)
{
    Quaternion q1 = Quaternion::Identity();
    Quaternion q2 = Quaternion::FromAxisAngle({ 0.0f, 1.0f, 0.0f }, 0.0001f);
    Quaternion result = Quaternion::Slerp(q1, q2, 0.5f);
    EXPECT_FALSE(std::isnan(result.w));
    EXPECT_TRUE(result.IsNormalized());
}

TEST(QuaternionTest, SlerpShortestPath)
{
    Quaternion q1(1.0f, 0.0f, 0.0f, 0.0f);
    Quaternion q2(-1.0f, 0.0f, 0.0f, 0.0f);
    Quaternion result = Quaternion::Slerp(q1, q2, 0.5f);
    EXPECT_NEAR(std::abs(result.w), 1.0f, kToleranceEpsilon);
    EXPECT_NEAR(result.x, 0.0f, kToleranceEpsilon);
    EXPECT_NEAR(result.y, 0.0f, kToleranceEpsilon);
    EXPECT_NEAR(result.z, 0.0f, kToleranceEpsilon);
}

TEST(QuaternionTest, ToAxisAngle)
{
    Quaternion q(0.707106781f, 0.0f, 0.707106781f, 0.0f);
    Vector3 axis;
    float degrees;
    q.ToAxisAngle(axis, degrees);
    EXPECT_TRUE(axis.IsNearlyEqual({ 0.0f, 1.0f, 0.0f }));
    EXPECT_NEAR(degrees, 90.0f, kToleranceEpsilon);
}

TEST(QuaternionTest, ToEuler)
{
    float roll = 30.0f;
    float pitch = 15.0f;
    float yaw = 45.0f;
    auto q = Quaternion::FromEuler(roll, pitch, yaw);
    auto result = q.ToEuler();
    EXPECT_NEAR(result.x, roll, kToleranceEpsilon);
    EXPECT_NEAR(result.y, pitch, kToleranceEpsilon);
    EXPECT_NEAR(result.z, yaw, kToleranceEpsilon);
}

TEST(QuaternionTest, ToEulerGimbalLock)
{
    auto q = Quaternion::FromEuler(0.0f, 90.0f, 45.0f);
    auto result = q.ToEuler();
    EXPECT_NEAR(result.x, 0.0f, kToleranceEpsilon);
    EXPECT_NEAR(result.y, 90.0f, kToleranceEpsilon);
    EXPECT_NEAR(result.z, 45.0f, kToleranceEpsilon);
}
