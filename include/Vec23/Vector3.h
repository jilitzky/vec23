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
    struct TVector3
    {
        static_assert(std::is_floating_point_v<T>, "TVector3 template parameter must be a floating point type");

        static constexpr T ToleranceEpsilon = kToleranceEpsilon<T>;
        static constexpr T SafetyEpsilon = kSafetyEpsilon<T>;

        T x;
        T y;
        T z;

        TVector3() : x(T()), y(T()), z(T()) {}

        TVector3(T x, T y, T z) : x(x), y(y), z(z) {}

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
                z *= inv;
            }
            else
            {
                x = 0.f;
                y = 0.f;
                z = 0.f;
            }
        }

        void Rotate(T degrees, const TVector3& axis)
        {
            T radians = degrees * kDegreesToRadians<T>;
            T cosT = std::cos(radians);
            T sinT = std::sin(radians);

            TVector3 u = axis;
            if (std::abs(u.LengthSquared() - 1.0f) > SafetyEpsilon)
            {
                u.Normalize();
            }

            TVector3 v = *this;
            *this = (v * cosT) + (u.Cross(v) * sinT) + (u * u.Dot(v) * (1.f - cosT));
        }

        // -------------------------
        // Core Logic
        // -------------------------

        bool IsNormalized() const
        {
            return (std::abs(LengthSquared() - 1.f) < ToleranceEpsilon);
        }

        TVector3 GetNormalized() const
        {
            TVector3 result = *this;
            result.Normalize();
            return result;
        }

        TVector3 GetRotated(T degrees, const TVector3& axis) const
        {
            TVector3 result = *this;
            result.Rotate(degrees, axis);
            return result;
        }

        T Length() const
        {
            return std::sqrt(LengthSquared());
        }

        T LengthSquared() const
        {
            return (x * x) + (y * y) + (z * z);
        }

        T Dot(const TVector3& other) const
        {
            return (x * other.x) + (y * other.y) + (z * other.z);
        }

        TVector3 Cross(const TVector3& other) const
        {
            TVector3 cross;
            cross.x = (y * other.z) - (z * other.y);
            cross.y = (z * other.x) - (x * other.z);
            cross.z = (x * other.y) - (y * other.x);
            return cross;
        }

        bool IsNearlyEqual(const TVector3& other, T epsilon = ToleranceEpsilon) const
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

        static T Distance(const TVector3& a, const TVector3& b)
        {
            return (b - a).Length();
        }

        static T DistanceSquared(const TVector3& a, const TVector3& b)
        {
            return (b - a).LengthSquared();
        }

        static TVector3 Reflect(const TVector3& v, const TVector3& n)
        {
            return v - n * (2.f * v.Dot(n));
        }

        static TVector3 Lerp(const TVector3& a, const TVector3& b, T t)
        {
            return ((1.f - t) * a) + (t * b);
        }

        static T Angle(const TVector3& a, const TVector3& b)
        {
            T dot = a.Dot(b);
            TVector3 cross = a.Cross(b);
            T radians = std::atan2f(cross.Length(), dot);
            return radians * kRadiansToDegrees<T>;
        }

        static T SignedAngle(const TVector3& a, const TVector3& b, const TVector3& axis)
        {
            TVector3 cross = a.Cross(b);
            T dot = a.Dot(b);
            T radians = std::atan2f(cross.Length(), dot);
            T degrees = radians * kRadiansToDegrees<T>;
            T sign = cross.Dot(axis);
            return (sign < 0.f) ? -degrees : degrees;
        }

        // -------------------------
        // Operators
        // -------------------------

        TVector3 operator+(const TVector3& other) const
        {
            return { x + other.x, y + other.y, z + other.z };
        }

        TVector3 operator-(const TVector3& other) const
        {
            return { x - other.x, y - other.y, z - other.z };
        }

        TVector3 operator*(const TVector3& other) const
        {
            return { x * other.x, y * other.y, z * other.z };
        }

        TVector3 operator*(T scalar) const
        {
            return { x * scalar, y * scalar, z * scalar };
        }

        TVector3 operator/(T scalar) const
        {
            return *this * (1.f / scalar);
        }

        TVector3 operator-() const
        {
            return { -x, -y, -z };
        }

        TVector3& operator+=(const TVector3& other)
        {
            x += other.x;
            y += other.y;
            z += other.z;
            return *this;
        }

        TVector3& operator-=(const TVector3& other)
        {
            x -= other.x;
            y -= other.y;
            z -= other.z;
            return *this;
        }

        TVector3& operator*=(T scalar)
        {
            x *= scalar;
            y *= scalar;
            z *= scalar;
            return *this;
        }

        TVector3& operator/=(T scalar)
        {
            *this *= 1.f / scalar;
            return *this;
        }

        bool operator==(const TVector3& other) const
        {
            return x == other.x && y == other.y && z == other.z;
        }

        bool operator!=(const TVector3& other) const
        {
            return !(*this == other);
        }

        T& operator[](int index)
        {
            assert(index >= 0 && index < 3);
            return (&x)[index];
        }

        const T& operator[](int index) const
        {
            assert(index >= 0 && index < 3);
            return (&x)[index];
        }

        friend TVector3 operator*(T scalar, const TVector3& vector)
        {
            return vector * scalar;
        }
    };

    using Vector3 = TVector3<float>;
    using DVector3 = TVector3<double>;
    using LDVector3 = TVector3<long double>;
}
