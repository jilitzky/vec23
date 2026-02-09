/// Copyright (c) 2026 Jose Ilitzky

#pragma once

#include "Constants.h"

namespace Vec23
{
    template<typename T>
    struct TQuaternion
    {
        static_assert(std::is_floating_point_v<T>, "TQuaternion template parameter must be a floating point type");

        static constexpr T Zero = kZero<T>;
        static constexpr T One = kOne<T>;

        T w;
        T x;
        T y;
        T z;

        constexpr TQuaternion() noexcept : w(One), x(Zero), y(Zero), z(Zero) {}

        constexpr TQuaternion(T w, T x, T y, T z) noexcept : w(w), x(x), y(y), z(z) {}

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
    };

    using Quaternion = TQuaternion<float>;
    using DQuaternion = TQuaternion<double>;
    using LDQuaternion = TQuaternion<long double>;
}
