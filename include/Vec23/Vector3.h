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
    struct TVector3
    {
        T x;
        T y;
        T z;

        constexpr TVector3() : x(TZero<T>), y(TZero<T>), z(TZero<T>) {}

        constexpr TVector3(T x, T y, T z) : x(x), y(y), z(z) {}

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
                z *= invLength;
            }
            else
            {
                x = y = z = TZero<T>;
            }
        }

        void Rotate(T degrees, const TVector3& axis)
        {
            T radians = degrees * kDegreesToRadians;
            T cosT = std::cos(radians);
            T sinT = std::sin(radians);

            TVector3 u = axis;
            if (std::abs(u.LengthSquared() - TOne<T>) > kSafetyEpsilon)
            {
                u.Normalize();
            }

            TVector3 v = *this;
            *this = (v * cosT) + (u.Cross(v) * sinT) + (u * u.Dot(v) * (TOne<T> - cosT));
        }

        // -------------------------
        // Core
        // -------------------------

        bool IsNormalized() const
        {
            return std::abs(LengthSquared() - TOne<T>) < kToleranceEpsilon;
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
            return std::hypot(x, y, z);
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
            return
            {
                (y * other.z) - (z * other.y),
                (z * other.x) - (x * other.z),
                (x * other.y) - (y * other.x)
            };
        }

        bool IsNearlyEqual(const TVector3& other, T epsilon = kToleranceEpsilon) const
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
            return v - n * (TTwo<T> * v.Dot(n));
        }

        static TVector3 Lerp(const TVector3& a, const TVector3& b, T t)
        {
            return { std::lerp(a.x, b.x, t), std::lerp(a.y, b.y, t), std::lerp(a.z, b.z, t) };
        }

        static T Angle(const TVector3& a, const TVector3& b)
        {
            T dot = a.Dot(b);
            TVector3 cross = a.Cross(b);
            T radians = std::atan2(cross.Length(), dot);
            return radians * kRadiansToDegrees;
        }

        static T SignedAngle(const TVector3& a, const TVector3& b, const TVector3& axis)
        {
            TVector3 cross = a.Cross(b);
            T dot = a.Dot(b);
            T radians = std::atan2(cross.Length(), dot);
            T degrees = radians * kRadiansToDegrees;
            T sign = cross.Dot(axis);
            return (sign < TZero<T>) ? -degrees : degrees;
        }

        // -------------------------
        // Operators
        // -------------------------

        bool operator==(const TVector3& other) const = default;

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
            return *this * (TOne<T> / scalar);
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
            *this *= TOne<T> / scalar;
            return *this;
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

        friend TVector3 operator*(T scalar, const TVector3& v)
        {
            return v * scalar;
        }

    private:
        static constexpr T kDegreesToRadians = TDegreesToRadians<T>;
        static constexpr T kRadiansToDegrees = TRadiansToDegrees<T>;
        static constexpr T kToleranceEpsilon = TToleranceEpsilon<T>;
        static constexpr T kSafetyEpsilon = TSafetyEpsilon<T>;
    };

    using Vector3 = TVector3<float>;
    using DVector3 = TVector3<double>;
    using LDVector3 = TVector3<long double>;
}
