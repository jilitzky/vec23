/// Copyright (c) 2026 Jose Ilitzky

#include <cmath>
#include <gtest/gtest.h>
#include <Vec23/Constants.h>
#include <Vec23/Vector3.h>

using namespace Vec23;

TEST(Vector3Test, Addition)
{
    Vector3 v1(1.f, 2.f, 3.f);
    Vector3 v2(3.f, 4.f, 5.f);
    Vector3 result = v1 + v2;
    EXPECT_TRUE(result.IsNearlyEqual({ 4.f, 6.f, 8.f }));
}

TEST(Vector3Test, Angle)
{
    Vector3 a(1.f, 0.f, 0.f);
    Vector3 b(0.f, -1.f, 0.f);
    EXPECT_NEAR(Vector3::Angle(a, b), 90.f, Vector3::ToleranceEpsilon);
}

TEST(Vector3Test, AngleEdgeCases)
{
    Vector3 v(1.f, 0.f, 0.f);
    EXPECT_NEAR(Vector3::Angle(v, v), 0.f, Vector3::ToleranceEpsilon);
    EXPECT_NEAR(Vector3::Angle(v, -v), 180.f, Vector3::ToleranceEpsilon);
}

TEST(Vector3Test, ComponentConstructor)
{
    Vector3 v(2.f, 3.f, 4.f);
    EXPECT_FLOAT_EQ(v.x, 2.f);
    EXPECT_FLOAT_EQ(v.y, 3.f);
    EXPECT_FLOAT_EQ(v.z, 4.f);
}

TEST(Vector3Test, ComponentMultiplication)
{
    Vector3 v1(2.f, 3.f, 4.f);
    Vector3 v2(4.f, 5.f, 6.f);
    Vector3 result = v1 * v2;
    EXPECT_TRUE(result.IsNearlyEqual({ 8.f, 15.f, 24.f }));
}

TEST(Vector3Test, CompoundAddition)
{
    Vector3 v1(1.f, 2.f, 3.f);
    Vector3 v2(3.f, 4.f, 5.f);
    v1 += v2;
    EXPECT_TRUE(v1.IsNearlyEqual({ 4.f, 6.f, 8.f }));
}

TEST(Vector3Test, CompoundScalarMultiplication)
{
    Vector3 v(2.f, 4.f, 6.f);
    v *= 0.5f;
    EXPECT_TRUE(v.IsNearlyEqual({ 1.f, 2.f, 3.f }));
}

TEST(Vector3Test, CompoundSubtraction)
{
    Vector3 v1(5.f, 6.f, 7.f);
    Vector3 v2(2.f, 3.f, 4.f);
    v1 -= v2;
    EXPECT_TRUE(v1.IsNearlyEqual({ 3.f, 3.f, 3.f }));
}

TEST(Vector3Test, CrossProduct)
{
    Vector3 x(1.f, 0.f, 0.f);
    Vector3 y(0.f, 1.f, 0.f);
    Vector3 z(0.f, 0.f, 1.f);

    EXPECT_TRUE(x.Cross(y) == z);
    EXPECT_TRUE(y.Cross(x) == -z);
    EXPECT_TRUE(x.Cross(z) == -y);
    EXPECT_TRUE(z.Cross(x) == y);
}

TEST(Vector3Test, DefaultConstructor)
{
    Vector3 v;
    EXPECT_FLOAT_EQ(v.x, 0.f);
    EXPECT_FLOAT_EQ(v.y, 0.f);
    EXPECT_FLOAT_EQ(v.z, 0.f);
}

TEST(Vector3Test, Distance)
{
    Vector3 v1(0.f, 0.f, 0.f);
    Vector3 v2(0.f, 10.f, 0.f);
    EXPECT_TRUE(Vector3::Distance(v1, v2) == 10.f);
    EXPECT_TRUE(Vector3::DistanceSquared(v1, v2) == 100.f);
}

TEST(Vector3Test, DivisionByZero)
{
    Vector3 v(10.f, 10.f, 10.f);
    Vector3 result = v / 0.f;
    EXPECT_TRUE(std::isinf(result.x));
    EXPECT_TRUE(std::isinf(result.y));
    EXPECT_TRUE(std::isinf(result.z));
}

