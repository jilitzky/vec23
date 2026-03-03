/// Copyright (c) 2026 Jose Ilitzky

#pragma once

#include <concepts>

namespace Vec23
{
    template<std::floating_point T>
    inline constexpr T TZero = static_cast<T>(0.0L);

    template<std::floating_point T>
    inline constexpr T THalf = static_cast<T>(0.5L);

    template<std::floating_point T>
    inline constexpr T TOne = static_cast<T>(1.0L);

    template<std::floating_point T>
    inline constexpr T TTwo = static_cast<T>(2.0L);

    template<std::floating_point T>
    inline constexpr T TPi = static_cast<T>(3.1415926535897932384626433L);
    
    template<std::floating_point T>
    inline constexpr T TDegreesToRadians = TPi<T> / static_cast<T>(180.0L);

    template<std::floating_point T>
    inline constexpr T TRadiansToDegrees = static_cast<T>(180.0L) / TPi<T>;

    template<std::floating_point T>
    inline constexpr T TToleranceEpsilon =
        (sizeof(T) > 8) ? static_cast<T>(1e-12L) :
        (sizeof(T) == 8) ? static_cast<T>(1e-9) :
        static_cast<T>(1e-4f);

    template<std::floating_point T>
    inline constexpr T TSafetyEpsilon =
        (sizeof(T) > 8) ? static_cast<T>(1e-15L) :
        (sizeof(T) == 8) ? static_cast<T>(1e-12) :
        static_cast<T>(1e-6f);
}
