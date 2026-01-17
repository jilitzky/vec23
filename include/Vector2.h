/// Copyright (c) 2026 Jose Ilitzky

#pragma once

namespace Vec23
{
    struct Vector2
    {
        float x;
        float y;

        // TODO: Why was = default not working?
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

        // TODO: Figure out why it's useful to do component-wise multiplication
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
            float multiplier = 1.f / scalar;
            return (*this * multiplier);
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

        // TODO: Should subtraction be implemented based on addition?
        Vector2& operator-=(const Vector2& other)
        {
            x -= other.x;
            y -= other.y;
            return *this;
        }

        // TODO: Why are there no unit tests for this?
        Vector2& operator*=(float scalar)
        {
            x *= scalar;
            y *= scalar;
            return *this;
        }

        Vector2& operator/=(float scalar)
        {
            *this *= 1.f / scalar;
            return *this;
        }

        bool operator==(const Vector2& other) const
        {
            return (x == other.x) && (y == other.y);
        }

        bool operator!=(const Vector2& other) const
        {
            return !(*this == other);
        }

        float& operator[](int index)
        {
            switch (index)
            {
            case 0:
                return x;
            case 1:
                return y;
            default:
                // TODO: What do we do here?
                static float zero = 0.f;
                return zero;
            }
        }

        // TODO: Can we reuse the non-const accessor?
        const float& operator[](int index) const
        {
            switch (index)
            {
            case 0:
                return x;
            case 1:
                return y;
            default:
                // TODO: What do we do here?
                static float zero = 0.f;
                return zero;
            }
        }

        // TODO: Why is this not working?
        //Vector2 operator*(float scalar, const Vector2& vector)
        //{
        //    return vector * scalar;
        //}
    };
}
