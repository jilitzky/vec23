/// Copyright (c) 2026 Jose Ilitzky

#include <gtest/gtest.h>
#include <Vec23/Constants.h>
#include <Vec23/Vector2.h>

using namespace Vec23;

// -------------------------
// Constructor Tests
// -------------------------

TEST(Vector2Test, DefaultConstructor)
{
    Vector2 v;
    EXPECT_TRUE(v.x == 0.f && v.y == 0.f);
}

TEST(Vector2Test, ScalarConstructor)
{
    Vector2 v(5.f);
    EXPECT_TRUE(v.x == 5.f && v.y == 5.f);
}

TEST(Vector2Test, ComponentConstructor)
{
    Vector2 v(2.f, 3.f);
    EXPECT_TRUE(v.x == 2.f && v.y == 3.f);
}

// -------------------------
// Operator Tests
// -------------------------

TEST(Vector2Test, Addition)
{
    Vector2 v1(1.f, 2.f);
    Vector2 v2(3.f, 4.f);
    Vector2 result = v1 + v2;
    EXPECT_TRUE(result.IsNearlyEqual(4.f, 6.f));
}

TEST(Vector2Test, Subtraction)
{
    Vector2 v1(5.f, 6.f);
    Vector2 v2(2.f, 3.f);
    Vector2 result = v1 - v2;
    EXPECT_TRUE(result.IsNearlyEqual(3.f, 3.f));
}

TEST(Vector2Test, MultiplicationScalar)
{
    Vector2 v(2.f, 4.f);
    Vector2 result = v * 2.0f;
    EXPECT_TRUE(result.IsNearlyEqual(4.f, 8.f));
}

TEST(Vector2Test, ComponentMultiplication)
{
    Vector2 v1(2.f, 3.f);
    Vector2 v2(4.f, 5.f);
    Vector2 result = v1 * v2;
    EXPECT_TRUE(result.IsNearlyEqual(8.f, 15.f));
}

TEST(Vector2Test, Negation)
{
    Vector2 v(1.f, -2.f);
    Vector2 result = -v;
    EXPECT_TRUE(result.IsNearlyEqual(-1.f, 2.f));
}

TEST(Vector2Test, CompoundAddition)
{
    Vector2 v1(1.f, 2.f);
    Vector2 v2(3.f, 4.f);
    v1 += v2;
    EXPECT_TRUE(v1.IsNearlyEqual(4.f, 6.f));
}

TEST(Vector2Test, CompoundSubtraction)
{
    Vector2 v1(5.f, 6.f);
    Vector2 v2(2.f, 3.f);
    v1 -= v2;
    EXPECT_TRUE(v1.IsNearlyEqual(3.f, 3.f));
}

TEST(Vector2Test, CompoundScalarMultiplication)
{
    Vector2 v(2.f, 4.f);
    v *= 0.5f;
    EXPECT_TRUE(v.IsNearlyEqual(1.f, 2.f));
}

TEST(Vector2Test, SubscriptOperator)
{
    Vector2 v(5.f, 10.f);
    EXPECT_FLOAT_EQ(v[0], 5.f);
    EXPECT_FLOAT_EQ(v[1], 10.f);

    v[0] = 7.f;
    EXPECT_FLOAT_EQ(v.x, 7.f);
}

// -------------------------
// Method Tests
// -------------------------

TEST(Vector2Test, DotProduct)
{
    Vector2 v1(1.0f, 0.0f);
    Vector2 v2(2.0f, 0.0f);
    EXPECT_FLOAT_EQ(v1.Dot(v2), 2.0f);

    Vector2 v3(0.0f, 1.0f);
    EXPECT_FLOAT_EQ(v1.Dot(v3), 0.0f);

    Vector2 v4(-1.0f, 0.0f);
    EXPECT_FLOAT_EQ(v1.Dot(v4), -1.0f);
}

TEST(Vector2Test, CrossProduct)
{
    Vector2 right(1.0f, 0.0f);
    Vector2 up(0.0f, 1.0f);

    EXPECT_FLOAT_EQ(right.Cross(up), 1.0f);
    EXPECT_FLOAT_EQ(up.Cross(right), -1.0f);
}

TEST(Vector2Test, Length)
{
    Vector2 v(3.0f, 4.0f);
    EXPECT_FLOAT_EQ(v.Length(), 5.0f);
    EXPECT_FLOAT_EQ(v.LengthSquared(), 25.0f);
}

