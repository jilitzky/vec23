/// Copyright (c) 2026 Jose Ilitzky

#pragma once

#include <cassert>
#include <cmath>
#include <concepts>
#include <format>
#include <string>
#include "Constants.h"

namespace Vec23
{
    template<std::floating_point T>
    struct Vector3
    {
        T x;
        T y;
        T z;

        constexpr Vector3() : x(kZero<T>), y(kZero<T>), z(kZero<T>) {}

        constexpr Vector3(T x, T y, T z) : x(x), y(y), z(z) {}

        // -------------------------
        // Modifiers
        // -------------------------

        constexpr void Normalize()
        {
            T lengthSq = LengthSquared();
            if (lengthSq > kSafetyEpsilon<T>)
            {
                T invLength = kOne<T> / std::sqrt(lengthSq);
                x *= invLength;
                y *= invLength;
                z *= invLength;
            }
            else
            {
                x = y = z = kZero<T>;
            }
        }

        void Rotate(T degrees, const Vector3& axis)
        {
            T radians = degrees * kDegreesToRadians<T>;
            T cosT = std::cos(radians);
            T sinT = std::sin(radians);

            Vector3 u = axis;
            if (std::abs(u.LengthSquared() - kOne<T>) > kSafetyEpsilon<T>)
            {
                u.Normalize();
            }

            Vector3 v = *this;
            *this = (v * cosT) + (u.Cross(v) * sinT) + (u * u.Dot(v) * (kOne<T> - cosT));
        }

        // -------------------------
        // Core
        // -------------------------

        bool IsNormalized() const
        {
            return std::abs(LengthSquared() - kOne<T>) < kToleranceEpsilon<T>;
        }

        constexpr Vector3 GetNormalized() const
        {
            Vector3 result = *this;
            result.Normalize();
            return result;
        }

        Vector3 GetRotated(T degrees, const Vector3& axis) const
        {
            Vector3 result = *this;
            result.Rotate(degrees, axis);
            return result;
        }

        T Length() const
        {
            return std::hypot(x, y, z);
        }

        constexpr T LengthSquared() const
        {
            return (x * x) + (y * y) + (z * z);
        }

        constexpr T Dot(const Vector3& other) const
        {
            return (x * other.x) + (y * other.y) + (z * other.z);
        }

        constexpr Vector3 Cross(const Vector3& other) const
        {
            return
            {
                (y * other.z) - (z * other.y),
                (z * other.x) - (x * other.z),
                (x * other.y) - (y * other.x)
            };
        }

        constexpr bool IsNearlyEqual(const Vector3& other, T epsilon = kToleranceEpsilon<T>) const
        {
            return DistanceSquared(*this, other) < (epsilon * epsilon);
        }

        std::string ToString() const
        {
            return std::format("({}, {}, {})", x, y, z);
        }

        // -------------------------
        // Utilities
        // -------------------------

        static T Distance(const Vector3& a, const Vector3& b)
        {
            return (b - a).Length();
        }

        static constexpr T DistanceSquared(const Vector3& a, const Vector3& b)
        {
            return (b - a).LengthSquared();
        }

        static constexpr Vector3 Reflect(const Vector3& v, const Vector3& n)
        {
            return v - n * (kTwo<T> * v.Dot(n));
        }

        static constexpr Vector3 Lerp(const Vector3& a, const Vector3& b, T t)
        {
            return { std::lerp(a.x, b.x, t), std::lerp(a.y, b.y, t), std::lerp(a.z, b.z, t) };
        }

        static T Angle(const Vector3& a, const Vector3& b)
        {
            T dot = a.Dot(b);
            Vector3 cross = a.Cross(b);
            T radians = std::atan2(cross.Length(), dot);
            return radians * kRadiansToDegrees<T>;
        }

        static T SignedAngle(const Vector3& a, const Vector3& b, const Vector3& axis)
        {
            Vector3 cross = a.Cross(b);
            T dot = a.Dot(b);
            T radians = std::atan2(cross.Length(), dot);
            T degrees = radians * kRadiansToDegrees<T>;
            T sign = cross.Dot(axis);
            return (sign < kZero<T>) ? -degrees : degrees;
        }

        // -------------------------
        // Operators
        // -------------------------

        constexpr bool operator==(const Vector3& other) const = default;

        constexpr Vector3 operator+(const Vector3& other) const
        {
            return { x + other.x, y + other.y, z + other.z };
        }

        constexpr Vector3 operator-(const Vector3& other) const
        {
            return { x - other.x, y - other.y, z - other.z };
        }

        constexpr Vector3 operator*(const Vector3& other) const
        {
            return { x * other.x, y * other.y, z * other.z };
        }

        constexpr Vector3 operator*(T scalar) const
        {
            return { x * scalar, y * scalar, z * scalar };
        }

        constexpr Vector3 operator/(T scalar) const
        {
            return *this * (kOne<T> / scalar);
        }

        constexpr Vector3 operator-() const
        {
            return { -x, -y, -z };
        }

        constexpr Vector3& operator+=(const Vector3& other)
        {
            x += other.x;
            y += other.y;
            z += other.z;
            return *this;
        }

        constexpr Vector3& operator-=(const Vector3& other)
        {
            x -= other.x;
            y -= other.y;
            z -= other.z;
            return *this;
        }

        constexpr Vector3& operator*=(T scalar)
        {
            x *= scalar;
            y *= scalar;
            z *= scalar;
            return *this;
        }

        constexpr Vector3& operator/=(T scalar)
        {
            *this *= kOne<T> / scalar;
            return *this;
        }

        constexpr T& operator[](int index)
        {
            assert(index >= 0 && index < 3);
            return (&x)[index];
        }

        constexpr const T& operator[](int index) const
        {
            assert(index >= 0 && index < 3);
            return (&x)[index];
        }

        constexpr friend Vector3 operator*(T scalar, const Vector3& v)
        {
            return v * scalar;
        }
    };

    using FVector3 = Vector3<float>;
    using DVector3 = Vector3<double>;
    using LDVector3 = Vector3<long double>;
}
