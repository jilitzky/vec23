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

        TQuaternion() : w(One), x(Zero), y(Zero), z(Zero) {}

        TQuaternion(T x, T y) : x(x), y(y) {}

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