TEST(Vector2Test, Normalization)
{
    Vector2 v(3.0f, 0.0f);
    v.Normalize();

    EXPECT_FLOAT_EQ(v.x, 1.0f);
    EXPECT_FLOAT_EQ(v.y, 0.0f);
    EXPECT_FLOAT_EQ(v.Length(), 1.0f);
}

TEST(Vector2Test, GetNormalized)
{
    Vector2 v(0.0f, 5.0f);
    Vector2 norm = v.GetNormalized();

    EXPECT_FLOAT_EQ(v.y, 5.0f);
    EXPECT_FLOAT_EQ(norm.y, 1.0f);
    EXPECT_FLOAT_EQ(norm.Length(), 1.0f);
}

TEST(Vector2Test, IsNormalized)
{
    Vector2 v(3.0f, 0.0f);
    EXPECT_FALSE(v.IsNormalized());

    v.Normalize();
    EXPECT_TRUE(v.IsNormalized());

    Vector2 nearZero(0.0000001f, 0.0000001f);
    EXPECT_FALSE(nearZero.IsNormalized());
}

TEST(Vector2Test, IsNearlyEqual)
{
    Vector2 a(1.0f, 0.0f);

    Vector2 b(1.00001f, 0.0f);
    EXPECT_TRUE(a.IsNearlyEqual(b));
    
    Vector2 c(1.0001f, 0.0f);
    EXPECT_FALSE(a.IsNearlyEqual(c));
    
    Vector2 d(-1.0f, 0.0f);
    EXPECT_FALSE(a.IsNearlyEqual(d));
}

TEST(Vector2Test, Rotate)
{
    Vector2 v(1.0f, 0.0f);

    v.Rotate(90.0f);
    EXPECT_NEAR(v.x, 0.0f, kToleranceEpsilon);
    EXPECT_NEAR(v.y, 1.0f, kToleranceEpsilon);

    v.Rotate(90.0f);
    EXPECT_NEAR(v.x, -1.0f, kToleranceEpsilon);
    EXPECT_NEAR(v.y, 0.0f, kToleranceEpsilon);
}

// -------------------------
// Utility Tests
// -------------------------

TEST(Vector2Test, Distance)
{
    Vector2 v1(0.0f, 0.0f);
    Vector2 v2(0.0f, 10.0f);

    EXPECT_FLOAT_EQ(Vector2::Distance(v1, v2), 10.0f);
    EXPECT_FLOAT_EQ(Vector2::DistanceSquared(v1, v2), 100.0f);
}

TEST(Vector2Test, Reflect)
{
    Vector2 incoming(1.0f, -1.0f);
    Vector2 normal(0.0f, 1.0f);

    Vector2 result = Vector2::Reflect(incoming, normal);
    EXPECT_NEAR(result.x, 1.0f, 0.0001f);
    EXPECT_NEAR(result.y, 1.0f, 0.0001f);
}

TEST(Vector2Test, Lerp)
{
    Vector2 start(0.0f, 0.0f);
    Vector2 end(10.0f, 10.0f);

    Vector2 mid = Vector2::Lerp(start, end, 0.5f);
    EXPECT_FLOAT_EQ(mid.x, 5.0f);
    EXPECT_FLOAT_EQ(mid.y, 5.0f);

    Vector2 quarter = Vector2::Lerp(start, end, 0.25f);
    EXPECT_FLOAT_EQ(quarter.x, 2.5f);
    EXPECT_FLOAT_EQ(quarter.y, 2.5f);
}

TEST(Vector2Test, SignedAngle)
{
    Vector2 a(1.0f, 0.0f);
    Vector2 b(0.0f, 1.0f);

    EXPECT_NEAR(Vector2::SignedAngle(a, b), 90.0f, kToleranceEpsilon);
    EXPECT_NEAR(Vector2::SignedAngle(b, a), -90.0f, kToleranceEpsilon);
}

TEST(Vector2Test, Angle)
{
    Vector2 a(1.0f, 0.0f);
    Vector2 b(0.0f, -1.0f);

    EXPECT_NEAR(Vector2::Angle(a, b), 90.0f, kToleranceEpsilon);
}

// -------------------------
// Global Operator Tests
// -------------------------

TEST(Vector2Test, MultiplicationGlobalScalar)
{
    Vector2 v(2.0f, 4.0f);

    Vector2 result = 2.0f * v;
    EXPECT_FLOAT_EQ(result.x, 4.0f);
    EXPECT_FLOAT_EQ(result.y, 8.0f);
}
