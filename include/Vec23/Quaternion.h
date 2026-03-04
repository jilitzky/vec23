/// Copyright (c) 2026 Jose Ilitzky

#pragma once

#include <algorithm>
#include <concepts>
#include <format>
#include "Constants.h"
#include "Vector3.h"

namespace Vec23
{
    template<std::floating_point T>
    struct Quaternion
    {
        T w;
        T x;
        T y;
        T z;

        constexpr Quaternion() : w(kOne<T>), x(kZero<T>), y(kZero<T>), z(kZero<T>) {}

        constexpr Quaternion(T w, T x, T y, T z) : w(w), x(x), y(y), z(z) {}

        static constexpr Quaternion Identity()
        {
            return Quaternion();
        }
        
        static constexpr Quaternion FromAxisAngle(const Vector3<T>& axis, T degrees)
        {
            T halfRadians = degrees * kHalf<T> * kDegreesToRadians<T>;
            T cosT = std::cos(halfRadians);
            T sinT = std::sin(halfRadians);

            Vector3 u = axis;
            T lengthSq = u.LengthSquared();

            if (lengthSq < kSafetyEpsilon<T>)
            {
                return Identity();
            }

            if (std::abs(lengthSq - kOne<T>) > kSafetyEpsilon<T>)
            {
                u.Normalize();
            }

            return { cosT, u.x * sinT, u.y * sinT, u.z * sinT };
        }

        static constexpr Quaternion FromEuler(T rollDegrees, T pitchDegrees, T yawDegrees)
        {
            T halfRollRadians = rollDegrees * kHalf<T> * kDegreesToRadians<T>;
            T cosRoll = std::cos(halfRollRadians);
            T sinRoll = std::sin(halfRollRadians);

            T halfPitchRadians = pitchDegrees * kHalf<T> * kDegreesToRadians<T>;
            T cosPitch = std::cos(halfPitchRadians);
            T sinPitch = std::sin(halfPitchRadians);

            T halfYawRadians = yawDegrees * kHalf<T> * kDegreesToRadians<T>;
            T cosYaw = std::cos(halfYawRadians);
            T sinYaw = std::sin(halfYawRadians);

            return Quaternion(
                cosRoll * cosPitch * cosYaw + sinRoll * sinPitch * sinYaw,
                sinRoll * cosPitch * cosYaw - cosRoll * sinPitch * sinYaw,
                cosRoll * sinPitch * cosYaw + sinRoll * cosPitch * sinYaw,
                cosRoll * cosPitch * sinYaw - sinRoll * sinPitch * cosYaw
            );
        }

        // -------------------------
        // Modifiers
        // -------------------------

        constexpr void Normalize()
        {
            T lengthSq = LengthSquared();
            if (lengthSq > kSafetyEpsilon<T>)
            {
                T invLength = kOne<T> / std::sqrt(lengthSq);
                w *= invLength;
                x *= invLength;
                y *= invLength;
                z *= invLength;
            }
            else
            {
                *this = Identity();
            }
        }

        constexpr void Conjugate()
        {
            x = -x;
            y = -y;
            z = -z;
        }

        constexpr void Inverse()
        {
            T lengthSq = LengthSquared();
            if (lengthSq > kSafetyEpsilon<T>)
            {
                T invLengthSq = kOne<T> / lengthSq;
                w *= invLengthSq;
                x *= -invLengthSq;
                y *= -invLengthSq;
                z *= -invLengthSq;
            }
            else
            {
                *this = Identity();
            }
        }

        // -------------------------
        // Core
        // -------------------------

        constexpr bool IsNormalized() const
        {
            return std::abs(LengthSquared() - kOne<T>) < kToleranceEpsilon<T>;
        }

        constexpr T Length() const
        {
            return std::sqrt(LengthSquared());
        }

        constexpr T LengthSquared() const
        {
            return (w * w) + (x * x) + (y * y) + (z * z);
        }

        constexpr T Dot(const Quaternion& other) const
        {
            return (w * other.w) + (x * other.x) + (y * other.y) + (z * other.z);
        }

        constexpr Quaternion GetNormalized() const
        {
            Quaternion result = *this;
            result.Normalize();
            return result;
        }

        constexpr Quaternion GetConjugated() const
        {
            Quaternion result = *this;
            result.Conjugate();
            return result;
        }

        constexpr Quaternion GetInversed() const
        {
            Quaternion result = *this;
            result.Inverse();
            return result;
        }

        constexpr Vector3<T> RotateVector(const Vector3<T>& v) const
        {
            T tempX = kTwo<T> * (y * v.z - z * v.y);
            T tempY = kTwo<T> * (z * v.x - x * v.z);
            T tempZ = kTwo<T> * (x * v.y - y * v.x);

            return Vector3<T>(
                v.x + w * tempX + (y * tempZ - z * tempY),
                v.y + w * tempY + (z * tempX - x * tempZ),
                v.z + w * tempZ + (x * tempY - y * tempX)
            );
        }

        constexpr Vector3<T> ToEuler() const
        {
            Vector3<T> euler;

            T gimbalTest = w * y - x * z;
            if (gimbalTest > kHalf<T> - kToleranceEpsilon<T>)
            {
                euler.x = kZero<T>;
                euler.y = kPi<T> * kHalf<T>;
                euler.z = kTwo<T> * std::atan2(z, w);
            }
            else if (gimbalTest < kToleranceEpsilon<T> - kHalf<T>)
            {
                euler.x = kZero<T>;
                euler.y = -kPi<T> * kHalf<T>;
                euler.z = kTwo<T> * std::atan2(x, w);
            }
            else
            {
                T wSq = w * w;
                T xSq = x * x;
                T ySq = y * y;
                T zSq = z * z;

                euler.x = std::atan2(kTwo<T> * (w * x + y * z), wSq - xSq - ySq + zSq);
                euler.y = std::asin(-kTwo<T> * (x * z - w * y));
                euler.z = std::atan2(kTwo<T> * (x * y + w * z), wSq + xSq - ySq - zSq);
            }

            return euler * kRadiansToDegrees<T>;
        }

