/// Copyright (c) 2026 Jose Ilitzky

#include <cmath>
#include <gtest/gtest.h>
#include <Vec23/Quaternion.h>

using namespace Vec23;

TEST(QuaternionTest, Conjugate)
{
    FQuaternion q(2.0f, -1.0f, 1.0f, 3.0f);
    q.Conjugate();
    EXPECT_TRUE(q.IsNearlyEqual({ 2.0f, 1.0f, -1.0f, -3.0f }));
}

TEST(QuaternionTest, DefaultConstructor)
{
    FQuaternion q;
    EXPECT_FLOAT_EQ(q.w, 1.0f);
    EXPECT_FLOAT_EQ(q.x, 0.0f);
    EXPECT_FLOAT_EQ(q.y, 0.0f);
    EXPECT_FLOAT_EQ(q.z, 0.0f);
}

TEST(QuaternionTest, Dot)
{
    FQuaternion q1(1.0f, 2.0f, 3.0f, 4.0f);
    FQuaternion q2(4.0f, 3.0f, 2.0f, 1.0f);
    EXPECT_NEAR(q1.Dot(q2), 20.f, kToleranceEpsilon<float>);
}

TEST(QuaternionTest, EqualsOperator)
{
    FQuaternion q(1.0f, 2.0f, 3.0f, 4.0f);
    EXPECT_TRUE(q == q);
}

TEST(QuaternionTest, FromAxisAngle)
{
    FVector3 axis(0.0f, 1.0f, 0.0f);
    auto q = FQuaternion::FromAxisAngle(axis, 90.0f);
    EXPECT_TRUE(q.IsNearlyEqual({ 0.707106781f, 0.0f, 0.707106781f, 0.0f }));
}

TEST(QuaternionTest, FromEulerCombined)
{
    auto q = FQuaternion::FromEuler(45.0f, 45.0f, 45.0f);
    EXPECT_TRUE(q.IsNearlyEqual(FQuaternion(0.8446232f, 0.1913417f, 0.4619398f, 0.1913417f)));
}

TEST(QuaternionTest, FromEulerPure)
{
    auto qRoll = FQuaternion::FromEuler(90.0f, 0.0f, 0.0f);
    EXPECT_TRUE(qRoll.IsNearlyEqual(FQuaternion(0.707106781f, 0.707106781f, 0.0f, 0.0f)));

    auto qPitch = FQuaternion::FromEuler(0.0f, 90.0f, 0.0f);
    EXPECT_TRUE(qPitch.IsNearlyEqual(FQuaternion(0.707106781f, 0.0f, 0.707106781f, 0.0f)));

    auto qYaw = FQuaternion::FromEuler(0.0f, 0.0f, 90.0f);
    EXPECT_TRUE(qYaw.IsNearlyEqual(FQuaternion(0.707106781f, 0.0f, 0.0f, 0.707106781f)));
}

TEST(QuaternionTest, Inverse)
{
    FQuaternion q(1.0f, 0.0f, 1.0f, 0.0f);
    q.Inverse();
    EXPECT_TRUE(q.IsNearlyEqual({ 0.5f, 0.0f, -0.5f, 0.0f }));
}

TEST(QuaternionTest, IsNormalized)
{
    FQuaternion q1(1.0f, 2.0f, 3.0f, 4.0f);
    EXPECT_FALSE(q1.IsNormalized());

    FQuaternion q2(0.0f, 0.0f, 1.0f, 0.0f);
    EXPECT_TRUE(q2.IsNormalized());
}

TEST(QuaternionTest, Length)
{
    FQuaternion q(1.0f, 1.0f, 1.0f, 1.0f);
    EXPECT_NEAR(q.Length(), 2.0f, kToleranceEpsilon<float>);
    EXPECT_NEAR(q.LengthSquared(), 4.0f, kToleranceEpsilon<float>);
}

TEST(QuaternionTest, Lerp)
{
    FQuaternion begin = FQuaternion::Identity();
    FQuaternion end = FQuaternion::FromAxisAngle({ 0.0f, 0.0f, 1.0f }, 90.0f);
    FQuaternion lerp = FQuaternion::Lerp(begin, end, 0.5f);
    FQuaternion expected = FQuaternion::FromAxisAngle({ 0.0f, 0.0f, 1.0f }, 45.0f);
    EXPECT_TRUE(lerp.IsNearlyEqual(expected));
    EXPECT_TRUE(lerp.IsNormalized());
}

TEST(QuaternionTest, MultiplicationAssignmentOperator)
{
    auto q = FQuaternion::Identity();
    FQuaternion rotation(0.5f, 0.5f, 0.5f, 0.5f);
    q *= rotation;
    EXPECT_TRUE(q.IsNearlyEqual(rotation));
}

