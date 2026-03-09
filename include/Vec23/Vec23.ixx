module;

#include <algorithm>
#include <cassert>
#include <cmath>
#include <concepts>
#include <format>
#include <string>
#include "Constants.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Quaternion.h"

export module Vec23;

export namespace Vec23
{
    using Vec23::Vector2;
    using Vec23::Vector3;
    using Vec23::Quaternion;

    using FVector2 = Vector2<float>;
    using DVector2 = Vector2<double>;
    using LDVector2 = Vector2<long double>;

    using FVector3 = Vector3<float>;
    using DVector3 = Vector3<double>;
    using LDVector3 = Vector3<long double>;

    using FQuaternion = Quaternion<float>;
    using DQuaternion = Quaternion<double>;
    using LDQuaternion = Quaternion<long double>;
}
