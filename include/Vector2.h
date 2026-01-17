/// Copyright (c) 2026 Jose Ilitzky

#pragma once

namespace Vec23
{
    struct Vector2
    {
        float x;
        float y;

        Vector2() : x(0.f), y(0.f) {}

        Vector2(float scalar) : x(scalar), y(scalar) {}

        Vector2(float x, float y) : x(x), y(y) {}

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

        // TODO: Why is this not working?
        //Vector2 operator*(float scalar, const Vector2& vector)
        //{
        //    return vector * scalar;
        //}
    };
}