TEST(QuaternionTest, MultiplicationOperator)
{
    auto qX = FQuaternion::FromAxisAngle({ 1.0f, 0.0f, 0.0f }, 90.0f);
    auto qY = FQuaternion::FromAxisAngle({ 0.0f, 1.0f, 0.0f }, 90.0f);
    FQuaternion result = qY * qX;
    EXPECT_TRUE(result.IsNearlyEqual({ 0.5f, 0.5f, 0.5f, -0.5f }));
}

TEST(QuaternionTest, MultiplicationScalarOperator)
{
    FQuaternion q(1.0f, 2.0f, 3.0f, 4.0f);
    q *= 2.0f;
    EXPECT_TRUE(q.IsNearlyEqual({ 2.0f, 4.0f, 6.0f, 8.0f }));
}

TEST(QuaternionTest, Normalize)
{
    FQuaternion q(0.0f, 0.0f, 2.0f, 0.0f);
    q.Normalize();
    EXPECT_TRUE(q.IsNearlyEqual({ 0.0f, 0.0f, 1.0f, 0.0f }));
}

TEST(QuaternionTest, ParameterConstructor)
{
    FQuaternion q(1.0f, 2.0f, 3.0f, 4.0f);
    EXPECT_DOUBLE_EQ(q.w, 1.0f);
    EXPECT_DOUBLE_EQ(q.x, 2.0f);
    EXPECT_DOUBLE_EQ(q.y, 3.0f);
    EXPECT_DOUBLE_EQ(q.z, 4.0f);
}

TEST(QuaternionTest, RotateVector)
{
    FVector3 v(1.0f, 0.0f, 0.0f);
    auto q = FQuaternion::FromAxisAngle({ 0.0f, 1.0f, 0.0f }, 90.0f);
    FVector3 result = q.RotateVector(v);
    EXPECT_TRUE(result.IsNearlyEqual({ 0.0f, 0.0f, -1.0f }));
}

TEST(QuaternionTest, SlerpConstantVelocity)
{
    FQuaternion q1 = FQuaternion::Identity();
    FQuaternion q2 = FQuaternion::FromAxisAngle({ 1.0f, 0.0f, 0.0f }, 90.0f);
    FQuaternion slerp = FQuaternion::Slerp(q1, q2, 0.25f);
    FQuaternion expected = FQuaternion::FromAxisAngle({ 1.0f, 0.0f, 0.0f }, 22.5f);
    EXPECT_TRUE(slerp.IsNearlyEqual(expected, kToleranceEpsilon<float>));
}

TEST(QuaternionTest, SlerpPrecisionSmallAngle)
{
    FQuaternion q1 = FQuaternion::Identity();
    FQuaternion q2 = FQuaternion::FromAxisAngle({ 0.0f, 1.0f, 0.0f }, 0.0001f);
    FQuaternion result = FQuaternion::Slerp(q1, q2, 0.5f);
    EXPECT_FALSE(std::isnan(result.w));
    EXPECT_TRUE(result.IsNormalized());
}

TEST(QuaternionTest, SlerpShortestPath)
{
    FQuaternion q1(1.0f, 0.0f, 0.0f, 0.0f);
    FQuaternion q2(-1.0f, 0.0f, 0.0f, 0.0f);
    FQuaternion result = FQuaternion::Slerp(q1, q2, 0.5f);
    EXPECT_NEAR(std::abs(result.w), 1.0f, kToleranceEpsilon<float>);
    EXPECT_NEAR(result.x, 0.0f, kToleranceEpsilon<float>);
    EXPECT_NEAR(result.y, 0.0f, kToleranceEpsilon<float>);
    EXPECT_NEAR(result.z, 0.0f, kToleranceEpsilon<float>);
}

TEST(QuaternionTest, ToAxisAngle)
{
    FQuaternion q(0.707106781f, 0.0f, 0.707106781f, 0.0f);
    FVector3 axis;
    float degrees;
    q.ToAxisAngle(axis, degrees);
    EXPECT_TRUE(axis.IsNearlyEqual({ 0.0f, 1.0f, 0.0f }));
    EXPECT_NEAR(degrees, 90.0f, kToleranceEpsilon<float>);
}

TEST(QuaternionTest, ToEuler)
{
    float roll = 30.0f;
    float pitch = 15.0f;
    float yaw = 45.0f;
    auto q = FQuaternion::FromEuler(roll, pitch, yaw);
    auto result = q.ToEuler();
    EXPECT_NEAR(result.x, roll, kToleranceEpsilon<float>);
    EXPECT_NEAR(result.y, pitch, kToleranceEpsilon<float>);
    EXPECT_NEAR(result.z, yaw, kToleranceEpsilon<float>);
}

TEST(QuaternionTest, ToEulerGimbalLock)
{
    auto q = FQuaternion::FromEuler(0.0f, 90.0f, 45.0f);
    auto result = q.ToEuler();
    EXPECT_NEAR(result.x, 0.0f, kToleranceEpsilon<float>);
    EXPECT_NEAR(result.y, 90.0f, kToleranceEpsilon<float>);
    EXPECT_NEAR(result.z, 45.0f, kToleranceEpsilon<float>);
}
