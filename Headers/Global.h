#pragma once
#include "Planet.h"
#include "Button.h"

namespace gl
{
    void beyondSolarSystem(std::vector<Planet>& planets, std::vector<Button>& buttonPlanets);
    double distance(Vector2f vec1, Vector2f vec2);
    Vector2f offset(double radius);
    Vector2f normalizeVector(Planet planet1, Planet planet2);
    bool collisionButton(float x, float y, float sizeX, float sizeY, float mouseX, float mouseY);
    void spawnPlanet(std::vector<Planet>& planets, RenderWindow& window);
    void calculatePanel(RectangleShape& panel, RectangleShape& panelInfo, RectangleShape& panelPlanet, RenderWindow& window, View& world, double& scaleWorldinWindow);
    void calculateBackground(RectangleShape& background, RenderWindow& window, View& world);
    void calculateButtonPlanet(std::vector<Button>& buttonsPlanet, RenderWindow& window, View& world, double& scaleWorldinWindow);
    void calculateButtonLogic(std::vector<Button>& buttonsLogic, RenderWindow& window, View& world, double& scaleWorldinWindow);
    void calculateNamesPlanet(std::vector<RectangleShape>& namesPlanet, RenderWindow& window, double& scaleWorldinWindow);
    void resetFosucPlanet(std::vector<Planet>& planets);
    void resetStatusButton(std::vector<Button>& buttons);
    void resetMenuPlanets(std::vector<Planet>& planets);
    void logicPlanet(std::vector<Planet>& planets, double& G, double& scalePhy, View& world);
    void drawButtons(std::vector<Button>& buttons, RenderWindow& window);
    void collisionPlanet(std::vector<Planet>& planets, std::vector<Button>& buttonsPlanet, RenderWindow& window, View& world, double scaleWorldinWindow);
    void generateButton(std::vector<Planet>& planets, std::vector<Button>& buttonsPlanet, std::vector<Button>& buttonsLogic, std::vector<RectangleShape>& namesPlanet, RenderWindow& window);
    void genButtonMenu(std::vector<Button>& buttonsMass, std::vector<Button>& buttonsSpeed, std::vector<Button>& buttonsCamera, std::vector<Button>& buttonsCloceAndDelete, RenderWindow& window);
    void calculateButtonMenu(std::vector<Button>& buttonsMass, std::vector<Button>& buttonsSpeed, std::vector<Button>& buttonsCamera, std::vector<Button>& buttonsCloceAndDelete, RenderWindow& window, View& world, double& scaleWorldinWindow);
}