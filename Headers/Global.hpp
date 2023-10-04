#pragma once
#include "Planet.hpp"

namespace global
{
    bool frameCollisionX(float x, float radius);
    bool frameCollisionY(float y, float radius);
    double distance(Vector2f vec1, Vector2f vec2);
    Vector2f offset(double radius);
    Vector2f normalizeVector(Planet planet1, Planet planet2);
    void spawnPlanet(std::vector<Planet> &planets, RenderWindow &window);
}
