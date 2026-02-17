/// Copyright (c) 2026 Jose Ilitzky

#pragma once

#include <algorithm>
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

        constexpr TQuaternion() : w(kOne), x(kZero), y(kZero), z(kZero) {}

        constexpr TQuaternion(T w, T x, T y, T z) : w(w), x(x), y(y), z(z) {}

        static constexpr TQuaternion Identity()
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

        static TQuaternion FromEuler(T rollDegrees, T pitchDegrees, T yawDegrees)
        {
            T halfRollRadians = rollDegrees * kHalf * kDegreesToRadians;
            T cosRoll = std::cos(halfRollRadians);
            T sinRoll = std::sin(halfRollRadians);

            T halfPitchRadians = pitchDegrees * kHalf * kDegreesToRadians;
            T cosPitch = std::cos(halfPitchRadians);
            T sinPitch = std::sin(halfPitchRadians);

            T halfYawRadians = yawDegrees * kHalf * kDegreesToRadians;
            T cosYaw = std::cos(halfYawRadians);
            T sinYaw = std::sin(halfYawRadians);

            return TQuaternion(
                cosRoll * cosPitch * cosYaw + sinRoll * sinPitch * sinYaw,
                sinRoll * cosPitch * cosYaw - cosRoll * sinPitch * sinYaw,
                cosRoll * sinPitch * cosYaw + sinRoll * cosPitch * sinYaw,
                cosRoll * cosPitch * sinYaw - sinRoll * sinPitch * cosYaw
            );
        }

        // -------------------------
        // Modifiers
        // -------------------------

        void Normalize()
        {
            T lengthSq = LengthSquared();
            if (lengthSq > kSafetyEpsilon)
            {
                T invLength = kOne / std::sqrt(lengthSq);
                w *= invLength;
                x *= invLength;
                y *= invLength;
                z *= invLength;
            }
            else
            {
                *this = Identity();
            }
        }

        void Conjugate()
        {
            x = -x;
            y = -y;
            z = -z;
        }

        void Inverse()
        {
            T lengthSq = LengthSquared();
            if (lengthSq > kSafetyEpsilon)
            {
                T invLengthSq = kOne / lengthSq;
                w *= invLengthSq;
                x *= -invLengthSq;
                y *= -invLengthSq;
                z *= -invLengthSq;
            }
            else
            {
                *this = Identity();
            }
        }

        // -------------------------
        // Core Logic
        // -------------------------

        bool IsNormalized() const
        {
            return std::abs(LengthSquared() - kOne) < kToleranceEpsilon;
        }

        T Length() const
        {
            return std::sqrt(LengthSquared());
        }

        T LengthSquared() const
        {
            return (w * w) + (x * x) + (y * y) + (z * z);
        }

        T Dot(const TQuaternion& other) const
        {
            return (w * other.w) + (x * other.x) + (y * other.y) + (z * other.z);
        }

        TQuaternion GetNormalized() const
        {
            TQuaternion result = *this;
            result.Normalize();
            return result;
        }

        TQuaternion GetConjugated() const
        {
            TQuaternion result = *this;
            result.Conjugate();
            return result;
        }

        TQuaternion GetInversed() const
        {
            TQuaternion result = *this;
            result.Inverse();
            return result;
        }

        TVector3<T> RotateVector(const TVector3<T>& v) const
        {
            T tempX = kTwo * (y * v.z - z * v.y);
            T tempY = kTwo * (z * v.x - x * v.z);
            T tempZ = kTwo * (x * v.y - y * v.x);

            return TVector3<T>(
                v.x + w * tempX + (y * tempZ - z * tempY),
                v.y + w * tempY + (z * tempX - x * tempZ),
                v.z + w * tempZ + (x * tempY - y * tempX)
            );
        }

        TVector3<T> ToEuler() const
        {
            TVector3<T> euler;

            T gimbalTest = w * y - x * z;
            if (gimbalTest > kHalf - kToleranceEpsilon)
            {
                euler.x = kZero;
                euler.y = kPi * kHalf;
                euler.z = kTwo * std::atan2(z, w);
            }
            else if (gimbalTest < kToleranceEpsilon - kHalf)
            {
                euler.x = kZero;
                euler.y = -kPi * kHalf;
                euler.z = kTwo * std::atan2(x, w);
            }
            else
            {
                T wSq = w * w;
                T xSq = x * x;
                T ySq = y * y;
                T zSq = z * z;

                euler.x = std::atan2(kTwo * (w * x + y * z), wSq - xSq - ySq + zSq);
                euler.y = std::asin(-kTwo * (x * z - w * y));
                euler.z = std::atan2(kTwo * (x * y + w * z), wSq + xSq - ySq - zSq);
            }

            return euler * kRadiansToDegrees;
        }

        void ToAxisAngle(TVector3<T>& outAxis, T& outDegrees) const
        {
            T clampedW = std::clamp(w, -kOne, kOne);
            T sinSqT = kOne - (clampedW * clampedW);
            if (sinSqT < kSafetyEpsilon)
            {
                outAxis = { kOne, kZero, kZero };
                outDegrees = kZero;
            }
            else
            {
                T invSinT = kOne / std::sqrt(sinSqT);
                outAxis.x = x * invSinT;
                outAxis.y = y * invSinT;
                outAxis.z = z * invSinT;
                outDegrees = std::acos(clampedW) * kTwo * kRadiansToDegrees;
            }
        }

        bool IsNearlyEqual(const TQuaternion& other, T epsilon = kSafetyEpsilon) const
        {
            T dot = this->Dot(other);
            return (kOne - std::abs(dot)) <= epsilon;
        }

        std::string ToString() const
        {
            std::stringstream stream;
            stream << "(" << w << ", " << x << ", " << y << ", " << z << ")";
            return stream.str();
        }

        // -------------------------
        // Utilities
        // -------------------------

        static TQuaternion Lerp(const TQuaternion& a, const TQuaternion& b, T t)
        {
            t = std::clamp(t, kZero, kOne);
            T dot = a.Dot(b);
            T scaleA = kOne - t;
            T scaleB = (dot < kZero) ? -t : t;

            TQuaternion result(
                scaleA * a.w + scaleB * b.w,
                scaleA * a.x + scaleB * b.x,
                scaleA * a.y + scaleB * b.y,
                scaleA * a.z + scaleB * b.z
            );

            result.Normalize();
            return result;
        }

        static TQuaternion Slerp(const TQuaternion& a, const TQuaternion& b, T t)
        {
            t = std::clamp(t, kZero, kOne);
            T dot = a.Dot(b);

            TQuaternion target = b;
            if (dot < kZero)
            {
                dot = -dot;
                target = -b;
            }

            if (dot > kOne - kToleranceEpsilon)
            {
                return Lerp(a, target, t);
            }

            T theta = std::acos(std::clamp(dot, -kOne, kOne));
            T sinT = std::sin(theta);
            T invSinT = kOne / sinT;
            T scaleA = std::sin((kOne - t) * theta) * invSinT;
            T scaleB = std::sin(t * theta) * invSinT;
            return (scaleA * a) + (scaleB * target);
        }

        // -------------------------
        // Operators
        // -------------------------

        TQuaternion operator+(const TQuaternion& other) const
        {
            return { w + other.w, x + other.x, y + other.y, z + other.z };
        }

        TQuaternion operator-(const TQuaternion& other) const
        {
            return { w - other.w, x - other.x, y - other.y, z - other.z };
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

        TQuaternion operator*(T scalar) const
        {
            return { w * scalar, x * scalar, y * scalar, z * scalar };
        }

        TVector3<T> operator*(const TVector3<T>& v) const
        {
            return RotateVector(v);
        }

        TQuaternion operator/(T scalar) const
        {
            return *this * (kOne / scalar);
        }

        TQuaternion operator-() const
        {
            return { -w, -x, -y, -z };
        }

        TQuaternion& operator*=(const TQuaternion& other)
        {
            TQuaternion temp = *this;
            w = temp.w * other.w - temp.x * other.x - temp.y * other.y - temp.z * other.z;
            x = temp.w * other.x + temp.x * other.w + temp.y * other.z - temp.z * other.y;
            y = temp.w * other.y - temp.x * other.z + temp.y * other.w + temp.z * other.x;
            z = temp.w * other.z + temp.x * other.y - temp.y * other.x + temp.z * other.w;
            return *this;
        }

        TQuaternion& operator*=(T scalar)
        {
            w *= scalar;
            x *= scalar;
            y *= scalar;
            z *= scalar;
            return *this;
        }

        TQuaternion& operator/=(T scalar)
        {
            *this *= kOne / scalar;
            return *this;
        }

        bool operator==(const TQuaternion& other) const
        {
            return w == other.w && x == other.x && y == other.y && z == other.z;
        }

        bool operator!=(const TQuaternion& other) const
        {
            return !(*this == other);
        }

        friend TQuaternion operator*(T scalar, const TQuaternion& q)
        {
            return q * scalar;
        }

    private:
        static constexpr T kZero = TZero<T>;
        static constexpr T kHalf = THalf<T>;
        static constexpr T kOne = TOne<T>;
        static constexpr T kTwo = TTwo<T>;
        static constexpr T kPi = TPi<T>;
        static constexpr T kDegreesToRadians = TDegreesToRadians<T>;
        static constexpr T kRadiansToDegrees = TRadiansToDegrees<T>;
        static constexpr T kToleranceEpsilon = TToleranceEpsilon<T>;
        static constexpr T kSafetyEpsilon = TSafetyEpsilon<T>;
    };

    using Quaternion = TQuaternion<float>;
    using DQuaternion = TQuaternion<double>;
    using LDQuaternion = TQuaternion<long double>;
}
