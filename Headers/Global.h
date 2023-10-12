#pragma once
#include "Planet.h"
#include "Button.h"

namespace gl
{
    bool frameCollisionX(float x, float radius);
    bool frameCollisionY(float y, float radius);
    double distance(Vector2f vec1, Vector2f vec2);
    Vector2f offset(double radius);
    Vector2f normalizeVector(Planet planet1, Planet planet2);
    void setStyleText(Text &text, Font &font, Vector2f position);
    bool collisionButton(float x, float y, float sizeX, float sizeY, float mouseX, float mouseY);
    //void generateButton(std::vector<Planet>& planets, std::vector<Button>& buttonsPlanet, std::vector<Button>& buttonsLogic, RenderWindow& window);
    void spawnPlanet(std::vector<Planet>& planets, RenderWindow& window);
    void calculatePanel(RectangleShape& panel, std::vector<Button>& buttonsPlanet, std::vector<Button>& buttonsLogic, RenderWindow& window, View& world, float& scaleWorldinWindow);
    void resetFosucPlanet(std::vector<Planet>& planets);
}

