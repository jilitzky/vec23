/// Copyright (c) 2026 Jose Ilitzky

#include <cmath>
#include <gtest/gtest.h>
#include <Vec23/Vector2.h>

using namespace Vec23;

TEST(Vector2Test, Addition)
{
    Vector2 v1(1.0f, 2.0f);
    Vector2 v2(3.0f, 4.0f);
    Vector2 result = v1 + v2;
    EXPECT_TRUE(result.IsNearlyEqual({ 4.0f, 6.0f }));
}

TEST(Vector2Test, Angle)
{
    Vector2 a(1.0f, 0.0f);
    Vector2 b(0.0f, -1.0f);
    EXPECT_NEAR(Vector2::Angle(a, b), 90.0f, Vector2::kToleranceEpsilon);
}

TEST(Vector2Test, AngleEdgeCases)
{
    Vector2 v(1.0f, 0.0f);
    EXPECT_NEAR(Vector2::Angle(v, v), 0.0f, Vector2::kToleranceEpsilon);
    EXPECT_NEAR(Vector2::Angle(v, -v), 180.0f, Vector2::kToleranceEpsilon);
}

TEST(Vector2Test, ComponentConstructor)
{
    Vector2 v(2.0f, 3.0f);
    EXPECT_FLOAT_EQ(v.x, 2.0f);
    EXPECT_FLOAT_EQ(v.y, 3.0f);
}

TEST(Vector2Test, ComponentMultiplication)
{
    Vector2 v1(2.0f, 3.0f);
    Vector2 v2(4.0f, 5.0f);
    Vector2 result = v1 * v2;
    EXPECT_TRUE(result.IsNearlyEqual({ 8.0f, 15.0f }));
}

TEST(Vector2Test, CompoundAddition)
{
    Vector2 v1(1.0f, 2.0f);
    Vector2 v2(3.0f, 4.0f);
    v1 += v2;
    EXPECT_TRUE(v1.IsNearlyEqual({ 4.0f, 6.0f }));
}

TEST(Vector2Test, CompoundScalarMultiplication)
{
    Vector2 v(2.0f, 4.0f);
    v *= 0.5f;
    EXPECT_TRUE(v.IsNearlyEqual({ 1.0f, 2.0f }));
}

TEST(Vector2Test, CompoundSubtraction)
{
    Vector2 v1(5.0f, 6.0f);
    Vector2 v2(2.0f, 3.0f);
    v1 -= v2;
    EXPECT_TRUE(v1.IsNearlyEqual({ 3.0f, 3.0f }));
}

TEST(Vector2Test, CrossProduct)
{
    Vector2 right(1.0f, 0.0f);
    Vector2 up(0.0f, 1.0f);

    EXPECT_TRUE(right.Cross(up) == 1.0f);
    EXPECT_TRUE(up.Cross(right) == -1.0f);
}

TEST(Vector2Test, DefaultConstructor)
{
    Vector2 v;
    EXPECT_FLOAT_EQ(v.x, 0.0f);
    EXPECT_FLOAT_EQ(v.y, 0.0f);
}

TEST(Vector2Test, Distance)
{
    Vector2 v1(0.0f, 0.0f);
    Vector2 v2(0.0f, 10.0f);
    EXPECT_TRUE(Vector2::Distance(v1, v2) == 10.0f);
    EXPECT_TRUE(Vector2::DistanceSquared(v1, v2) == 100.0f);
}

TEST(Vector2Test, DivisionByZero)
{
    Vector2 v(10.0f, 10.0f);
    Vector2 result = v / 0.0f;
    EXPECT_TRUE(std::isinf(result.x));
    EXPECT_TRUE(std::isinf(result.y));
}

TEST(Vector2Test, DotProduct)
{
    Vector2 v1(1.0f, 0.0f);
    Vector2 v2(2.0f, 0.0f);
    EXPECT_TRUE(v1.Dot(v2) == 2.0f);

    Vector2 v3(0.0f, 1.0f);
    EXPECT_TRUE(v1.Dot(v3) == 0.0f);

    Vector2 v4(-1.0f, 0.0f);
    EXPECT_TRUE(v1.Dot(v4) == -1.0f);
}

TEST(Vector2Test, GetNormalized)
{
    Vector2 v(0.0f, 5.0f);
    Vector2 norm = v.GetNormalized();
    EXPECT_TRUE(v.IsNearlyEqual({ 0.0f, 5.0f }));
    EXPECT_TRUE(norm.IsNearlyEqual({ 0.0f, 1.0f }));
    EXPECT_TRUE(norm.Length() == 1.0f);
}

TEST(Vector2Test, IsNearlyEqual)
{
    Vector2 v(1.0f, 0.0f);
    EXPECT_TRUE(v.IsNearlyEqual({ 1.00001f, 0.0f }));
    EXPECT_FALSE(v.IsNearlyEqual({ 1.0001f, 0.0f }));
    EXPECT_FALSE(v.IsNearlyEqual({ -1.0f, 0.0f }));
}

