#pragma once
#include "SFML/Graphics.hpp"


bool frameCollisionX(float x, float radius)
{
    return (x + radius > 1920 || x - radius < 0);
}
bool frameCollisionY(float y, float radius)
{
    return (y + radius > 1080 || y - radius < 0);
}
float distance(Vector2f vec1, Vector2f vec2)
{
    float dx = vec1.x - vec2.x;
    float dy = vec1.y - vec2.y;
    return std::sqrt(dx * dx + dy * dy);
}
