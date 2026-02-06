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
    inline constexpr T kToleranceEpsilon = std::numeric_limits<T>::epsilon() * static_cast<T>(1000);

    template<typename T>
    inline constexpr T kSafetyEpsilon = std::numeric_limits<T>::epsilon() * static_cast<T>(10);
}
