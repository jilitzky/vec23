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

        static TQuaternion FromAxisAngle(const TVector3<T>& axis, float degrees)
        {
            float radians = degrees * kDegreesToRadians;
        }

        // -------------------------
        // Modifiers
        // -------------------------

        // -------------------------
        // Core Logic
        // -------------------------

        // -------------------------
        // Utilities
        // -------------------------

        // -------------------------
        // Operators
        // -------------------------

    private:
        static constexpr T kZero = TZero<T>;
        static constexpr T kOne = TOne<T>;
        static constexpr T kDegreesToRadians = TDegreesToRadians<T>;
    };

    using Quaternion = TQuaternion<float>;
    using DQuaternion = TQuaternion<double>;
    using LDQuaternion = TQuaternion<long double>;
}
