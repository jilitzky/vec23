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

        constexpr Vector2() noexcept : x(kZero<T>), y(kZero<T>) {}

        constexpr Vector2(T x, T y) noexcept : x(x), y(y) {}

        // -------------------------
        // Modifiers
        // -------------------------

        void Normalize() noexcept
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

        void Rotate(T degrees) noexcept
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

        bool IsNormalized() const noexcept
        {
            return std::abs(LengthSquared() - kOne<T>) < kToleranceEpsilon<T>;
        }

        Vector2 GetNormalized() const noexcept
        {
            Vector2 result = *this;
            result.Normalize();
            return result;
        }

        Vector2 GetRotated(T degrees) const noexcept
        {
            Vector2 result = *this;
            result.Rotate(degrees);
            return result;
        }

        T Length() const noexcept
        {
            return std::hypot(x, y);
        }

        constexpr T LengthSquared() const noexcept
        {
            return (x * x) + (y * y);
        }

        constexpr T Dot(const Vector2& other) const noexcept
        {
            return (x * other.x) + (y * other.y);
        }

        constexpr T Cross(const Vector2& other) const noexcept
        {
            return (x * other.y) - (y * other.x);
        }

        bool IsNearlyEqual(const Vector2& other, T epsilon = kToleranceEpsilon<T>) const noexcept
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

        static T Distance(const Vector2& a, const Vector2& b) noexcept
        {
            return (b - a).Length();
        }

        static constexpr T DistanceSquared(const Vector2& a, const Vector2& b) noexcept
        {
            return (b - a).LengthSquared();
        }

        static constexpr Vector2 Reflect(const Vector2& v, const Vector2& n) noexcept
        {
            return v - n * (kTwo<T> * v.Dot(n));
        }

        static constexpr Vector2 Lerp(const Vector2& a, const Vector2& b, T t) noexcept
        {
            return { std::lerp(a.x, b.x, t), std::lerp(a.y, b.y, t) };
        }

        static T Angle(const Vector2& a, const Vector2& b) noexcept
        {
            return std::abs(SignedAngle(a, b));
        }

        static T SignedAngle(const Vector2& a, const Vector2& b) noexcept
        {
            T dot = a.Dot(b);
            T cross = a.Cross(b);
            T radians = std::atan2(cross, dot);
            return radians * kRadiansToDegrees<T>;
        }

        // -------------------------
        // Operators
        // -------------------------

        constexpr bool operator==(const Vector2& other) const noexcept = default;

        constexpr Vector2 operator+(const Vector2& other) const noexcept
        {
            return { x + other.x, y + other.y };
        }

        constexpr Vector2 operator-(const Vector2& other) const noexcept
        {
            return { x - other.x, y - other.y };
        }

        constexpr Vector2 operator*(const Vector2& other) const noexcept
        {
            return { x * other.x, y * other.y };
        }

        constexpr Vector2 operator*(T scalar) const noexcept
        {
            return { x * scalar, y * scalar };
        }

        constexpr Vector2 operator/(T scalar) const noexcept
        {
            return *this * (kOne<T> / scalar);
        }

        constexpr Vector2 operator-() const noexcept
        {
            return { -x, -y };
        }

        constexpr Vector2& operator+=(const Vector2& other) noexcept
        {
            x += other.x;
            y += other.y;
            return *this;
        }

        constexpr Vector2& operator-=(const Vector2& other) noexcept
        {
            x -= other.x;
            y -= other.y;
            return *this;
        }

        constexpr Vector2& operator*=(T scalar) noexcept
        {
            x *= scalar;
            y *= scalar;
            return *this;
        }

        constexpr Vector2& operator/=(T scalar) noexcept
        {
            *this *= kOne<T> / scalar;
            return *this;
        }

        constexpr T& operator[](int index) noexcept
        {
            assert(index >= 0 && index < 2);
            return (&x)[index];
        }

        constexpr const T& operator[](int index) const noexcept
        {
            assert(index >= 0 && index < 2);
            return (&x)[index];
        }

        constexpr friend Vector2 operator*(T scalar, const Vector2& v) noexcept
        {
            return v * scalar;
        }
    };

    using FVector2 = Vector2<float>;
    using DVector2 = Vector2<double>;
    using LDVector2 = Vector2<long double>;
}
