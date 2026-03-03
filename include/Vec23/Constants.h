/// Copyright (c) 2026 Jose Ilitzky

#pragma once

#include <concepts>
#include <limits>
#include <numbers>

namespace Vec23
{
    template<std::floating_point T>
    inline constexpr T kZero = T(0);

    template<std::floating_point T>
    inline constexpr T kHalf = T(0.5);

    template<std::floating_point T>
    inline constexpr T kOne = T(1);

    template<std::floating_point T>
    inline constexpr T kTwo = T(2);

    template<std::floating_point T>
    inline constexpr T kPi = std::numbers::pi_v<T>;
    
    template<std::floating_point T>
    inline constexpr T kDegreesToRadians = kPi<T> / T(180);

    template<std::floating_point T>
    inline constexpr T kRadiansToDegrees = T(180) / kPi<T>;

    template<std::floating_point T>
    inline constexpr T kToleranceEpsilon =
        std::same_as<T, long double> ? 1e-12L :
        std::same_as<T, double> ? 1e-9 :
        1e-4f;

    template<std::floating_point T>
    inline constexpr T kSafetyEpsilon =
        std::same_as<T, long double> ? 1e-15L :
        std::same_as<T, double> ? 1e-12 :
        1e-6f;
}
