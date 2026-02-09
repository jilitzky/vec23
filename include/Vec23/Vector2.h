/// Copyright (c) 2026 Jose Ilitzky

#pragma once

#include <cassert>
#include <cmath>
#include <sstream>
#include <string>
#include "Constants.h"

namespace Vec23
{
    template<typename T>
    struct TVector2
    {
        static_assert(std::is_floating_point_v<T>, "TVector2 template parameter must be a floating point type");

        static constexpr T Zero = kZero<T>;
        static constexpr T ToleranceEpsilon = kToleranceEpsilon<T>;
        static constexpr T SafetyEpsilon = kSafetyEpsilon<T>;

        T x;
        T y;

        constexpr TVector2() noexcept : x(Zero), y(Zero) {}

        constexpr TVector2(T x, T y) noexcept : x(x), y(y) {}

        // -------------------------
        // Modifiers
        // -------------------------

        void Normalize()
        {
            T lengthSq = LengthSquared();
            if (lengthSq > SafetyEpsilon)
            {
                T inv = 1.f / std::sqrt(lengthSq);
                x *= inv;
                y *= inv;
            }
            else
            {
                x = 0.f;
                y = 0.f;
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
        // Core Logic
        // -------------------------

        bool IsNormalized() const
        {
            return (std::abs(LengthSquared() - 1.f) < ToleranceEpsilon);
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
            return std::sqrt(LengthSquared());
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

        bool IsNearlyEqual(const TVector2& other, T epsilon = kToleranceEpsilon<T>) const
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
            return v - n * (2.f * v.Dot(n));
        }

        static TVector2 Lerp(const TVector2& a, const TVector2& b, T t)
        {
            return ((1.f - t) * a) + (t * b);
        }

        static T Angle(const TVector2& a, const TVector2& b)
        {
            return std::abs(SignedAngle(a, b));
        }

        static T SignedAngle(const TVector2& a, const TVector2& b)
        {
            T dot = a.Dot(b);
            T cross = a.Cross(b);
            T radians = std::atan2f(cross, dot);
            return radians * kRadiansToDegrees<T>;
        }

        // -------------------------
        // Operators
        // -------------------------

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
            return *this * (1.f / scalar);
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
            *this *= 1.f / scalar;
            return *this;
        }

        bool operator==(const TVector2& other) const
        {
            return x == other.x && y == other.y;
        }

        bool operator!=(const TVector2& other) const
        {
            return !(*this == other);
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

        friend TVector2 operator*(T scalar, const TVector2& vector)
        {
            return vector * scalar;
        }
    };

    using Vector2 = TVector2<float>;
    using DVector2 = TVector2<double>;
    using LDVector2 = TVector2<long double>;
}
