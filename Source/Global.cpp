#include "../Headers/Global.h"
#include "../Headers/Texture.h"
#include <ppl.h>

using namespace sf;
void gl::beyondSolarSystem(std::vector<Planet>& planets, std::vector<Button>& buttonPlanets) 
{
    for (int i = 0; i < planets.size(); i++)
    {
        if ( -34500 > planets[i].getPosition().x || planets[i].getPosition().x > 34500 || -34500 > planets[i].getPosition().y  || planets[i].getPosition().y > 34500)
        {
            planets.erase(planets.begin() + i);
            buttonPlanets.erase(buttonPlanets.begin() + i);
        }
    }
}

double gl::distance(Vector2f vec1, Vector2f vec2)
{
    double dx = vec1.x - vec2.x;
    double dy = vec1.y - vec2.y;
    return std::sqrt(dx * dx + dy * dy);
}
Vector2f gl::offset(double radius)
{
    return Vector2f(radius, radius);
}
Vector2f gl::normalizeVector(Planet planet1, Planet planet2)
{
    Vector2f vec = (planet1.getPosition() + offset(planet1.getRadius())) - (planet2.getPosition() + offset(planet2.getRadius()));
    double distan = distance(planet1.getPosition() + offset(planet1.getRadius()), planet2.getPosition() + offset(planet2.getRadius()));
    return Vector2f((float)vec.x / distan, (float)vec.y / distan);
}