TEST(Vector3Test, DotProduct)
{
    Vector3 v1(1.f, 0.f, 0.f);
    Vector3 v2(2.f, 0.f, 0.f);
    EXPECT_TRUE(v1.Dot(v2) == 2.f);

    Vector3 v3(0.f, 1.f, 0.f);
    EXPECT_TRUE(v1.Dot(v3) == 0.f);

    Vector3 v4(-1.f, 0.f, 0.f);
    EXPECT_TRUE(v1.Dot(v4) == -1.f);
}

TEST(Vector3Test, GetNormalized)
{
    Vector3 v(0.f, 5.f, 0.f);
    Vector3 norm = v.GetNormalized();
    EXPECT_TRUE(v.IsNearlyEqual({ 0.f, 5.f, 0.f }));
    EXPECT_TRUE(norm.IsNearlyEqual({ 0.f, 1.f, 0.f }));
    EXPECT_TRUE(norm.Length() == 1.f);
}

TEST(Vector3Test, IsNearlyEqual)
{
    Vector3 v(1.f, 0.f, 0.f);
    EXPECT_TRUE(v.IsNearlyEqual({ 1.00001f, 0.0f, 0.f }));
    EXPECT_FALSE(v.IsNearlyEqual({ 1.0001f, 0.0f, 0.f }));
    EXPECT_FALSE(v.IsNearlyEqual({ -1.0f, 0.0f, 0.f }));
}

TEST(Vector3Test, IsNormalized)
{
    Vector3 v(3.f, 0.f, 0.f);
    EXPECT_FALSE(v.IsNormalized());

    v.Normalize();
    EXPECT_TRUE(v.IsNormalized());
}

TEST(Vector3Test, Length)
{
    Vector3 v(1.f, 1.f, 1.f);
    EXPECT_NEAR(v.Length(), 1.732050f, Vector3::ToleranceEpsilon);
    EXPECT_NEAR(v.LengthSquared(), 3.f, Vector3::ToleranceEpsilon);
}

TEST(Vector3Test, Lerp)
{
    Vector3 start(0.f, 0.f, 0.f);
    Vector3 end(10.f, 10.f, 10.f);

    Vector3 mid = Vector3::Lerp(start, end, 0.5f);
    EXPECT_TRUE(mid.IsNearlyEqual({ 5.f, 5.f, 5.f }));

    Vector3 quarter = Vector3::Lerp(start, end, 0.25f);
    EXPECT_TRUE(quarter.IsNearlyEqual({ 2.5f, 2.5f, 2.5f }));
}

TEST(Vector3Test, LerpExtrapolation)
{
    Vector3 start(0.f, 0.f, 0.f);
    Vector3 end(10.f, 10.f, 10.f);
    Vector3 result = Vector3::Lerp(start, end, 2.f);
    EXPECT_TRUE(result.IsNearlyEqual({ 20.f, 20.f, 20.f }));
}

TEST(Vector3Test, MultiplicationGlobalScalar)
{
    Vector3 v(2.f, 4.f, 6.f);
    Vector3 result = 2.f * v;
    EXPECT_TRUE(result.IsNearlyEqual({ 4.f, 8.f, 12.f }));
}

TEST(Vector3Test, MultiplicationScalar)
{
    Vector3 v(2.f, 4.f, 6.f);
    Vector3 result = v * 2.f;
    EXPECT_TRUE(result.IsNearlyEqual({ 4.f, 8.f, 12.f }));
}

TEST(Vector3Test, Negation)
{
    Vector3 v(1.f, -2.f, 3.f);
    Vector3 result = -v;
    EXPECT_TRUE(result.IsNearlyEqual({ -1.f, 2.f, -3.f }));
}

TEST(Vector3Test, Normalization)
{
    Vector3 v(3.f, 0.f, 0.f);
    v.Normalize();
    EXPECT_TRUE(v.IsNearlyEqual({ 1.f, 0.f, 0.f }));
    EXPECT_TRUE(v.Length() == 1.f);
}

