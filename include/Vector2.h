/// Copyright (c) 2026 Jose Ilitzky

#pragma once

namespace Vec23
{
    struct Vector2
    {
        float x;
        float y;

        // -------------------------
        // Constructors
        // -------------------------

        Vector2() : x(0.f), y(0.f) {}

        Vector2(float scalar) : x(scalar), y(scalar) {}

        Vector2(float x, float y) : x(x), y(y) {}

        // -------------------------
        // Operators
        // -------------------------

        Vector2 operator+(const Vector2& other) const
        {
            return { x + other.x, y + other.y };
        }

        Vector2 operator-(const Vector2& other) const
        {
            return { x - other.x, y - other.y };
        }

        Vector2 operator*(const Vector2& other) const
        {
            return { x * other.x, y * other.y };
        }

        Vector2 operator*(float scalar) const
        {
            return { x * scalar, y * scalar };
        }

        Vector2 operator/(float scalar) const
        {
            float inv = 1.f / scalar;
            return { x * inv, y * inv };
        }

        Vector2 operator-() const
        {
            return { -x, -y };
        }

        Vector2& operator+=(const Vector2& other)
        {
            x += other.x;
            y += other.y;
            return *this;
        }

        Vector2& operator-=(const Vector2& other)
        {
            x -= other.x;
            y -= other.y;
            return *this;
        }

        Vector2& operator*=(float scalar)
        {
            x *= scalar;
            y *= scalar;
            return *this;
        }

        Vector2& operator/=(float scalar)
        {
            float inv = 1.f / scalar;
            x *= inv;
            y *= inv;
            return *this;
        }

        bool operator==(const Vector2& other) const
        {
            return x == other.x && y == other.y;
        }

        bool operator!=(const Vector2& other) const
        {
            return !(*this == other);
        }

        float& operator[](int index)
        {
            assert(index >= 0 && index < 2);
            return (&x)[index];
        }

        const float& operator[](int index) const
        {
            assert(index >= 0 && index < 2);
            return (&x)[index];
        }

        // -------------------------
        // Methods
        // -------------------------

        float Dot(const Vector2& other) const
        {
            return (x * other.x) + (y * other.y);
        }

        float Cross(const Vector2& other) const
        {
            return (x * other.y) - (y * other.x);
        }

        float Length() const
        {
            return std::sqrtf(LengthSquared());
        }

        float LengthSquared() const
        {
            return (x * x) + (y * y);
        }

        // TODO: Why are we using an epsilon of 1e-6f here?
        void Normalize()
        {
            float lengthSq = LengthSquared();
            if (lengthSq > 1e-6f)
            {
                float inv = 1.f / std::sqrt(lengthSq);
                x *= inv;
                y *= inv;
            }
            else
            {
                x = 0.f;
                y = 0.f;
            }
        }

        // TODO: Why are we using an epsilon of 1e-6f here?
        Vector2 GetNormalized() const
        {
            float lengthSq = LengthSquared();
            if (lengthSq > 1e-6f)
            {
                float inv = 1.f / std::sqrt(lengthSq);
                return { x * inv, y * inv };
            }
            return { 0.f, 0.f };
        }

        // TODO: Why are we using an epsilon of 1e-4f here?
        bool IsNormalized() const
        {
            return (std::abs(LengthSquared() - 1.f) < 1e-4f);
        }

        // -------------------------
        // Utilities
        // -------------------------

        static float Distance(const Vector2& a, const Vector2& b)
        {
            return std::sqrt(DistanceSquared(a, b));
        }

        static float DistanceSquared(const Vector2& a, const Vector2& b)
        {
            float dx = b.x - a.x;
            float dy = b.y - a.y;
            return (dx * dx) + (dy * dy);
        }

        //// Reflects vector 'v' off surface with normal 'n'
        static Vector2 Reflect(const Vector2& v, const Vector2& n)
        {
            return { 0, 0 };
        }

        static Vector2 Lerp(const Vector2& a, const Vector2& b, float t)
        {
            return (a * (1.f - t)) + (b * t);
        }

        std::string ToString() const
        {
            std::stringstream stream;
            stream << "{" << x << ", " << y << "}";
            return stream.str();
        }
    };

    // -------------------------
    // Global Operators
    // -------------------------

    Vector2 operator*(float scalar, const Vector2& vector)
    {
        return vector * scalar;
    }
}
