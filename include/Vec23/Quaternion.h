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

        static TQuaternion FromEuler(T pitch, T yaw, T roll)
        {
            // TODO: Implement me!
            return {};
        }

        static TQuaternion LookAt(const TVector3<T>& forward, const TVector3<T>& up)
        {
            // TODO: Implement me!
            return {};
        }

        // -------------------------
        // Modifiers
        // -------------------------

        void Normalize()
        {
            T lengthSq = LengthSquared();
            if (lengthSq > kSafetyEpsilon)
            {
                T inv = kOne / std::sqrt(lengthSq);
                w *= inv;
                x *= inv;
                y *= inv;
                z *= inv;
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
                T inv = kOne / lengthSq;
                w *= inv;
                x *= -inv;
                y *= -inv;
                z *= -inv;
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
            // TODO: Implement me!
            return {};
        }

        void ToAxisAngle(TVector3<T>& outAxis, T& outDegrees) const
        {
            // TODO: Implement me!
        }

        bool IsNearlyEqual(const TQuaternion& other, T epsilon = kSafetyEpsilon) const
        {
            return std::abs(w - other.w) <= epsilon && std::abs(x - other.x) <= epsilon && std::abs(y - other.y) <= epsilon && std::abs(z - other.z) <= epsilon;
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
            // TODO: Implement me!
            return {};
        }

        static TQuaternion Slerp(const TQuaternion& a, const TQuaternion& b, T t)
        {
            // TODO: Implement me!
            return {};
        }

        // -------------------------
        // Operators
        // -------------------------

        TQuaternion& operator*=(const TQuaternion& other)
        {
            TQuaternion temp = *this;
            w = temp.w * other.w - temp.x * other.x - temp.y * other.y - temp.z * other.z;
            x = temp.w * other.x + temp.x * other.w + temp.y * other.z - temp.z * other.y;
            y = temp.w * other.y - temp.x * other.z + temp.y * other.w + temp.z * other.x;
            z = temp.w * other.z + temp.x * other.y - temp.y * other.x + temp.z * other.w;
            return *this;
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

        TVector3<T> operator*(const TVector3<T>& v) const
        {
            return RotateVector(v);
        }

        bool operator==(const TQuaternion& other) const
        {
            return w == other.w && x == other.x && y == other.y && z == other.z;
        }

        bool operator!=(const TQuaternion& other) const
        {
            return !(*this == other);
        }

    private:
        static constexpr T kZero = TZero<T>;
        static constexpr T kHalf = THalf<T>;
        static constexpr T kOne = TOne<T>;
        static constexpr T kTwo = TTwo<T>;
        static constexpr T kDegreesToRadians = TDegreesToRadians<T>;
        static constexpr T kSafetyEpsilon = TSafetyEpsilon<T>;
    };

    using Quaternion = TQuaternion<float>;
    using DQuaternion = TQuaternion<double>;
    using LDQuaternion = TQuaternion<long double>;
}
