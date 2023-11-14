#pragma once
#include "Planet.h"
#include "Button.h"

namespace gl
{
    void beyondSolarSystem(std::vector<Planet>& planets, std::vector<Button>& buttonPlanets);
    double distance(Vector2f vec1, Vector2f vec2);
    Vector2f offset(double radius);
    Vector2f normalizeVector(Planet planet1, Planet planet2);
    void setStyleText(Text& text, Font& font);
    bool collisionButton(float x, float y, float sizeX, float sizeY, float mouseX, float mouseY);
    void spawnPlanet(std::vector<Planet>& planets, RenderWindow& window);
    void resetFosucPlanet(std::vector<Planet>& planets);
    void resetStatusButton(std::vector<Button>& buttons);
    void resetMenuPlanets(std::vector<Planet>& planets);
    void logicPlanet(std::vector<Planet>& planets, double& G, double& scalePhy);
    void drawButtons(std::vector<Button>& buttons, RenderWindow& window);
    void drawTrackAndPlanet(std::vector<Planet>& planets, RenderWindow& window);
    void collisionPlanet(std::vector<Planet>& planets, std::vector<Button>& buttonsPlanet);
    void generateButton(std::vector<Planet>& planets, std::vector<Button>& buttonsPlanet, std::vector<Button>& buttonsLogic, std::vector<RectangleShape>& namesPlanet, RenderWindow& window);
    void genButtonMenu(std::vector<Button>& buttonsMass, std::vector<Button>& buttonsSpeed, std::vector<Button>& buttonsLogicPanelPlanet, RenderWindow& window);
}