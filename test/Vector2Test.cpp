/// Copyright (c) 2026 Jose Ilitzky

#include <cmath>
#include <gtest/gtest.h>
#include <Vec23/Vector2.h>

namespace Vec23::Test
{
    TEST(Vector2Test, Addition)
    {
        FVector2 v1(1.0f, 2.0f);
        FVector2 v2(3.0f, 4.0f);
        FVector2 result = v1 + v2;
        EXPECT_TRUE(result.IsNearlyEqual({ 4.0f, 6.0f }));
    }

    TEST(Vector2Test, Angle)
    {
        FVector2 a(1.0f, 0.0f);
        FVector2 b(0.0f, -1.0f);
        EXPECT_NEAR(FVector2::Angle(a, b), 90.0f, kToleranceEpsilon<float>);
    }

    TEST(Vector2Test, AngleEdgeCases)
    {
        FVector2 v(1.0f, 0.0f);
        EXPECT_NEAR(FVector2::Angle(v, v), 0.0f, kToleranceEpsilon<float>);
        EXPECT_NEAR(FVector2::Angle(v, -v), 180.0f, kToleranceEpsilon<float>);
    }

    TEST(Vector2Test, ComponentConstructor)
    {
        FVector2 v(2.0f, 3.0f);
        EXPECT_FLOAT_EQ(v.x, 2.0f);
        EXPECT_FLOAT_EQ(v.y, 3.0f);
    }

    TEST(Vector2Test, ComponentMultiplication)
    {
        FVector2 v1(2.0f, 3.0f);
        FVector2 v2(4.0f, 5.0f);
        FVector2 result = v1 * v2;
        EXPECT_TRUE(result.IsNearlyEqual({ 8.0f, 15.0f }));
    }

    TEST(Vector2Test, CompoundAddition)
    {
        FVector2 v1(1.0f, 2.0f);
        FVector2 v2(3.0f, 4.0f);
        v1 += v2;
        EXPECT_TRUE(v1.IsNearlyEqual({ 4.0f, 6.0f }));
    }

    TEST(Vector2Test, CompoundScalarMultiplication)
    {
        FVector2 v(2.0f, 4.0f);
        v *= 0.5f;
        EXPECT_TRUE(v.IsNearlyEqual({ 1.0f, 2.0f }));
    }

    TEST(Vector2Test, CompoundSubtraction)
    {
        FVector2 v1(5.0f, 6.0f);
        FVector2 v2(2.0f, 3.0f);
        v1 -= v2;
        EXPECT_TRUE(v1.IsNearlyEqual({ 3.0f, 3.0f }));
    }

    TEST(Vector2Test, CrossProduct)
    {
        FVector2 right(1.0f, 0.0f);
        FVector2 up(0.0f, 1.0f);
        EXPECT_TRUE(right.Cross(up) == 1.0f);
        EXPECT_TRUE(up.Cross(right) == -1.0f);
    }

    TEST(Vector2Test, DefaultConstructor)
    {
        FVector2 v;
        EXPECT_FLOAT_EQ(v.x, 0.0f);
        EXPECT_FLOAT_EQ(v.y, 0.0f);
    }

    TEST(Vector2Test, Distance)
    {
        FVector2 v1(0.0f, 0.0f);
        FVector2 v2(0.0f, 10.0f);
        EXPECT_TRUE(FVector2::Distance(v1, v2) == 10.0f);
        EXPECT_TRUE(FVector2::DistanceSquared(v1, v2) == 100.0f);
    }

    TEST(Vector2Test, DivisionByZero)
    {
        FVector2 v(10.0f, 10.0f);
        FVector2 result = v / 0.0f;
        EXPECT_TRUE(std::isinf(result.x));
        EXPECT_TRUE(std::isinf(result.y));
    }

    TEST(Vector2Test, DotProduct)
    {
        FVector2 v1(1.0f, 0.0f);
        FVector2 v2(2.0f, 0.0f);
        EXPECT_TRUE(v1.Dot(v2) == 2.0f);

        FVector2 v3(0.0f, 1.0f);
        EXPECT_TRUE(v1.Dot(v3) == 0.0f);

        FVector2 v4(-1.0f, 0.0f);
        EXPECT_TRUE(v1.Dot(v4) == -1.0f);
    }

    TEST(Vector2Test, GetNormalized)
    {
        FVector2 v(0.0f, 5.0f);
        FVector2 norm = v.GetNormalized();
        EXPECT_TRUE(v.IsNearlyEqual({ 0.0f, 5.0f }));
        EXPECT_TRUE(norm.IsNearlyEqual({ 0.0f, 1.0f }));
        EXPECT_TRUE(norm.Length() == 1.0f);
    }

    TEST(Vector2Test, IsNearlyEqual)
    {
        FVector2 v(1.0f, 0.0f);
        EXPECT_TRUE(v.IsNearlyEqual({ 1.00001f, 0.0f }));
        EXPECT_FALSE(v.IsNearlyEqual({ 1.0001f, 0.0f }));
        EXPECT_FALSE(v.IsNearlyEqual({ -1.0f, 0.0f }));
    }

    TEST(Vector2Test, IsNormalized)
    {
        FVector2 v(3.0f, 0.0f);
        EXPECT_FALSE(v.IsNormalized());

        v.Normalize();
        EXPECT_TRUE(v.IsNormalized());
    }

    TEST(Vector2Test, Length)
    {
        FVector2 v(3.0f, 4.0f);
        EXPECT_TRUE(v.Length() == 5.0f);
        EXPECT_TRUE(v.LengthSquared() == 25.0f);
    }

