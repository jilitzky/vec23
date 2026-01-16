/// Copyright (c) 2026 Jose Ilitzky

#include <gtest/gtest.h>
#include "Vector2.h"

using namespace Vec23;

//class Vector2Test : public ::testing::Test
//{
//};

// -----------------------------------------------------------------------------
// 1. Constructor Tests
// -----------------------------------------------------------------------------

TEST(Vector2Test, DefaultConstructor) {
    Vector2 v;
    EXPECT_FLOAT_EQ(v.x, 0.0f);
    EXPECT_FLOAT_EQ(v.y, 0.0f);
}

//TEST(Vector2Test, ScalarConstructor) {
//    Vector2 v(5.0f);
//    EXPECT_FLOAT_EQ(v.x, 5.0f);
//    EXPECT_FLOAT_EQ(v.y, 5.0f);
//}

TEST(Vector2Test, ComponentConstructor) {
    Vector2 v(2.0f, 3.0f);
    EXPECT_FLOAT_EQ(v.x, 2.0f);
    EXPECT_FLOAT_EQ(v.y, 3.0f);
}

// -----------------------------------------------------------------------------
// 2. Operator Tests
// -----------------------------------------------------------------------------

TEST(Vector2Test, Addition) {
    Vector2 v1(1.0f, 2.0f);
    Vector2 v2(3.0f, 4.0f);
    Vector2 result = v1 + v2;

    EXPECT_FLOAT_EQ(result.x, 4.0f);
    EXPECT_FLOAT_EQ(result.y, 6.0f);
}

TEST(Vector2Test, Subtraction) {
    Vector2 v1(5.0f, 6.0f);
    Vector2 v2(2.0f, 3.0f);
    Vector2 result = v1 - v2;

    EXPECT_FLOAT_EQ(result.x, 3.0f);
    EXPECT_FLOAT_EQ(result.y, 3.0f);
}

TEST(Vector2Test, MultiplicationScalar) {
    Vector2 v(2.0f, 4.0f);
    Vector2 result = v * 2.0f;

    EXPECT_FLOAT_EQ(result.x, 4.0f);
    EXPECT_FLOAT_EQ(result.y, 8.0f);
}

//TEST(Vector2Test, MultiplicationGlobalScalar) {
//    Vector2 v(2.0f, 4.0f);
//    // Tests the "float * vector" global operator
//    Vector2 result = 2.0f * v;
//
//    EXPECT_FLOAT_EQ(result.x, 4.0f);
//    EXPECT_FLOAT_EQ(result.y, 8.0f);
//}

TEST(Vector2Test, ComponentMultiplication) {
    Vector2 v1(2.0f, 3.0f);
    Vector2 v2(4.0f, 5.0f);
    Vector2 result = v1 * v2;

    EXPECT_FLOAT_EQ(result.x, 8.0f);
    EXPECT_FLOAT_EQ(result.y, 15.0f);
}

//TEST(Vector2Test, Negation) {
//    Vector2 v(1.0f, -2.0f);
//    Vector2 result = -v;
//
//    EXPECT_FLOAT_EQ(result.x, -1.0f);
//    EXPECT_FLOAT_EQ(result.y, 2.0f);
//}
//
//TEST(Vector2Test, CompoundAddition) {
//    Vector2 v1(1.0f, 2.0f);
//    Vector2 v2(3.0f, 4.0f);
//    v1 += v2;
//
//    EXPECT_FLOAT_EQ(v1.x, 4.0f);
//    EXPECT_FLOAT_EQ(v1.y, 6.0f);
//}
//
//TEST(Vector2Test, SubscriptOperator) {
//    Vector2 v(5.0f, 10.0f);
//    EXPECT_FLOAT_EQ(v[0], 5.0f);
//    EXPECT_FLOAT_EQ(v[1], 10.0f);
//
//    // Test write via subscript
//    v[0] = 7.0f;
//    EXPECT_FLOAT_EQ(v.x, 7.0f);
//}
