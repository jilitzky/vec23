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

        Vector2() : x(0.f), y(0.f) {}

        Vector2(float x, float y) : x(x), y(y) {}

        // -------------------------
        // Modifiers
        // -------------------------

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

        void Rotate(float degrees)
        {
            float radians = degrees * kDegreesToRadians;
            float cosR = std::cos(radians);
            float sinR = std::sin(radians);
            float oldX = x;

            x = (oldX * cosR) - (y * sinR);
            y = (oldX * sinR) + (y * cosR);
        }

        // -------------------------
        // Core Logic
        // -------------------------

        bool IsNormalized() const
        {
            return (std::abs(LengthSquared() - 1.f) < kToleranceEpsilon);
        }

        Vector2 GetNormalized() const
        {
            Vector2 result = *this;
            result.Normalize();
            return result;
        }

        Vector2 GetRotated(float degrees) const
        {
            Vector2 result = *this;
            result.Rotate(degrees);
            return result;
        }

        float Length() const
        {
            return std::sqrt(LengthSquared());
        }

        float LengthSquared() const
        {
            return (x * x) + (y * y);
        }

        float Dot(const Vector2& other) const
        {
            return (x * other.x) + (y * other.y);
        }

        float Cross(const Vector2& other) const
        {
            return (x * other.y) - (y * other.x);
        }

        bool IsNearlyEqual(const Vector2& other, float epsilon = kToleranceEpsilon) const
        {
            return DistanceSquared(*this, other) < (epsilon * epsilon);
        }

        std::string ToString() const
        {
            std::stringstream stream;
            stream << "{" << x << ", " << y << "}";
            return stream.str();
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
            return *this * (1.f / scalar);
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
            *this *= 1.f / scalar;
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

        friend Vector2 operator*(float scalar, const Vector2& vector)
        {
            return vector * scalar;
        }
    };
}
