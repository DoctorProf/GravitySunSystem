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
bool gl::collisionButton(float x, float y, float sizeX, float sizeY, float mouseX, float mouseY)
{
    return (mouseX >= x && mouseX <= sizeX + x) && (mouseY >= y && mouseY <= sizeY + y);
}
void gl::setStyleText(Text& text, Font& font)
{
    text.setFont(font);
    text.setFillColor(Color::White);
    text.setCharacterSize(20);
}
void gl::spawnPlanet(std::vector<Planet>& planets, RenderWindow& window)
{
    planets.push_back(Planet(7.0f, 2e30, Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f), Vector2f(0, 0), Color::Color(255, 255, 0), L"������", 2.46e12));
    planets.push_back(Planet(0.03, 3.33e23, Vector2f(planets[0].getPosition().x + planets[0].getRadius() * 2 + 58, planets[0].getPosition().y + planets[0].getRadius()), Vector2f(0, 1.4), Color::Color(209, 159, 120), L"��������", 58));
    planets.push_back(Planet(0.06, 4.87e24, Vector2f(planets[0].getPosition().x + planets[0].getRadius() * 2 + 108, planets[0].getPosition().y + planets[0].getRadius()), Vector2f(0, 1.07), Color::Color(167, 92, 21), L"������", 108));
    planets.push_back(Planet(0.06, 5.97e24, Vector2f(planets[0].getPosition().x + planets[0].getRadius() * 2 + 150, planets[0].getPosition().y + planets[0].getRadius()), Vector2f(0, 0.9), Color::Color(85, 118, 145), L"�����", 150));
    planets.push_back(Planet(0.04, 6.42e23, Vector2f(planets[0].getPosition().x + planets[0].getRadius() * 2 + 228, planets[0].getPosition().y + planets[0].getRadius()), Vector2f(0, 0.74), Color::Color(255, 0, 0), L"����", 228));
    planets.push_back(Planet(0.7f, 1.89e27, Vector2f(planets[0].getPosition().x + planets[0].getRadius() * 2 + 778, planets[0].getPosition().y + planets[0].getRadius()), Vector2f(0, -0.40), Color::Color(172, 153, 128), L"������", 778));
    planets.push_back(Planet(0.6f, 5.68e26, Vector2f(planets[0].getPosition().x + planets[0].getRadius() * 2 + 1400, planets[0].getPosition().y + planets[0].getRadius()), Vector2f(0, -0.30), Color::Color(222, 189, 110), L"������", 1400));
    planets.push_back(Planet(0.25f, 8.68e25, Vector2f(planets[0].getPosition().x + planets[0].getRadius() * 2 + 2800, planets[0].getPosition().y + planets[0].getRadius()), Vector2f(0, -0.22), Color::Color(111, 231, 234), L"����", 2800));
    planets.push_back(Planet(0.24f, 1.024e26, Vector2f(planets[0].getPosition().x + planets[0].getRadius() * 2 + 4550, planets[0].getPosition().y + planets[0].getRadius()), Vector2f(0, -0.17), Color::Color(0, 0, 255), L"������", 4550));
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
                if (abs(planets[i].getMass()) > abs(planets[j].getMass()))
                {
                    planets[i].setMass(planets[i].getMass() + planets[j].getMass());
                    planets[i].setVelocity((planets[i].getVelocity() * (float)planets[i].getMass() + planets[j].getVelocity() * (float)planets[j].getMass()) / (float)planets[i].getMass());
                    planets.erase(planets.begin() + j);
                    buttonsPlanet.erase(buttonsPlanet.begin() + j);
                }
                else if (abs(planets[j].getMass()) > abs(planets[i].getMass()))
                {
                    planets[j].setMass(planets[j].getMass() + planets[i].getMass());
                    planets[j].setVelocity((planets[i].getVelocity() * (float)planets[i].getMass() + planets[j].getVelocity() * (float)planets[j].getMass()) / (float)planets[j].getMass());
                    planets.erase(planets.begin() + i);
                    buttonsPlanet.erase(buttonsPlanet.begin() + i);
                }
            }
        }
    }
}
void gl::generateButton(std::vector<Planet>& planets, std::vector<Button>& buttonsPlanet, std::vector<Button>& buttonsLogic,std::vector<RectangleShape>& namesPlanet, RenderWindow& window)
{
    for (int i = 0; i < planets.size(); i++)
    {
        buttonsPlanet.push_back(Button(window.getSize().x / 76.8, window.getSize().y / 54.0f + window.getSize().y / 21.6 * i, window.getSize().x / 19.2, window.getSize().y / 36.0f, textureButtonPlanet[i], textureNamesPlanet[i], 1.0f));
    }
    for (int i = 0; i < 9; i++)
    {
        buttonsLogic.push_back(Button(window.getSize().x / 38.4, window.getSize().y / 2.3 + window.getSize().y / 18.0f * i, window.getSize().x / 38.4, window.getSize().y / 21.6, textureButtonLogic[i], textureInfo[i], 1.0f));
    }
    for (int i = 0; i < planets.size(); i++) 
    {
        namesPlanet.push_back(RectangleShape(Vector2f(window.getSize().x / 21.8, window.getSize().y / 77.1)));
    }
}
void gl::genButtonMenu(std::vector<Button>& buttonsMass, std::vector<Button>& buttonsSpeed, std::vector<Button>& buttonsLogicPanelPlanet,RenderWindow &window)
{
    buttonsLogicPanelPlanet.push_back(Button(window.getSize().x / 1.247, window.getSize().y / 1.069, window.getSize().x / 38.4, window.getSize().y / 21.6, textureButtonLogic[11], textureInfo[9], 1.0f));
    buttonsLogicPanelPlanet.push_back(Button(window.getSize().x / 1.247 + window.getSize().x / 25.6f, window.getSize().y / 1.069, window.getSize().x / 38.4, window.getSize().y / 21.6, textureButtonLogic[9], textureInfo[12], 1.0f));
    buttonsLogicPanelPlanet.push_back(Button(window.getSize().x / 1.247 + window.getSize().x / 12.8f, window.getSize().y / 1.069, window.getSize().x / 38.4, window.getSize().y / 21.6, textureButtonLogic[10], textureInfo[13], 1.0f));
    buttonsLogicPanelPlanet.push_back(Button(window.getSize().x / 1.247 + window.getSize().x / 8.5f, window.getSize().y / 1.069, window.getSize().x / 38.4, window.getSize().y / 21.6, textureButtonLogic[12], textureInfo[10], 1.0f));
    buttonsLogicPanelPlanet.push_back(Button(window.getSize().x / 1.247 + window.getSize().x / 6.4f, window.getSize().y / 1.069, window.getSize().x / 38.4, window.getSize().y / 21.6, textureButtonLogic[8], textureInfo[11], 1.0f));
    buttonsMass.push_back(Button(window.getSize().x / 1.247, window.getSize().y / 1.27, window.getSize().x / 38.4, window.getSize().y / 43.2, textureButtonPanel[0], "", 0.1f));
    buttonsMass.push_back(Button(window.getSize().x / 1.247 + window.getSize().x / 32.0f, window.getSize().y / 1.27, window.getSize().x / 38.4, window.getSize().y / 43.2, textureButtonPanel[1], "", 0.5f));
    buttonsMass.push_back(Button(window.getSize().x / 1.247 + window.getSize().x / 16.0f, window.getSize().y / 1.27, window.getSize().x / 38.4, window.getSize().y / 43.2, textureButtonPanel[2], "", 2.0f));
    buttonsMass.push_back(Button(window.getSize().x / 1.247 + window.getSize().x / 10.7f, window.getSize().y / 1.27, window.getSize().x / 38.4, window.getSize().y / 43.2, textureButtonPanel[3], "", 5.0f));
    buttonsMass.push_back(Button(window.getSize().x / 1.247 + window.getSize().x / 8.0f, window.getSize().y / 1.27, window.getSize().x / 38.4, window.getSize().y / 43.2, textureButtonPanel[4], "", 10.0f));
    buttonsMass.push_back(Button(window.getSize().x / 1.247 + window.getSize().x / 6.4f, window.getSize().y / 1.27, window.getSize().x / 38.4, window.getSize().y / 43.2, textureButtonPanel[5], "", -1.0f));
    buttonsSpeed.push_back(Button(window.getSize().x / 1.247, window.getSize().y / 1.187, window.getSize().x / 38.4, window.getSize().y / 43.2, textureButtonPanel[1], "", 0.5f));
    buttonsSpeed.push_back(Button(window.getSize().x / 1.247 + window.getSize().x / 32.0f, window.getSize().y / 1.187, window.getSize().x / 38.4, window.getSize().y / 43.2, textureButtonPanel[6], "", 0.7f));
    buttonsSpeed.push_back(Button(window.getSize().x / 1.247 + window.getSize().x / 16.0f, window.getSize().y / 1.187, window.getSize().x / 38.4, window.getSize().y / 43.2, textureButtonPanel[7], "", 0.9f));
    buttonsSpeed.push_back(Button(window.getSize().x / 1.247 + window.getSize().x / 10.7f, window.getSize().y / 1.187, window.getSize().x / 38.4, window.getSize().y / 43.2, textureButtonPanel[8], "", 1.1f));
    buttonsSpeed.push_back(Button(window.getSize().x / 1.247 + window.getSize().x / 8.0f, window.getSize().y / 1.187, window.getSize().x / 38.4, window.getSize().y / 43.2, textureButtonPanel[9], "", 1.3f));
    buttonsSpeed.push_back(Button(window.getSize().x / 1.247 + window.getSize().x / 6.4f, window.getSize().y / 1.187, window.getSize().x / 38.4, window.getSize().y / 43.2, textureButtonPanel[10], "", 0.0f));
}