TEST(Vector3Test, NormalizeZeroVector)
{
    Vector3 v(0.f, 0.f, 0.f);
    v.Normalize();
    EXPECT_TRUE(v.x == 0.f && v.y == 0.f && v.z == 0.f);
}

TEST(Vector3Test, Reflect)
{
    Vector3 incoming(1.f, -1.f, 1.f);
    Vector3 normal(0.f, 1.f, 0.f);
    Vector3 result = Vector3::Reflect(incoming, normal);
    EXPECT_TRUE(result.IsNearlyEqual({ 1.f, 1.f, 1.f }));
}

TEST(Vector3Test, ReflectHeadOn)
{
    Vector3 incoming(0.f, -1.f, 0.f);
    Vector3 normal(0.f, 1.f, 0.f);
    Vector3 result = Vector3::Reflect(incoming, normal);
    EXPECT_TRUE(result.IsNearlyEqual({ 0.f, 1.f, 0.f }));
}

TEST(Vector3Test, ReflectParallel)
{
    Vector3 incoming(1.f, 0.f, 0.f);
    Vector3 normal(0.f, 1.f, 0.f);
    Vector3 result = Vector3::Reflect(incoming, normal);
    EXPECT_TRUE(result.IsNearlyEqual({ 1.f, 0.f, 0.f }));
}

TEST(Vector3Test, Rotate)
{
    Vector3 r(1.f, 2.f, 0.f);
    Vector3 up(0.f, 1.f, 0.f);
    r.Rotate(90.f, up);
    EXPECT_TRUE(r.IsNearlyEqual({ 0.f, 2.f, -1.f }));
}

TEST(Vector3Test, RotateNegation)
{
    Vector3 up(0.f, 1.f, 0.f);
    Vector3 v1(1.f, 0.f, 0.f);
    Vector3 v2 = v1;
    v1.Rotate(-90.f, up);
    v2.Rotate(90.f, -up);
    EXPECT_TRUE(v1.IsNearlyEqual(v2));
}

TEST(Vector3Test, RotateOneEighty)
{
    Vector3 right(1.f, 0.f, 0.f);
    Vector3 flipped = right;
    Vector3 up(0.f, 1.f, 0.f);
    flipped.Rotate(180.f, up);
    EXPECT_TRUE(flipped.IsNearlyEqual(-right));
}

TEST(Vector3Test, RotateSpinInPlace)
{
    Vector3 v(0.f, 5.f, 0.f);
    Vector3 up(0.f, 1.f, 0.f);
    v.Rotate(45.f, up);
    EXPECT_TRUE(v.IsNearlyEqual({ 0.f, 5.f, 0.f }));
}

TEST(Vector3Test, SignedAngle)
{
    Vector3 a(1.f, 0.f, 0.f);
    Vector3 b(0.f, 0.f, 1.f);
    Vector3 up(0.f, 1.f, 0.f);
    EXPECT_NEAR(Vector3::SignedAngle(a, b, up), -90.f, Vector3::ToleranceEpsilon);
    EXPECT_NEAR(Vector3::SignedAngle(b, a, up), 90.f, Vector3::ToleranceEpsilon);
}

TEST(Vector3Test, SubscriptOperator)
{
    Vector3 v(5.f, 10.f, 15.f);
    EXPECT_FLOAT_EQ(v[0], 5.f);
    EXPECT_FLOAT_EQ(v[1], 10.f);
    EXPECT_FLOAT_EQ(v[2], 15.f);

    v[0] = 1.f;
    v[1] = 2.f;
    v[2] = 3.f;
    EXPECT_TRUE(v.IsNearlyEqual({ 1.f, 2.f, 3.f }));
}

TEST(Vector3Test, Subtraction)
{
    Vector3 v1(5.f, 6.f, 7.f);
    Vector3 v2(2.f, 3.f, 4.f);
    Vector3 result = v1 - v2;
    EXPECT_TRUE(result.IsNearlyEqual({ 3.f, 3.f, 3.f }));
}
