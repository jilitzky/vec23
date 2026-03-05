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
    struct Vector2
    {
        T x;
        T y;

        constexpr Vector2() : x(kZero<T>), y(kZero<T>) {}

        constexpr Vector2(T x, T y) : x(x), y(y) {}

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
            }
            else
            {
                x = y = kZero<T>;
            }
        }

        void Rotate(T degrees)
        {
            T radians = degrees * kDegreesToRadians<T>;
            T cosT = std::cos(radians);
            T sinT = std::sin(radians);
            T oldX = x;

            x = (oldX * cosT) - (y * sinT);
            y = (oldX * sinT) + (y * cosT);
        }

        // -------------------------
        // Core
        // -------------------------

        bool IsNormalized() const
        {
            return std::abs(LengthSquared() - kOne<T>) < kToleranceEpsilon<T>;
        }

        constexpr Vector2 GetNormalized() const
        {
            Vector2 result = *this;
            result.Normalize();
            return result;
        }

        Vector2 GetRotated(T degrees) const
        {
            Vector2 result = *this;
            result.Rotate(degrees);
            return result;
        }

        T Length() const
        {
            return std::hypot(x, y);
        }

        constexpr T LengthSquared() const
        {
            return (x * x) + (y * y);
        }

        constexpr T Dot(const Vector2& other) const
        {
            return (x * other.x) + (y * other.y);
        }

        constexpr T Cross(const Vector2& other) const
        {
            return (x * other.y) - (y * other.x);
        }

        constexpr bool IsNearlyEqual(const Vector2& other, T epsilon = kToleranceEpsilon<T>) const
        {
            return DistanceSquared(*this, other) < (epsilon * epsilon);
        }

        std::string ToString() const
        {
            return std::format("({}, {})", x, y);
        }

        // -------------------------
        // Utilities
        // -------------------------

        static T Distance(const Vector2& a, const Vector2& b)
        {
            return (b - a).Length();
        }

        static constexpr T DistanceSquared(const Vector2& a, const Vector2& b)
        {
            return (b - a).LengthSquared();
        }

        static constexpr Vector2 Reflect(const Vector2& v, const Vector2& n)
        {
            return v - n * (kTwo<T> * v.Dot(n));
        }

        static constexpr Vector2 Lerp(const Vector2& a, const Vector2& b, T t)
        {
            return { std::lerp(a.x, b.x, t), std::lerp(a.y, b.y, t) };
        }

        static T Angle(const Vector2& a, const Vector2& b)
        {
            return std::abs(SignedAngle(a, b));
        }

        static T SignedAngle(const Vector2& a, const Vector2& b)
        {
            T dot = a.Dot(b);
            T cross = a.Cross(b);
            T radians = std::atan2(cross, dot);
            return radians * kRadiansToDegrees<T>;
        }

        // -------------------------
        // Operators
        // -------------------------

        constexpr bool operator==(const Vector2& other) const = default;

        constexpr Vector2 operator+(const Vector2& other) const
        {
            return { x + other.x, y + other.y };
        }

        constexpr Vector2 operator-(const Vector2& other) const
        {
            return { x - other.x, y - other.y };
        }

        constexpr Vector2 operator*(const Vector2& other) const
        {
            return { x * other.x, y * other.y };
        }

        constexpr Vector2 operator*(T scalar) const
        {
            return { x * scalar, y * scalar };
        }

        constexpr Vector2 operator/(T scalar) const
        {
            return *this * (kOne<T> / scalar);
        }

        constexpr Vector2 operator-() const
        {
            return { -x, -y };
        }

        constexpr Vector2& operator+=(const Vector2& other)
        {
            x += other.x;
            y += other.y;
            return *this;
        }

        constexpr Vector2& operator-=(const Vector2& other)
        {
            x -= other.x;
            y -= other.y;
            return *this;
        }

        constexpr Vector2& operator*=(T scalar)
        {
            x *= scalar;
            y *= scalar;
            return *this;
        }

        constexpr Vector2& operator/=(T scalar)
        {
            *this *= kOne<T> / scalar;
            return *this;
        }

        constexpr T& operator[](int index)
        {
            assert(index >= 0 && index < 2);
            return (&x)[index];
        }

        constexpr const T& operator[](int index) const
        {
            assert(index >= 0 && index < 2);
            return (&x)[index];
        }

        constexpr friend Vector2 operator*(T scalar, const Vector2& v)
        {
            return v * scalar;
        }
    };

    using FVector2 = Vector2<float>;
    using DVector2 = Vector2<double>;
    using LDVector2 = Vector2<long double>;
}
