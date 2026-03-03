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
    struct TVector2
    {
        T x;
        T y;

        constexpr TVector2() : x(TZero<T>), y(TZero<T>) {}

        constexpr TVector2(T x, T y) : x(x), y(y) {}

        // -------------------------
        // Modifiers
        // -------------------------

        void Normalize()
        {
            T lengthSq = LengthSquared();
            if (lengthSq > kSafetyEpsilon)
            {
                T invLength = TOne<T> / std::sqrt(lengthSq);
                x *= invLength;
                y *= invLength;
            }
            else
            {
                x = y = TZero<T>;
            }
        }

        void Rotate(T degrees)
        {
            T radians = degrees * kDegreesToRadians;
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
            return std::abs(LengthSquared() - TOne<T>) < kToleranceEpsilon;
        }

        TVector2 GetNormalized() const
        {
            TVector2 result = *this;
            result.Normalize();
            return result;
        }

        TVector2 GetRotated(T degrees) const
        {
            TVector2 result = *this;
            result.Rotate(degrees);
            return result;
        }

        T Length() const
        {
            return std::hypot(x, y);
        }

        T LengthSquared() const
        {
            return (x * x) + (y * y);
        }

        T Dot(const TVector2& other) const
        {
            return (x * other.x) + (y * other.y);
        }

        T Cross(const TVector2& other) const
        {
            return (x * other.y) - (y * other.x);
        }

        bool IsNearlyEqual(const TVector2& other, T epsilon = kToleranceEpsilon) const
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

        static T Distance(const TVector2& a, const TVector2& b)
        {
            return (b - a).Length();
        }

        static T DistanceSquared(const TVector2& a, const TVector2& b)
        {
            return (b - a).LengthSquared();
        }

        static TVector2 Reflect(const TVector2& v, const TVector2& n)
        {
            return v - n * (TTwo<T> * v.Dot(n));
        }

        static TVector2 Lerp(const TVector2& a, const TVector2& b, T t)
        {
            return { std::lerp(a.x, b.x, t), std::lerp(a.y, b.y, t) };
        }

        static T Angle(const TVector2& a, const TVector2& b)
        {
            return std::abs(SignedAngle(a, b));
        }

        static T SignedAngle(const TVector2& a, const TVector2& b)
        {
            T dot = a.Dot(b);
            T cross = a.Cross(b);
            T radians = std::atan2(cross, dot);
            return radians * kRadiansToDegrees;
        }

        // -------------------------
        // Operators
        // -------------------------

        bool operator==(const TVector2& other) const = default;

        TVector2 operator+(const TVector2& other) const
        {
            return { x + other.x, y + other.y };
        }

        TVector2 operator-(const TVector2& other) const
        {
            return { x - other.x, y - other.y };
        }

        TVector2 operator*(const TVector2& other) const
        {
            return { x * other.x, y * other.y };
        }

        TVector2 operator*(T scalar) const
        {
            return { x * scalar, y * scalar };
        }

        TVector2 operator/(T scalar) const
        {
            return *this * (TOne<T> / scalar);
        }

        TVector2 operator-() const
        {
            return { -x, -y };
        }

        TVector2& operator+=(const TVector2& other)
        {
            x += other.x;
            y += other.y;
            return *this;
        }

        TVector2& operator-=(const TVector2& other)
        {
            x -= other.x;
            y -= other.y;
            return *this;
        }

        TVector2& operator*=(T scalar)
        {
            x *= scalar;
            y *= scalar;
            return *this;
        }

        TVector2& operator/=(T scalar)
        {
            *this *= TOne<T> / scalar;
            return *this;
        }

        T& operator[](int index)
        {
            assert(index >= 0 && index < 2);
            return (&x)[index];
        }

        const T& operator[](int index) const
        {
            assert(index >= 0 && index < 2);
            return (&x)[index];
        }

        friend TVector2 operator*(T scalar, const TVector2& v)
        {
            return v * scalar;
        }

    private:
        static constexpr T kDegreesToRadians = TDegreesToRadians<T>;
        static constexpr T kRadiansToDegrees = TRadiansToDegrees<T>;
        static constexpr T kToleranceEpsilon = TToleranceEpsilon<T>;
        static constexpr T kSafetyEpsilon = TSafetyEpsilon<T>;
    };

    using Vector2 = TVector2<float>;
    using DVector2 = TVector2<double>;
    using LDVector2 = TVector2<long double>;
}