        constexpr void ToAxisAngle(Vector3<T>& outAxis, T& outDegrees) const
        {
            T clampedW = std::clamp(w, -kOne<T>, kOne<T>);
            T sinSqT = kOne<T> - (clampedW * clampedW);
            if (sinSqT < kSafetyEpsilon<T>)
            {
                outAxis = { kOne<T>, kZero<T>, kZero<T> };
                outDegrees = kZero<T>;
            }
            else
            {
                T invSinT = kOne<T> / std::sqrt(sinSqT);
                outAxis.x = x * invSinT;
                outAxis.y = y * invSinT;
                outAxis.z = z * invSinT;
                outDegrees = std::acos(clampedW) * kTwo<T> * kRadiansToDegrees<T>;
            }
        }

        constexpr bool IsNearlyEqual(const Quaternion& other, T epsilon = kSafetyEpsilon<T>) const
        {
            T lenSqA = LengthSquared();
            T lenSqB = other.LengthSquared();
            if (lenSqA < kSafetyEpsilon<T> || lenSqB < kSafetyEpsilon<T>)
            {
                return lenSqA < kSafetyEpsilon<T> && lenSqB < kSafetyEpsilon<T>;
            }

            T dot = Dot(other);
            return std::abs(dot * dot - lenSqA * lenSqB) <= epsilon;
        }

        std::string ToString() const
        {
            return std::format("({}, {}, {}, {})", w, x, y, z);
        }

        // -------------------------
        // Utilities
        // -------------------------

        static constexpr Quaternion Lerp(const Quaternion& a, const Quaternion& b, T t)
        {
            t = std::clamp(t, kZero<T>, kOne<T>);

            const T dot = a.Dot(b);
            const T sign = (dot < kZero<T>) ? -kOne<T> : kOne<T>;

            Quaternion result(
                std::lerp(a.w, b.w * sign, t),
                std::lerp(a.x, b.x * sign, t),
                std::lerp(a.y, b.y * sign, t),
                std::lerp(a.z, b.z * sign, t)
            );

            result.Normalize();
            return result;
        }

        static constexpr Quaternion Slerp(const Quaternion& a, const Quaternion& b, T t)
        {
            t = std::clamp(t, kZero<T>, kOne<T>);

            T dot = a.Dot(b);
            Quaternion target = b;
            if (dot < kZero<T>)
            {
                dot = -dot;
                target = -b;
            }

            if (dot > kOne<T> - kToleranceEpsilon<T>)
            {
                return Lerp(a, target, t);
            }

            T theta = std::acos(std::clamp(dot, -kOne<T>, kOne<T>));
            T sinT = std::sin(theta);
            T invSinT = kOne<T> / sinT;
            T scaleA = std::sin((kOne<T> - t) * theta) * invSinT;
            T scaleB = std::sin(t * theta) * invSinT;
            return (scaleA * a) + (scaleB * target);
        }

        // -------------------------
        // Operators
        // -------------------------

        constexpr bool operator==(const Quaternion& other) const = default;

        constexpr Quaternion operator+(const Quaternion& other) const
        {
            return { w + other.w, x + other.x, y + other.y, z + other.z };
        }

        constexpr Quaternion operator-(const Quaternion& other) const
        {
            return { w - other.w, x - other.x, y - other.y, z - other.z };
        }

        constexpr Quaternion operator*(const Quaternion& other) const
        {
            return Quaternion(
                w * other.w - x * other.x - y * other.y - z * other.z,
                w * other.x + x * other.w + y * other.z - z * other.y,
                w * other.y - x * other.z + y * other.w + z * other.x,
                w * other.z + x * other.y - y * other.x + z * other.w
            );
        }

        constexpr Quaternion operator*(T scalar) const
        {
            return { w * scalar, x * scalar, y * scalar, z * scalar };
        }

        constexpr Vector3<T> operator*(const Vector3<T>& v) const
        {
            return RotateVector(v);
        }

        constexpr Quaternion operator/(T scalar) const
        {
            return *this * (kOne<T> / scalar);
        }

        constexpr Quaternion operator-() const
        {
            return { -w, -x, -y, -z };
        }

        constexpr Quaternion& operator*=(const Quaternion& other)
        {
            Quaternion temp = *this;
            w = temp.w * other.w - temp.x * other.x - temp.y * other.y - temp.z * other.z;
            x = temp.w * other.x + temp.x * other.w + temp.y * other.z - temp.z * other.y;
            y = temp.w * other.y - temp.x * other.z + temp.y * other.w + temp.z * other.x;
            z = temp.w * other.z + temp.x * other.y - temp.y * other.x + temp.z * other.w;
            return *this;
        }

        constexpr Quaternion& operator*=(T scalar)
        {
            w *= scalar;
            x *= scalar;
            y *= scalar;
            z *= scalar;
            return *this;
        }

        constexpr Quaternion& operator/=(T scalar)
        {
            *this *= kOne<T> / scalar;
            return *this;
        }

        constexpr friend Quaternion operator*(T scalar, const Quaternion& q)
        {
            return q * scalar;
        }
    };

    using FQuaternion = Quaternion<float>;
    using DQuaternion = Quaternion<double>;
    using LDQuaternion = Quaternion<long double>;
}
