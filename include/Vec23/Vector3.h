/// Copyright (c) 2026 Jose Ilitzky

#pragma once

#include <cassert>
#include <cmath>
#include <sstream>
#include <string>
#include "Constants.h"

namespace Vec23
{
    struct Vector3
    {
        float x;
        float y;
        float z;

        Vector3() : x(0.f), y(0.f), z(0.f) {}

        Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

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
                z *= inv;
            }
            else
            {
                x = 0.f;
                y = 0.f;
                z = 0.f;
            }
        }

        void Rotate(float degrees, const Vector3& axis)
        {
            // TODO: Implement this using quaternions
        }

        // -------------------------
        // Core Logic
        // -------------------------

        bool IsNormalized() const
        {
            return (std::abs(LengthSquared() - 1.f) < kToleranceEpsilon);
        }

        Vector3 GetNormalized() const
        {
            Vector3 result = *this;
            result.Normalize();
            return result;
        }

        Vector3 GetRotated(float degrees, const Vector3& axis) const
        {
            Vector3 result = *this;
            result.Rotate(degrees, axis);
            return result;
        }

        float Length() const
        {
            return std::sqrt(LengthSquared());
        }

        float LengthSquared() const
        {
            return (x * x) + (y * y) + (z * z);
        }

        float Dot(const Vector3& other) const
        {
            return (x * other.x) + (y * other.y) + (z * other.z);
        }

        Vector3 Cross(const Vector3& other) const
        {
            Vector3 cross;
            cross.x = (y * other.z) - (z * other.y);
            cross.y = (z * other.x) - (x * other.z);
            cross.z = (x * other.y) - (y * other.x);
            return cross;
        }

        bool IsNearlyEqual(const Vector3& other, float epsilon = kToleranceEpsilon) const
        {
            return DistanceSquared(*this, other) < (epsilon * epsilon);
        }

        std::string ToString() const
        {
            std::stringstream stream;
            stream << "{" << x << ", " << y << ", " << z << "}";
            return stream.str();
        }

        // -------------------------
        // Utilities
        // -------------------------

        static float Distance(const Vector3& a, const Vector3& b)
        {
            return (b - a).Length();
        }

        static float DistanceSquared(const Vector3& a, const Vector3& b)
        {
            return (b - a).LengthSquared();
        }

        static Vector3 Reflect(const Vector3& v, const Vector3& n)
        {
            return v - n * (2.f * v.Dot(n));
        }

        static Vector3 Lerp(const Vector3& a, const Vector3& b, float t)
        {
            return ((1.f - t) * a) + (t * b);
        }

        static float Angle(const Vector3& a, const Vector3& b)
        {
            float dot = a.Dot(b);
            Vector3 cross = a.Cross(b);
            float radians = std::atan2f(cross.Length(), dot);
            return radians * kRadiansToDegrees;
        }

        static float SignedAngle(const Vector3& a, const Vector3& b, const Vector3& axis)
        {
            Vector3 cross = a.Cross(b);
            float dot = a.Dot(b);
            float radians = std::atan2f(cross.Length(), dot);
            float degrees = radians * kRadiansToDegrees;
            float sign = cross.Dot(axis);
            return (sign < 0.f) ? -degrees : degrees;
        }

        // -------------------------
        // Operators
        // -------------------------

        Vector3 operator+(const Vector3& other) const
        {
            return { x + other.x, y + other.y, z + other.z };
        }

        Vector3 operator-(const Vector3& other) const
        {
            return { x - other.x, y - other.y, z - other.z };
        }

        Vector3 operator*(const Vector3& other) const
        {
            return { x * other.x, y * other.y, z * other.z };
        }

        Vector3 operator*(float scalar) const
        {
            return { x * scalar, y * scalar, z * scalar };
        }

        Vector3 operator/(float scalar) const
        {
            return *this * (1.f / scalar);
        }

        Vector3 operator-() const
        {
            return { -x, -y, -z };
        }

        Vector3& operator+=(const Vector3& other)
        {
            x += other.x;
            y += other.y;
            z += other.z;
            return *this;
        }

        Vector3& operator-=(const Vector3& other)
        {
            x -= other.x;
            y -= other.y;
            z -= other.z;
            return *this;
        }

        Vector3& operator*=(float scalar)
        {
            x *= scalar;
            y *= scalar;
            z *= scalar;
            return *this;
        }

        Vector3& operator/=(float scalar)
        {
            *this *= 1.f / scalar;
            return *this;
        }

        bool operator==(const Vector3& other) const
        {
            return x == other.x && y == other.y && z == other.z;
        }

        bool operator!=(const Vector3& other) const
        {
            return !(*this == other);
        }

        float& operator[](int index)
        {
            assert(index >= 0 && index < 3);
            return (&x)[index];
        }

        const float& operator[](int index) const
        {
            assert(index >= 0 && index < 3);
            return (&x)[index];
        }

        friend Vector3 operator*(float scalar, const Vector3& vector)
        {
            return vector * scalar;
        }
    };
}
