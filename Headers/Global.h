#pragma once
#include "Planet.h"
#include "Button.h"

namespace gl
{
    double distance(Vector2f vec1, Vector2f vec2);
    Vector2f offset(double radius);
    Vector2f normalizeVector(Planet planet1, Planet planet2);
    void setStyleText(Text &text, Font &font, Vector2f position);
    bool collisionButton(float x, float y, float sizeX, float sizeY, float mouseX, float mouseY);
    void spawnPlanet(std::vector<Planet>& planets, RenderWindow& window);
    void calculatePanel(RectangleShape& panel, RenderWindow& window, View& world, float& scaleWorldinWindow);
    void calculateButtonPlanet(std::vector<Button>& buttonsPlanet, RenderWindow& window, View& world, float& scaleWorldinWindow);
    void calculateButtonLogic(std::vector<Button>& buttonsLogic, RenderWindow& window, View& world, float& scaleWorldinWindow);
    void resetFosucPlanet(std::vector<Planet>& planets);
    void logicPlanet(std::vector<Planet>& planets, double& G, double& scalePhy, View& world);
    void drawButtons(std::vector<Button>& buttons, RenderWindow& window);
    void collisionPlanet(std::vector<Planet>& planets, std::vector<Button>& buttonsPlanet, RenderWindow& window, View& world, float scaleWorldinWindow);
    void generateButton(std::vector<Planet>& planets, std::vector<Button>& buttonsPlanet, std::vector<Button>& buttonsLogic, RenderWindow& window);
}
