/// Copyright (c) 2026 Jose Ilitzky

#pragma once

#include "Constants.h"
#include "Vector3.h"

namespace Vec23
{
    template<typename T>
    struct TQuaternion
    {
        static_assert(std::is_floating_point_v<T>, "TQuaternion template parameter must be a floating point type");

        T w;
        T x;
        T y;
        T z;

        constexpr TQuaternion() noexcept : w(kOne), x(kZero), y(kZero), z(kZero) {}

        constexpr TQuaternion(T w, T x, T y, T z) noexcept : w(w), x(x), y(y), z(z) {}

        static constexpr TQuaternion Identity() noexcept
        {
            return TQuaternion();
        }
        
        static TQuaternion FromAxisAngle(const TVector3<T>& axis, T degrees)
        {
            T halfRadians = degrees * kHalf * kDegreesToRadians;
            T cosT = std::cos(halfRadians);
            T sinT = std::sin(halfRadians);

            TVector3 u = axis;
            T lengthSq = u.LengthSquared();

            if (lengthSq < kSafetyEpsilon)
            {
                return Identity();
            }

            if (std::abs(lengthSq - kOne) > kSafetyEpsilon)
            {
                u.Normalize();
            }

            return { cosT, u.x * sinT, u.y * sinT, u.z * sinT };
        }

        // -------------------------
        // Modifiers
        // -------------------------

        // -------------------------
        // Core Logic
        // -------------------------

        bool IsNearlyEqual(const TQuaternion& other, T epsilon = kSafetyEpsilon) const
        {
            return std::abs(w - other.w) <= epsilon && std::abs(x - other.x) <= epsilon && std::abs(y - other.y) <= epsilon && std::abs(z - other.z) <= epsilon;
        }

        // -------------------------
        // Utilities
        // -------------------------

        // -------------------------
        // Operators
        // -------------------------

        TQuaternion& operator*=(const TQuaternion& other)
        {
            TQuaternion temp = *this;
            w = temp.w * other.w - temp.x * other.x - temp.y * other.y - temp.z * other.z;
            x = temp.w * other.x + temp.x * other.w + temp.y * other.z - temp.z * other.y;
            y = temp.w * other.y - temp.x * other.z + temp.y * other.w + temp.z * other.x;
            z = temp.w * other.z + temp.x * other.y - temp.y * other.x + temp.z * other.w;
            return *this;
        }

        TQuaternion operator*(const TQuaternion& other) const
        {
            return TQuaternion(
                w * other.w - x * other.x - y * other.y - z * other.z,
                w * other.x + x * other.w + y * other.z - z * other.y,
                w * other.y - x * other.z + y * other.w + z * other.x,
                w * other.z + x * other.y - y * other.x + z * other.w
            );
        }

    private:
        static constexpr T kZero = TZero<T>;
        static constexpr T kHalf = THalf<T>;
        static constexpr T kOne = TOne<T>;
        static constexpr T kDegreesToRadians = TDegreesToRadians<T>;
        static constexpr T kSafetyEpsilon = TVector3<T>::kSafetyEpsilon;
    };

    using Quaternion = TQuaternion<float>;
    using DQuaternion = TQuaternion<double>;
    using LDQuaternion = TQuaternion<long double>;
}