TEST(Vector2Test, IsNormalized)
{
    Vector2 v(3.0f, 0.0f);
    EXPECT_FALSE(v.IsNormalized());

    v.Normalize();
    EXPECT_TRUE(v.IsNormalized());
}

TEST(Vector2Test, Length)
{
    Vector2 v(3.0f, 4.0f);
    EXPECT_TRUE(v.Length() == 5.0f);
    EXPECT_TRUE(v.LengthSquared() == 25.0f);
}

TEST(Vector2Test, Lerp)
{
    Vector2 start(0.0f, 0.0f);
    Vector2 end(10.0f, 10.0f);

    Vector2 mid = Vector2::Lerp(start, end, 0.5f);
    EXPECT_TRUE(mid.IsNearlyEqual({ 5.0f, 5.0f }));

    Vector2 quarter = Vector2::Lerp(start, end, 0.25f);
    EXPECT_TRUE(quarter.IsNearlyEqual({ 2.5f, 2.5f }));
}

TEST(Vector2Test, LerpExtrapolation)
{
    Vector2 start(0.0f, 0.0f);
    Vector2 end(10.0f, 10.0f);
    Vector2 result = Vector2::Lerp(start, end, 2.0f);
    EXPECT_TRUE(result.IsNearlyEqual({ 20.0f, 20.0f }));
}

TEST(Vector2Test, MultiplicationGlobalScalar)
{
    Vector2 v(2.0f, 4.0f);
    Vector2 result = 2.0f * v;
    EXPECT_TRUE(result.IsNearlyEqual({ 4.0f, 8.0f }));
}

TEST(Vector2Test, MultiplicationScalar)
{
    Vector2 v(2.0f, 4.0f);
    Vector2 result = v * 2.0f;
    EXPECT_TRUE(result.IsNearlyEqual({ 4.0f, 8.0f }));
}

TEST(Vector2Test, Negation)
{
    Vector2 v(1.0f, -2.0f);
    Vector2 result = -v;
    EXPECT_TRUE(result.IsNearlyEqual({ -1.0f, 2.0f }));
}

TEST(Vector2Test, Normalization)
{
    Vector2 v(3.0f, 0.0f);
    v.Normalize();
    EXPECT_TRUE(v.IsNearlyEqual({ 1.0f, 0.0f }));
    EXPECT_TRUE(v.Length() == 1.0f);
}

TEST(Vector2Test, NormalizeZeroVector)
{
    Vector2 v(0.0f, 0.0f);
    v.Normalize();
    EXPECT_TRUE(v.x == 0.0f && v.y == 0.0f);
}

TEST(Vector2Test, Reflect)
{
    Vector2 incoming(1.0f, -1.0f);
    Vector2 normal(0.0f, 1.0f);
    Vector2 result = Vector2::Reflect(incoming, normal);
    EXPECT_TRUE(result.IsNearlyEqual({ 1.0f, 1.0f }));
}

TEST(Vector2Test, ReflectHeadOn)
{
    Vector2 incoming(0.0f, -1.0f);
    Vector2 normal(0.0f, 1.0f);
    Vector2 result = Vector2::Reflect(incoming, normal);
    EXPECT_TRUE(result.IsNearlyEqual({ 0.0f, 1.0f }));
}

TEST(Vector2Test, ReflectParallel)
{
    Vector2 incoming(1.0f, 0.0f);
    Vector2 normal(0.0f, 1.0f);
    Vector2 result = Vector2::Reflect(incoming, normal);
    EXPECT_TRUE(result.IsNearlyEqual({ 1.0f, 0.0f }));
}

TEST(Vector2Test, Rotate)
{
    Vector2 v(1.0f, 0.0f);

    v.Rotate(90.0f);
    EXPECT_TRUE(v.IsNearlyEqual({ 0.0f, 1.0f }));

    v.Rotate(90.0f);
    EXPECT_TRUE(v.IsNearlyEqual({ -1.0f, 0.0f }));
}

TEST(Vector2Test, SignedAngle)
{
    Vector2 a(1.0f, 0.0f);
    Vector2 b(0.0f, 1.0f);
    EXPECT_NEAR(Vector2::SignedAngle(a, b), 90.0f, Vector2::kToleranceEpsilon);
    EXPECT_NEAR(Vector2::SignedAngle(b, a), -90.0f, Vector2::kToleranceEpsilon);
}

TEST(Vector2Test, SubscriptOperator)
{
    Vector2 v(5.0f, 10.0f);
    EXPECT_FLOAT_EQ(v[0], 5.0f);
    EXPECT_FLOAT_EQ(v[1], 10.0f);

    v[0] = 1.0f;
    v[1] = 2.0f;
    EXPECT_TRUE(v.IsNearlyEqual({ 1.0f, 2.0f }));
}

TEST(Vector2Test, Subtraction)
{
    Vector2 v1(5.0f, 6.0f);
    Vector2 v2(2.0f, 3.0f);
    Vector2 result = v1 - v2;
    EXPECT_TRUE(result.IsNearlyEqual({ 3.0f, 3.0f }));
}
