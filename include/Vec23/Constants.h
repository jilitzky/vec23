/// Copyright (c) 2026 Jose Ilitzky

#pragma once

#include <concepts>
#include <limits>
#include <numbers>

namespace Vec23
{
    template<std::floating_point T>
    inline constexpr T TZero = T(0);

    template<std::floating_point T>
    inline constexpr T THalf = T(0.5);

    template<std::floating_point T>
    inline constexpr T TOne = T(1);

    template<std::floating_point T>
    inline constexpr T TTwo = T(2);

    template<std::floating_point T>
    inline constexpr T TPi = std::numbers::pi_v<T>;
    
    template<std::floating_point T>
    inline constexpr T TDegreesToRadians = TPi<T> / T(180);

    template<std::floating_point T>
    inline constexpr T TRadiansToDegrees = T(180) / TPi<T>;

    template<std::floating_point T>
    inline constexpr T TToleranceEpsilon =
        std::same_as<T, long double> ? 1e-12L :
        std::same_as<T, double> ? 1e-9 :
        1e-4f;

    template<std::floating_point T>
    inline constexpr T TSafetyEpsilon =
        std::same_as<T, long double> ? 1e-15L :
        std::same_as<T, double> ? 1e-12 :
        1e-6f;
}