    TEST(Vector2Test, Lerp)
    {
        FVector2 start(0.0f, 0.0f);
        FVector2 end(10.0f, 10.0f);

        FVector2 mid = FVector2::Lerp(start, end, 0.5f);
        EXPECT_TRUE(mid.IsNearlyEqual({ 5.0f, 5.0f }));

        FVector2 quarter = FVector2::Lerp(start, end, 0.25f);
        EXPECT_TRUE(quarter.IsNearlyEqual({ 2.5f, 2.5f }));
    }

    TEST(Vector2Test, LerpExtrapolation)
    {
        FVector2 start(0.0f, 0.0f);
        FVector2 end(10.0f, 10.0f);
        FVector2 result = FVector2::Lerp(start, end, 2.0f);
        EXPECT_TRUE(result.IsNearlyEqual({ 20.0f, 20.0f }));
    }

    TEST(Vector2Test, MultiplicationGlobalScalar)
    {
        FVector2 v(2.0f, 4.0f);
        FVector2 result = 2.0f * v;
        EXPECT_TRUE(result.IsNearlyEqual({ 4.0f, 8.0f }));
    }

    TEST(Vector2Test, MultiplicationScalar)
    {
        FVector2 v(2.0f, 4.0f);
        FVector2 result = v * 2.0f;
        EXPECT_TRUE(result.IsNearlyEqual({ 4.0f, 8.0f }));
    }

    TEST(Vector2Test, Negation)
    {
        FVector2 v(1.0f, -2.0f);
        FVector2 result = -v;
        EXPECT_TRUE(result.IsNearlyEqual({ -1.0f, 2.0f }));
    }

    TEST(Vector2Test, Normalization)
    {
        FVector2 v(3.0f, 0.0f);
        v.Normalize();
        EXPECT_TRUE(v.IsNearlyEqual({ 1.0f, 0.0f }));
        EXPECT_TRUE(v.Length() == 1.0f);
    }

    TEST(Vector2Test, NormalizeZeroVector)
    {
        FVector2 v(0.0f, 0.0f);
        v.Normalize();
        EXPECT_TRUE(v.x == 0.0f && v.y == 0.0f);
    }

    TEST(Vector2Test, Reflect)
    {
        FVector2 incoming(1.0f, -1.0f);
        FVector2 normal(0.0f, 1.0f);
        FVector2 result = FVector2::Reflect(incoming, normal);
        EXPECT_TRUE(result.IsNearlyEqual({ 1.0f, 1.0f }));
    }

    TEST(Vector2Test, ReflectHeadOn)
    {
        FVector2 incoming(0.0f, -1.0f);
        FVector2 normal(0.0f, 1.0f);
        FVector2 result = FVector2::Reflect(incoming, normal);
        EXPECT_TRUE(result.IsNearlyEqual({ 0.0f, 1.0f }));
    }

    TEST(Vector2Test, ReflectParallel)
    {
        FVector2 incoming(1.0f, 0.0f);
        FVector2 normal(0.0f, 1.0f);
        FVector2 result = FVector2::Reflect(incoming, normal);
        EXPECT_TRUE(result.IsNearlyEqual({ 1.0f, 0.0f }));
    }

    TEST(Vector2Test, Rotate)
    {
        FVector2 v(1.0f, 0.0f);

        v.Rotate(90.0f);
        EXPECT_TRUE(v.IsNearlyEqual({ 0.0f, 1.0f }));

        v.Rotate(90.0f);
        EXPECT_TRUE(v.IsNearlyEqual({ -1.0f, 0.0f }));
    }

    TEST(Vector2Test, SignedAngle)
    {
        FVector2 a(1.0f, 0.0f);
        FVector2 b(0.0f, 1.0f);
        EXPECT_NEAR(FVector2::SignedAngle(a, b), 90.0f, kToleranceEpsilon<float>);
        EXPECT_NEAR(FVector2::SignedAngle(b, a), -90.0f, kToleranceEpsilon<float>);
    }

    TEST(Vector2Test, SubscriptOperator)
    {
        FVector2 v(5.0f, 10.0f);
        EXPECT_FLOAT_EQ(v[0], 5.0f);
        EXPECT_FLOAT_EQ(v[1], 10.0f);

        v[0] = 1.0f;
        v[1] = 2.0f;
        EXPECT_TRUE(v.IsNearlyEqual({ 1.0f, 2.0f }));
    }

    TEST(Vector2Test, Subtraction)
    {
        FVector2 v1(5.0f, 6.0f);
        FVector2 v2(2.0f, 3.0f);
        FVector2 result = v1 - v2;
        EXPECT_TRUE(result.IsNearlyEqual({ 3.0f, 3.0f }));
    }

    // -------------------------
    // Static Tests
    // -------------------------

    static constexpr FVector2 kZero = { 0.0f, 0.0f };
    static_assert(kZero.GetNormalized() == kZero);
    static_assert(kZero.LengthSquared() == 0.0f);
    static_assert(kZero.Dot(kZero) == 0.0f);
    static_assert(kZero.Cross(kZero) == 0.0f);
    static_assert(kZero.IsNearlyEqual(kZero));
    static_assert(FVector2::Reflect(kZero, kZero) == kZero);
    static_assert(FVector2::Lerp(kZero, kZero, 0.0f) == kZero);
    static_assert(kZero == kZero);
    static_assert(kZero + kZero == kZero);
    static_assert(kZero - kZero == kZero);
    static_assert(kZero * kZero == kZero);
    static_assert(kZero * 0.0f == kZero);
    static_assert(kZero / 1.0f == kZero);
    static_assert(-kZero == kZero);
    static_assert(kZero[0] == 0.0f);
    static_assert(0.0f * kZero == kZero);
}