void gl::setStyleText(Text& text, Font& font, double& scaleWorldinWindow)
{
    text.setFont(font);
    text.setFillColor(Color::White);
    text.setCharacterSize(18 * scaleWorldinWindow);
}
bool gl::collisionButton(float x, float y, float sizeX, float sizeY, float mouseX, float mouseY)
{
    return (mouseX >= x && mouseX <= sizeX + x) && (mouseY >= y && mouseY <= sizeY + y);
}
void gl::spawnPlanet(std::vector<Planet>& planets, RenderWindow& window)
{
    planets.push_back(Planet(70, 2e30, Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f), Vector2f(0, 0.0), Color::Color(255, 255, 0), L"Солнце"));
    planets.push_back(Planet(0.3, 3.33e23, Vector2f(planets[0].getPosition().x + planets[0].getRadius() * 2 + 58, planets[0].getPosition().y + planets[0].getRadius()), Vector2f(0, 1.03), Color::Color(209, 159, 120), L"Меркурий"));
    planets.push_back(Planet(0.6, 4.87e24, Vector2f(planets[0].getPosition().x + planets[0].getRadius() * 2 + 108, planets[0].getPosition().y + planets[0].getRadius()), Vector2f(0, 0.9), Color::Color(167, 92, 21), L"Венера"));
    planets.push_back(Planet(0.6, 5.97e24, Vector2f(planets[0].getPosition().x + planets[0].getRadius() * 2 + 150, planets[0].getPosition().y + planets[0].getRadius()), Vector2f(0, 0.8), Color::Color(85, 118, 145), L"Земля"));
    planets.push_back(Planet(0.4, 6.42e23, Vector2f(planets[0].getPosition().x + planets[0].getRadius() * 2 + 228, planets[0].getPosition().y + planets[0].getRadius()), Vector2f(0, 0.68), Color::Color(255, 0, 0), L"Марс"));
    planets.push_back(Planet(7, 1.89e27, Vector2f(planets[0].getPosition().x + planets[0].getRadius() * 2 + 778, planets[0].getPosition().y + planets[0].getRadius()), Vector2f(0, -0.4), Color::Color(172, 153, 128), L"Юпитер"));
    planets.push_back(Planet(6, 5.68e26, Vector2f(planets[0].getPosition().x + planets[0].getRadius() * 2 + 1400, planets[0].getPosition().y + planets[0].getRadius()), Vector2f(0, -0.30), Color::Color(222, 189, 110), L"Сатурн"));
    planets.push_back(Planet(2.5, 8.68e25, Vector2f(planets[0].getPosition().x + planets[0].getRadius() * 2 + 2800, planets[0].getPosition().y + planets[0].getRadius()), Vector2f(0, -0.22), Color::Color(111, 231, 234), L"Уран"));
    planets.push_back(Planet(2.4, 1.024e26, Vector2f(planets[0].getPosition().x + planets[0].getRadius() * 2 + 4550, planets[0].getPosition().y + planets[0].getRadius()), Vector2f(0, -0.17), Color::Color(0, 0, 255), L"Нептун"));
}
void gl::calculatePanel(RectangleShape& panel, RectangleShape &panelInfo, RectangleShape &panelPlanet, RenderWindow& window, View& world, double& scaleWorldinWindow)
{
    window.setView(world);
    Vector2f panelCoords = window.mapPixelToCoords(Vector2i(0, 0));
    panel.setSize(Vector2f(window.getSize().x / 12.8 * scaleWorldinWindow, world.getSize().y));
    panel.setPosition(Vector2f(panelCoords.x, panelCoords.y));
    Vector2f panelInfoCoords = window.mapPixelToCoords(Vector2i(window.getSize().x / 1.19, 0));
    panelInfo.setSize(Vector2f(window.getSize().x / 6.4 * scaleWorldinWindow, window.getSize().y / 10.8 * scaleWorldinWindow));
    panelInfo.setPosition(Vector2f(panelInfoCoords.x, panelInfoCoords.y));
    Vector2f panelPlanetCoords = window.mapPixelToCoords(Vector2i(window.getSize().x / 2.74, window.getSize().y / 4.5));
    panelPlanet.setSize(Vector2f(window.getSize().x / 3.84 * scaleWorldinWindow, window.getSize().y / 1.8 * scaleWorldinWindow));
    panelPlanet.setPosition(Vector2f(panelPlanetCoords.x, panelPlanetCoords.y));
}
void gl::calculateBackground(RectangleShape& background, RenderWindow& window, View& world)
{
    window.setView(world);
    Vector2f backgroundCoords = window.mapPixelToCoords(Vector2i(0, 0));
    background.setPosition(Vector2f(backgroundCoords.x, backgroundCoords.y));
    background.setSize(Vector2f(world.getSize().x, world.getSize().y));
}
void gl::calculateButtonPlanet(std::vector<Button>& buttonsPlanet, RenderWindow& window, View& world, double& scaleWorldinWindow)
{
    window.setView(world);
    Vector2f buttonCoords = window.mapPixelToCoords(Vector2i(window.getSize().x / 76.8, window.getSize().y / 54.0f));
    for (int i = 0; i < buttonsPlanet.size(); i++)
    {
        buttonsPlanet[i].setSize(Vector2f(window.getSize().x / 19.2 * scaleWorldinWindow, window.getSize().y / 36.0f * scaleWorldinWindow));
        buttonsPlanet[i].setPosition(Vector2f(buttonCoords.x, buttonCoords.y + window.getSize().y / 21.6 * scaleWorldinWindow * i));
    }
}
void gl::calculateButtonLogic(std::vector<Button>& buttonsLogic, std::vector<Button> &buttonsInfo, RenderWindow& window, View& world, double& scaleWorldinWindow)
{
    window.setView(world);
    Vector2f buttonCoordsL = window.mapPixelToCoords(Vector2i(window.getSize().x / 38.4, window.getSize().y / 2.3));
    Vector2f buttonCoordsI = window.mapPixelToCoords(Vector2i(window.getSize().x / 17.5, window.getSize().y / 2.25));
    for (int i = 0; i < buttonsLogic.size(); i++)
    {
        buttonsLogic[i].setSize(Vector2f(window.getSize().x / 38.4 * scaleWorldinWindow, window.getSize().y / 21.6 * scaleWorldinWindow));
        buttonsLogic[i].setPosition(Vector2f(buttonCoordsL.x, buttonCoordsL.y + window.getSize().y / 18 * scaleWorldinWindow * i));
    }
    for (int i = 0; i < buttonsInfo.size(); i++)
    {
        buttonsInfo[i].setSize(Vector2f(window.getSize().x / 64.0f  * scaleWorldinWindow, window.getSize().y / 36.0f * scaleWorldinWindow));
        buttonsInfo[i].setPosition(Vector2f(buttonCoordsI.x, buttonCoordsI.y + window.getSize().y / 18.0f * scaleWorldinWindow * i));
    }
}
void gl::calculateNamesPlanet(std::vector<RectangleShape>& namesPlanet, RenderWindow& window, double& scaleWorldinWindow)
{
    for (int i = 0; i < namesPlanet.size(); i++)
    {
        namesPlanet[i].setSize(Vector2f(window.getSize().x / 21.8 * scaleWorldinWindow, window.getSize().y / 77.1 * scaleWorldinWindow));
    }
}
void gl::resetFosucPlanet(std::vector<Planet>& planets)
{
    for (int i = 0; i < planets.size(); i++)
    {
        planets[i].setFocus(false);
    }
}
void gl::resetStatusButton(std::vector<Button>& buttons)
{
    for (int i = 0; i < buttons.size(); i++)
    {
        buttons[i].setStatus(false);
    }
}
void gl::resetMenuPlanets(std::vector<Planet>& planets)
{
    for (int i = 0; i < planets.size(); i++)
    {
        planets[i].setMenuPlanet(false);
    }
}

