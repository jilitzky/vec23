/// Copyright (c) 2026 Jose Ilitzky

#pragma once

#include <limits>

namespace Vec23
{
    template<typename T>
    inline constexpr T kPi = static_cast<T>(3.1415926535897932384626433L);
    
    template<typename T>
    inline constexpr T kRadiansToDegrees = static_cast<T>(180.L) / kPi<T>;

    template<typename T>
    inline constexpr T kDegreesToRadians = kPi<T> / static_cast<T>(180.L);

    template<typename T>
    inline constexpr T kToleranceEpsilon =
        (sizeof(T) > 8) ? static_cast<T>(1e-12L) :
        (sizeof(T) == 8) ? static_cast<T>(1e-9) :
        static_cast<T>(1e-4f);

    template<typename T>
    inline constexpr T kSafetyEpsilon =
        (sizeof(T) > 8) ? static_cast<T>(1e-15L) :
        (sizeof(T) == 8) ? static_cast<T>(1e-12) :
        static_cast<T>(1e-6f);
}
