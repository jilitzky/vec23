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

        Vector2(float x, float y) : x(x), y(y) {}

        Vector2 operator+(const Vector2& other)
        {
            return { x + other.x, y + other.y };
        }

        Vector2 operator-(const Vector2& other)
        {
            return { x - other.x, y - other.y };
        }

        // TODO: Figure out when it's useful to use component-wise multiplication
        Vector2 operator*(const Vector2& other)
        {
            return { x * other.x, y * other.y };
        }

        Vector2 operator*(float scalar)
        {
            return { x * scalar, y * scalar };
        }

        // TODO: Can this be optimized?
        Vector2 operator/(float scalar)
        {
            return { x / scalar, y / scalar };
        }
    };
}
