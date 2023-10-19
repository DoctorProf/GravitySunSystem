#include "../Headers/Global.h"
#include "../Headers/Texture.h"
#include <ppl.h>

using namespace sf;

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

void gl::setStyleText(Text &text, Font &font, Vector2f position)
{
    text.setFont(font);
    text.setFillColor(Color::White);
    text.setCharacterSize(18);
    text.setPosition(position.x, position.y);
}
bool gl::collisionButton(float x, float y, float sizeX, float sizeY, float mouseX, float mouseY)
{
    return (mouseX >= x && mouseX <= sizeX + x) && (mouseY >= y && mouseY <= sizeY + y);
}
void gl::spawnPlanet(std::vector<Planet>& planets, RenderWindow& window)
{
    planets.push_back(Planet(70, 2e30, Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f), Vector2f(0, 0.0), Color::Color(255, 255, 0), L"Солнце"));
    planets.push_back(Planet(0.3, 3.33e23, Vector2f(planets[0].getPosition().x + planets[0].getRadius() * 2 + 58, planets[0].getPosition().y + planets[0].getRadius()), Vector2f(0, 1.03), Color::Color(128, 128, 128), L"Меркурий"));
    planets.push_back(Planet(0.6, 4.87e24, Vector2f(planets[0].getPosition().x + planets[0].getRadius() * 2 + 108, planets[0].getPosition().y + planets[0].getRadius()), Vector2f(0, 0.9), Color::Color(234, 205, 177), L"Венера"));
    planets.push_back(Planet(0.6, 5.97e24, Vector2f(planets[0].getPosition().x + planets[0].getRadius() * 2 + 150, planets[0].getPosition().y + planets[0].getRadius()), Vector2f(0, 0.8), Color::Color(154, 205, 50), L"Земля"));
    planets.push_back(Planet(0.4, 6.42e23, Vector2f(planets[0].getPosition().x + planets[0].getRadius() * 2 + 228, planets[0].getPosition().y + planets[0].getRadius()), Vector2f(0, 0.68), Color::Color(228, 64, 3), L"Марс"));
    planets.push_back(Planet(7, 1.89e27, Vector2f(planets[0].getPosition().x + planets[0].getRadius() * 2 + 778, planets[0].getPosition().y + planets[0].getRadius()), Vector2f(0, -0.4), Color::Color(255, 226, 183), L"Юпитер"));
    planets.push_back(Planet(6, 5.68e26, Vector2f(planets[0].getPosition().x + planets[0].getRadius() * 2 + 1400, planets[0].getPosition().y + planets[0].getRadius()), Vector2f(0, -0.30), Color::Color(255, 219, 139), L"Сатурн"));
    planets.push_back(Planet(2.5, 8.68e25, Vector2f(planets[0].getPosition().x + planets[0].getRadius() * 2 + 2800, planets[0].getPosition().y + planets[0].getRadius()), Vector2f(0, -0.22), Color::Color(150, 229, 233), L"Уран"));
    planets.push_back(Planet(2.4, 1.024e26, Vector2f(planets[0].getPosition().x + planets[0].getRadius() * 2 + 4550, planets[0].getPosition().y + planets[0].getRadius()), Vector2f(0, -0.17), Color::Color(0, 0, 255), L"Нептун"));
}
void gl::calculatePanel(RectangleShape& panel, RectangleShape &panelInfo, RenderWindow& window, View& world, float& scaleWorldinWindow)
{
    window.setView(world);
    Vector2f panelCoords = window.mapPixelToCoords(Vector2i(0, 0));
    panel.setSize(Vector2f(window.getSize().x / 12.8 * scaleWorldinWindow, world.getSize().y));
    panel.setPosition(Vector2f(panelCoords.x, panelCoords.y));
    Vector2f panelInfoCoords = window.mapPixelToCoords(Vector2i(window.getSize().x / 1.19, 0));
    panelInfo.setSize(Vector2f(window.getSize().x / 6.4 * scaleWorldinWindow, window.getSize().y / 10.8 * scaleWorldinWindow));
    panelInfo.setPosition(Vector2f(panelInfoCoords.x, panelInfoCoords.y));
}
void gl::calculateBackground(RectangleShape& background, RenderWindow& window, View& world)
{
    window.setView(world);
    Vector2f backgroundCoords = window.mapPixelToCoords(Vector2i(0, 0));
    background.setPosition(Vector2f(backgroundCoords.x, backgroundCoords.y));
    background.setSize(Vector2f(world.getSize().x, world.getSize().y));
}
void gl::calculateButtonPlanet(std::vector<Button>& buttonsPlanet, RenderWindow& window, View& world, float& scaleWorldinWindow)
{
    window.setView(world);
    Vector2f buttonCoords = window.mapPixelToCoords(Vector2i(window.getSize().x / 76.8, window.getSize().y / 54));
    for (int i = 0; i < buttonsPlanet.size(); i++)
    {
        buttonsPlanet[i].setSize(Vector2f(window.getSize().x / 19.2 * scaleWorldinWindow, window.getSize().y / 36 * scaleWorldinWindow));
        buttonsPlanet[i].setPosition(Vector2f(buttonCoords.x, buttonCoords.y + window.getSize().y / 21.6 * scaleWorldinWindow * i));
    }
}
void gl::calculateButtonLogic(std::vector<Button>& buttonsLogic, std::vector<Button> &buttonsInfo, RenderWindow& window, View& world, float& scaleWorldinWindow)
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
        buttonsInfo[i].setSize(Vector2f(window.getSize().x / 64  * scaleWorldinWindow, window.getSize().y / 36 * scaleWorldinWindow));
        buttonsInfo[i].setPosition(Vector2f(buttonCoordsI.x, buttonCoordsI.y + window.getSize().y / 18 * scaleWorldinWindow * i));
    }
}
void gl::calculateNamesPlanet(std::vector<RectangleShape>& namesPlanet, RenderWindow& window, float& scaleWorldinWindow)
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
void gl::resetStatuButton(std::vector<Button>& buttons)
{
    for (int i = 0; i < buttons.size(); i++)
    {
        buttons[i].setStatus(false);
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
                world.setCenter(Vector2f(planets[j].getPosition().x + planets[j].getRadius(), planets[j].getPosition().y + planets[j].getRadius()));
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
void gl::collisionPlanet(std::vector<Planet>& planets, std::vector<Button>& buttonsPlanet, RenderWindow& window, View& world, float scaleWorldinWindow)
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
        buttonsPlanet.push_back(Button(window.getSize().x / 76.8, 20 + window.getSize().y / 38.4 * i, window.getSize().x / 19.2, window.getSize().y / 64, textureButton[i], textureNamesPlanet[i], 1));
    }
    for (int i = 0; i < 8; i++)
    {
        buttonsLogic.push_back(Button(window.getSize().x / 38.4, window.getSize().y / 2.3 + window.getSize().y / 18 * i, window.getSize().x / 38.4, window.getSize().y / 21.6, textureButton[i + 9], "", 1));
    }
    for (int i = 0; i < 8; i++)
    {
        buttonsInfo.push_back(Button(window.getSize().x / 17.5, window.getSize().y / 2.25 + window.getSize().y / 18 * i, window.getSize().x / 64, window.getSize().y / 36, textureButton[17], textureInfo[i], 1));
    }
    for (int i = 0; i < planets.size(); i++) 
    {
        namesPlanet.push_back(RectangleShape(Vector2f(window.getSize().x / 21.8, window.getSize().y / 77.1)));
    }
}