void gl::logicPlanet(std::vector<Planet>& planets, double& G, double& scalePhy, View& world)
{
    Concurrency::parallel_for(0, (int)planets.size(), [&](int j)
        {
            for (int i = 0; i < planets.size(); i++)
            {
                if (i == j) continue;

                double distan = distance(planets[j].getPosition() + offset(planets[j].getRadius()), planets[i].getPosition() + offset(planets[i].getRadius())) * scalePhy;
                double a = (double)(G * (planets[j].getMass() * planets[i].getMass()) / pow(distan, 2)) / planets[j].getMass();
                planets[j].update(normalizeVector(planets[i], planets[j]), a);
            }
            planets[j].move();
            if (planets[j].getFocus())
            {
                world.setCenter(Vector2f((float)(planets[j].getPosition().x + planets[j].getRadius()), (float)(planets[j].getPosition().y + planets[j].getRadius())));
            }
        });
}
void gl::drawButtons(std::vector<Button>& buttons, RenderWindow& window)
{
    for (int i = 0; i < buttons.size(); i++)
    {
        buttons[i].draw(window);
    }
}
void gl::collisionPlanet(std::vector<Planet>& planets, std::vector<Button>& buttonsPlanet, RenderWindow& window, View& world, double scaleWorldinWindow)
{
    for (int j = 0; j < planets.size(); j++)
    {
        for (int i = 0; i < planets.size(); i++)
        {
            if (i == j) continue;

            if (distance(planets[i].getPosition() + offset(planets[i].getRadius()), planets[j].getPosition() + offset(planets[j].getRadius())) <= planets[i].getRadius() + planets[j].getRadius())
            {
                if (planets[i].getMass() > planets[j].getMass())
                {
                    planets[i].setMass(planets[i].getMass() + planets[j].getMass());
                    planets.erase(planets.begin() + j);
                    buttonsPlanet.erase(buttonsPlanet.begin() + j);
                    calculateButtonPlanet(buttonsPlanet, window, world, scaleWorldinWindow);
                }
                else if (planets[j].getMass() > planets[i].getMass())
                {
                    planets[j].setMass(planets[j].getMass() + planets[i].getMass());
                    planets.erase(planets.begin() + i);
                    buttonsPlanet.erase(buttonsPlanet.begin() + i);
                    calculateButtonPlanet(buttonsPlanet, window, world, scaleWorldinWindow);
                }
            }
        }
    }
}
void gl::generateButton(std::vector<Planet>& planets, std::vector<Button>& buttonsPlanet, std::vector<Button>& buttonsLogic,std::vector<RectangleShape>& namesPlanet, std::vector<Button>& buttonsInfo, RenderWindow& window)
{
    for (int i = 0; i < planets.size(); i++)
    {
        buttonsPlanet.push_back(Button(window.getSize().x / 76.8, 20.0f + window.getSize().y / 38.4 * i, window.getSize().x / 19.2, window.getSize().y / 64.0f, textureButton[i], textureNamesPlanet[i], 1.0f));
    }
    for (int i = 0; i < 8; i++)
    {
        buttonsLogic.push_back(Button(window.getSize().x / 38.4, window.getSize().y / 2.3 + window.getSize().y / 18.0f * i, window.getSize().x / 38.4, window.getSize().y / 21.6, textureButton[i + 9], "", 1.0f));
    }
    for (int i = 0; i < 8; i++)
    {
        buttonsInfo.push_back(Button(window.getSize().x / 17.5, window.getSize().y / 2.25 + window.getSize().y / 18.0f * i, window.getSize().x / 64, window.getSize().y / 36, textureButton[17], textureInfo[i], 1.0f));
    }
    for (int i = 0; i < planets.size(); i++) 
    {
        namesPlanet.push_back(RectangleShape(Vector2f(window.getSize().x / 21.8, window.getSize().y / 77.1)));
    }
}
void gl::genButtonMenu(std::vector<Button>& buttonsMass, std::vector<Button>& buttonsSpeed, std::vector<Button>& buttonsCamera, std::vector<Button>& buttonsCloceAndDelete,RenderWindow &window)
{
    buttonsCloceAndDelete.push_back(Button(window.getSize().x / 2.56, window.getSize().y / 1.46, window.getSize().x / 38.4, window.getSize().y / 21.6, textureButtonWindow[10], "", 1.0f));
    buttonsCloceAndDelete.push_back(Button(window.getSize().x / 1.745, window.getSize().y / 1.46, window.getSize().x / 38.4, window.getSize().y / 21.6, textureButton[16], "", 1.0f));
    buttonsCamera.push_back(Button(window.getSize().x / 2.16, window.getSize().y / 2.4, window.getSize().x / 38.4, window.getSize().y / 21.6, textureButtonWindow[8], "", 1.0f));
    buttonsCamera.push_back(Button(window.getSize().x / 2.02, window.getSize().y / 2.4, window.getSize().x / 38.4, window.getSize().y / 21.6, textureButtonWindow[9], "", 1.0f));
    buttonsMass.push_back(Button(window.getSize().x / 2.56, window.getSize().y / 3.375, window.getSize().x / 38.4, window.getSize().y / 43.2, textureButtonWindow[0], "", 0.1f));
    buttonsMass.push_back(Button(window.getSize().x / 2.37, window.getSize().y / 3.375, window.getSize().x / 38.4, window.getSize().y / 43.2, textureButtonWindow[1], "", 0.5f));
    buttonsMass.push_back(Button(window.getSize().x / 2.21, window.getSize().y / 3.375, window.getSize().x / 38.4, window.getSize().y / 43.2, textureButtonWindow[2], "", 2.0f));
    buttonsMass.push_back(Button(window.getSize().x / 2.06, window.getSize().y / 3.375, window.getSize().x / 38.4, window.getSize().y / 43.2, textureButtonWindow[3], "", 5.0f));
    buttonsMass.push_back(Button(window.getSize().x / 1.94, window.getSize().y / 3.375, window.getSize().x / 38.4, window.getSize().y / 43.2, textureButtonWindow[4], "", 10.0f));
    buttonsMass.push_back(Button(window.getSize().x / 1.83, window.getSize().y / 3.375, window.getSize().x / 38.4, window.getSize().y / 43.2, textureButtonWindow[7], "", -1.0f));
    buttonsSpeed.push_back(Button(window.getSize().x / 2.56, window.getSize().y / 2.77, window.getSize().x / 38.4, window.getSize().y / 43.2, textureButtonWindow[0], "", 0.1f));
    buttonsSpeed.push_back(Button(window.getSize().x / 2.37, window.getSize().y / 2.77, window.getSize().x / 38.4, window.getSize().y / 43.2, textureButtonWindow[1], "", 0.5f));
    buttonsSpeed.push_back(Button(window.getSize().x / 2.21, window.getSize().y / 2.77, window.getSize().x / 38.4, window.getSize().y / 43.2, textureButtonWindow[5], "", 1.2f));
    buttonsSpeed.push_back(Button(window.getSize().x / 2.06, window.getSize().y / 2.77, window.getSize().x / 38.4, window.getSize().y / 43.2, textureButtonWindow[6], "", 1.5f));
}
void gl::calculateButtonMenu(std::vector<Button>& buttonsMass, std::vector<Button>& buttonsSpeed, std::vector<Button>& buttonsCamera, std::vector<Button>& buttonsCloceAndDelete, RenderWindow& window, View& world, double& scaleWorldinWindow)
{
    window.setView(world);
    Vector2f CoordsButtonMass = window.mapPixelToCoords(Vector2i(window.getSize().x / 2.56, window.getSize().y / 3.375));
    Vector2f CoordsButtonSpeed = window.mapPixelToCoords(Vector2i(window.getSize().x / 2.56, window.getSize().y / 2.77));
    Vector2f CoordsButtonCamera = window.mapPixelToCoords(Vector2i(window.getSize().x / 2.16, window.getSize().y / 2.4));
    Vector2f CoordsButtonCloseAndDelete = window.mapPixelToCoords(Vector2i(window.getSize().x / 2.56, window.getSize().y / 1.46));
    for (int i = 0; i < buttonsMass.size(); i++) 
    {
        buttonsMass[i].setSize(Vector2f(window.getSize().x / 38.4 * scaleWorldinWindow, window.getSize().y / 43.2 * scaleWorldinWindow));
        buttonsMass[i].setPosition(Vector2f(CoordsButtonMass.x + window.getSize().x / 32.0f * scaleWorldinWindow * i, CoordsButtonMass.y));
    }
    for (int i = 0; i < buttonsSpeed.size(); i++)
    {
        buttonsSpeed[i].setSize(Vector2f(window.getSize().x / 38.4 * scaleWorldinWindow, window.getSize().y / 43.2 * scaleWorldinWindow));
        buttonsSpeed[i].setPosition(Vector2f(CoordsButtonSpeed.x + window.getSize().x / 32.0f * scaleWorldinWindow * i, CoordsButtonSpeed.y));
    }
    for (int i = 0; i < buttonsCamera.size(); i++)
    {
        buttonsCamera[i].setSize(Vector2f(window.getSize().x / 38.4 * scaleWorldinWindow, window.getSize().y / 21.6 * scaleWorldinWindow));
        buttonsCamera[i].setPosition(Vector2f(CoordsButtonCamera.x + window.getSize().x / 27.4 * scaleWorldinWindow * i, CoordsButtonCamera.y));
    }
    for (int i = 0; i < buttonsCloceAndDelete.size(); i++)
    {
        buttonsCloceAndDelete[i].setSize(Vector2f(window.getSize().x / 38.4 * scaleWorldinWindow, window.getSize().y / 21.6 * scaleWorldinWindow));
        buttonsCloceAndDelete[i].setPosition(Vector2f(CoordsButtonCloseAndDelete.x + window.getSize().x / 5.49 * scaleWorldinWindow * i, CoordsButtonCloseAndDelete.y));
    }
}