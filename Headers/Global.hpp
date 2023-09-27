#pragma once
#include "SFML/Graphics.hpp"

double SCALEPHY = (double)1e9;
double SCALEGRAP = 1;
Time TIMEPERFRAME = seconds(1.0f / 600); // tps
Time TIMEPERFRAME2 = seconds(1.0f / 60); // fps

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
Vector2f offset(double radius)
{
    return Vector2f(radius, radius);
}
Vector2f normalizeVector(Planet planet1, Planet planet2)
{
    Vector2f vec = (planet1.getPosition() + offset(planet1.getRadius())) - (planet2.getPosition() + offset(planet2.getRadius()));
    double distan = distance(planet1.getPosition() + offset(planet1.getRadius()), planet2.getPosition() + offset(planet2.getRadius()));
    return Vector2f((float)vec.x / distan, (float)vec.y / distan);
}
