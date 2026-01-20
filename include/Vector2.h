/// Copyright (c) 2026 Jose Ilitzky

#pragma once

#include <cassert>
#include <cmath>
#include <sstream>
#include <string>
#include "Constants.h"

namespace Vec23
{
    struct Vector2
    {
        float x;
        float y;

        // -------------------------
        // Constructors
        // -------------------------

        Vector2() : x(0.f), y(0.f) {}

        Vector2(float scalar) : x(scalar), y(scalar) {}

        Vector2(float x, float y) : x(x), y(y) {}

        // -------------------------
        // Operators
        // -------------------------

        Vector2 operator+(const Vector2& other) const
        {
            return { x + other.x, y + other.y };
        }

        Vector2 operator-(const Vector2& other) const
        {
            return { x - other.x, y - other.y };
        }

        Vector2 operator*(const Vector2& other) const
        {
            return { x * other.x, y * other.y };
        }

        Vector2 operator*(float scalar) const
        {
            return { x * scalar, y * scalar };
        }

        Vector2 operator/(float scalar) const
        {
            float inv = 1.f / scalar;
            return { x * inv, y * inv };
        }

        Vector2 operator-() const
        {
            return { -x, -y };
        }

        Vector2& operator+=(const Vector2& other)
        {
            x += other.x;
            y += other.y;
            return *this;
        }

        Vector2& operator-=(const Vector2& other)
        {
            x -= other.x;
            y -= other.y;
            return *this;
        }

        Vector2& operator*=(float scalar)
        {
            x *= scalar;
            y *= scalar;
            return *this;
        }

        Vector2& operator/=(float scalar)
        {
            float inv = 1.f / scalar;
            x *= inv;
            y *= inv;
            return *this;
        }

        bool operator==(const Vector2& other) const
        {
            return x == other.x && y == other.y;
        }

        bool operator!=(const Vector2& other) const
        {
            return !(*this == other);
        }

        float& operator[](int index)
        {
            assert(index >= 0 && index < 2);
            return (&x)[index];
        }

        const float& operator[](int index) const
        {
            assert(index >= 0 && index < 2);
            return (&x)[index];
        }

        // -------------------------
        // Methods
        // -------------------------

        float Dot(const Vector2& other) const
        {
            return (x * other.x) + (y * other.y);
        }

        float Cross(const Vector2& other) const
        {
            return (x * other.y) - (y * other.x);
        }

        float Length() const
        {
            return std::sqrt(LengthSquared());
        }

        float LengthSquared() const
        {
            return (x * x) + (y * y);
        }

        void Normalize()
        {
            float lengthSq = LengthSquared();
            if (lengthSq > kSafetyEpsilon)
            {
                float inv = 1.f / std::sqrt(lengthSq);
                x *= inv;
                y *= inv;
            }
            else
            {
                x = 0.f;
                y = 0.f;
            }
        }

        Vector2 GetNormalized() const
        {
            float lengthSq = LengthSquared();
            if (lengthSq > kSafetyEpsilon)
            {
                float inv = 1.f / std::sqrt(lengthSq);
                return { x * inv, y * inv };
            }
            return { 0.f, 0.f };
        }

        bool IsNormalized() const
        {
            return (std::abs(LengthSquared() - 1.f) < kToleranceEpsilon);
        }

        bool IsNearlyEqual(const Vector2& other, float epsilon = kToleranceEpsilon) const
        {
            return DistanceSquared(*this, other) < (epsilon * epsilon);
        }

        void Rotate(float degrees)
        {
            float radians = degrees * kDegreesToRadians;
            float cosR = std::cos(radians);
            float sinR = std::sin(radians);
            float px = x;

            x = (px * cosR) - (y * sinR);
            y = (px * sinR) + (y * cosR);
        }

        // -------------------------
        // Utilities
        // -------------------------

        static float Distance(const Vector2& a, const Vector2& b)
        {
            return (b - a).Length();
        }

        static float DistanceSquared(const Vector2& a, const Vector2& b)
        {
            return (b - a).LengthSquared();
        }

        static Vector2 Reflect(const Vector2& v, const Vector2& n)
        {
            return v - n * (2.f * v.Dot(n));
        }

        static Vector2 Lerp(const Vector2& a, const Vector2& b, float t)
        {
            return ((1.f - t) * a) + (t * b);
        }

        static float Angle(const Vector2& a, const Vector2& b)
        {
            return std::abs(SignedAngle(a, b));
        }

        static float SignedAngle(const Vector2& a, const Vector2& b)
        {
            float dot = a.Dot(b);
            float cross = a.Cross(b);
            float radians = std::atan2f(cross, dot);
            return radians * kRadiansToDegrees;
        }

        std::string ToString() const
        {
            std::stringstream stream;
            stream << "{" << x << ", " << y << "}";
            return stream.str();
        }

        // -------------------------
        // Global Operators
        // -------------------------

        friend Vector2 operator*(float scalar, const Vector2& vector)
        {
            return vector * scalar;
        }
    };
}
