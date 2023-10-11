#include "../Headers/Global.h"
#include "../Headers/Button.h"
#include "../Headers/Texture.h"
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <ppl.h>
#include <cstdlib>
#include <boost/lexical_cast.hpp>

using namespace sf;
using namespace global;
using namespace Concurrency;

void spawnPlanet(std::vector<Planet>& planets, RenderWindow& window)
{
    planets.push_back(Planet(70, 2e30, Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f), Vector2f(0, 0.0), Color::Color(255, 255, 0), "Sun"));
    planets.push_back(Planet(0.3, 3.33e23, Vector2f(planets[0].getPosition().x + planets[0].getRadius() * 2 + 58, planets[0].getPosition().y + planets[0].getRadius()), Vector2f(0, 1.03), Color::Color(128, 128, 128), "Mercury"));
    planets.push_back(Planet(0.6, 4.87e24, Vector2f(planets[0].getPosition().x + planets[0].getRadius() * 2 + 108, planets[0].getPosition().y + planets[0].getRadius()), Vector2f(0, 0.9), Color::Color(234, 205, 177), "Venus"));
    planets.push_back(Planet(0.6, 5.97e24, Vector2f(planets[0].getPosition().x + planets[0].getRadius() * 2 + 150, planets[0].getPosition().y + planets[0].getRadius()), Vector2f(0, 0.8), Color::Color(154, 205, 50), "Earth"));
    planets.push_back(Planet(0.4, 6.42e23, Vector2f(planets[0].getPosition().x + planets[0].getRadius() * 2 + 228, planets[0].getPosition().y + planets[0].getRadius()), Vector2f(0, 0.68), Color::Color(228, 64, 3), "Mars"));
    planets.push_back(Planet(7, 1.89e27, Vector2f(planets[0].getPosition().x + planets[0].getRadius() * 2 + 778, planets[0].getPosition().y + planets[0].getRadius()), Vector2f(0, -0.4), Color::Color(255, 226, 183), "Jupiter"));
    planets.push_back(Planet(6, 5.68e26, Vector2f(planets[0].getPosition().x + planets[0].getRadius() * 2 + 1400, planets[0].getPosition().y + planets[0].getRadius()), Vector2f(0, -0.30), Color::Color(255, 219, 139), "Saturn"));
    planets.push_back(Planet(2.5, 8.68e25, Vector2f(planets[0].getPosition().x + planets[0].getRadius() * 2 + 2800, planets[0].getPosition().y + planets[0].getRadius()), Vector2f(0, -0.22), Color::Color(150, 229, 233), "Uranus"));
    planets.push_back(Planet(2.4, 1.024e26, Vector2f(planets[0].getPosition().x + planets[0].getRadius() * 2 + 4550, planets[0].getPosition().y + planets[0].getRadius()), Vector2f(0, -0.17), Color::Color(0, 0, 255), "Neptune"));
}
void calculatePanel(RectangleShape &panel, std::vector<Button> &buttonsPlanet, RenderWindow &window, View &world, float &scaleWorldinWindow)
{
    window.setView(world);
    Vector2f panelCoords = window.mapPixelToCoords(Vector2i(0, 0));
    Vector2f buttonCoords = window.mapPixelToCoords(Vector2i(25, 20));
    panel.setSize(Vector2f(150 * scaleWorldinWindow, world.getSize().y));
    panel.setPosition(Vector2f(panelCoords.x, panelCoords.y));
    for (int i = 0; i < buttonsPlanet.size(); i++)
    {
        buttonsPlanet[i].setSize(Vector2f(100 * scaleWorldinWindow, 30 * scaleWorldinWindow));
        buttonsPlanet[i].setPosition(Vector2f(buttonCoords.x, buttonCoords.y + 50 * scaleWorldinWindow * i));
    }
}
void generateButtonPlanet(std::vector<Planet> &planets,std::vector<Button> &buttonsPlanet, RenderWindow &window) 
{
    for (int i = 0; i < planets.size(); i++)
    {
        Vector2f buttonCoords = window.mapPixelToCoords(Vector2i(25, 20));
        buttonsPlanet.push_back(Button(25, 20 + 50 * i, 100, 30, textureButton[i], 1));
    }
}
int main() 
{
    View world;
    world.setCenter(Vector2f(960, 540));
    world.setSize(Vector2f(1920, 1080));
    RenderWindow window(VideoMode(1920, 1080), "Gravity");
    std::setlocale(LC_ALL, "rus");
    Font font;
    font.loadFromFile("C:\\windows\\fonts\\arial.ttf");
    bool pause = false;
    bool trackDraw = true;
    Clock clock;
    Clock clock2;
    Clock clock3;
    Time interval = seconds(0.02);
    std::vector<Planet> planets;
    std::vector<Button> buttonsPlanet;
    Vector2f previousWorldSize = world.getSize();
    RectangleShape panel;
    panel.setFillColor(Color::Color(25,25,25));
    panel.setSize(Vector2f(150, world.getSize().y));
    panel.setPosition(Vector2f(0, 0));
    float scaleWorldinWindow = world.getSize().x / window.getSize().x;
    const float G = 6.67e-11;
    double scalePhy = 1e9;
    const int frameRate = 120;
    Time accumulatedTime = Time::Zero;
    Time accumulatedTime2 = Time::Zero;

    bool unlimited_fps = false;

    Time timePerFrame = seconds(1.0f / frameRate); // tps
    Time timePerFrame2 = seconds(1.0f / frameRate); // fps

    spawnPlanet(std::ref(planets), window);
    generateButtonPlanet(planets, buttonsPlanet, window);
    
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
            else if (event.type == Event::KeyReleased && event.key.code == Keyboard::T)
            {
                trackDraw = !trackDraw;
                for (int i = 0; i < planets.size(); i++)
                {
                    planets[i].clearTrack();
                }
            }
            else if (event.type == Event::KeyReleased && event.key.code == Keyboard::Delete)
            {
                world.setSize(1920, 1080);
                world.setCenter(Vector2f(960, 540));
                planets.clear();
                buttonsPlanet.clear();
                spawnPlanet(planets, window);
                generateButtonPlanet(planets, buttonsPlanet, window);
            }
            else if (event.type == Event::KeyReleased && event.key.code == Keyboard::Space)
            {
                pause = !pause;
            }
            else if (event.type == Event::KeyPressed && event.key.code == Keyboard::W)
            {
                world.move(0, -25);
                calculatePanel(panel, buttonsPlanet, window, world, scaleWorldinWindow);
            } 
            else if (event.type == Event::KeyPressed && event.key.code == Keyboard::S)
            {
                world.move(0, 25);
                calculatePanel(panel, buttonsPlanet, window, world, scaleWorldinWindow);
            }
            else if (event.type == Event::KeyPressed && event.key.code == Keyboard::A)
            {
                world.move(-25, 0);
                calculatePanel(panel, buttonsPlanet, window, world, scaleWorldinWindow);
            }
            else if (event.type == Event::KeyPressed && event.key.code == Keyboard::D)
            {
                world.move(25, 0);
                calculatePanel(panel, buttonsPlanet, window, world, scaleWorldinWindow);
            }
            else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Numpad8)
            {
                world.setSize(world.getSize().x * 2, world.getSize().y * 2);
                break;
            }
            else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Numpad2)
            {
                world.setSize(world.getSize().x / 2, world.getSize().y / 2);
                break;
            }
            else if (event.type == Event::MouseButtonPressed) 
            {
                if (event.mouseButton.button == Mouse::Left) 
                {
                    /*Vector2i x = window.mapCoordsToPixel(Vector2f(buttonsPlanet[0].getPosition().x, buttonsPlanet[0].getPosition().y));
                    std::cout << "Корды мыши (" << event.mouseButton.x << "," << event.mouseButton.y << ")" << "\n" << "Корды кнопки (" << x.x << "," << x.y << ")" << "\n"
                        << "Размеры кнопки (" << buttonsPlanet[0].getSize().x << "," << buttonsPlanet[0].getSize().y << ")" << "\n";*/
                    for (int i = 0; i < buttonsPlanet.size(); i++) 
                    {
                        Vector2i buttonCoor = window.mapCoordsToPixel(Vector2f(buttonsPlanet[i].getPosition().x, buttonsPlanet[i].getPosition().y));
                        if (collisionButton(buttonCoor.x, buttonCoor.y, buttonsPlanet[i].getSize().x / scaleWorldinWindow, buttonsPlanet[i].getSize().y/ scaleWorldinWindow, event.mouseButton.x, event.mouseButton.y))
                        {
                            pause = true;
                            RenderWindow windowSettings(VideoMode(500, 600), planets[i].getName());
                            Text textMass;
                            Text textSpeed;
                            Text textCamera;
                            std::ostringstream massE;
                            std::vector<Button> buttonsMass;
                            std::vector<Button> buttonsSpeed;
                            Button buttonCamera(220, 190, 50, 50, textureButtonWindow[7], 1);
                            setStyleText(textMass, font, Vector2f(50, 30));
                            setStyleText(textSpeed, font, Vector2f(50, 90));
                            setStyleText(textCamera, font, Vector2f(150, 160));
                            buttonsMass.push_back(Button(50, 60, 50, 25, textureButtonWindow[0], 0.1f));
                            buttonsMass.push_back(Button(110, 60, 50, 25, textureButtonWindow[1], 0.5f));
                            buttonsMass.push_back(Button(170, 60, 50, 25, textureButtonWindow[2], 2.0f));
                            buttonsMass.push_back(Button(230, 60, 50, 25, textureButtonWindow[3], 5.0f));
                            buttonsMass.push_back(Button(290, 60, 50, 25, textureButtonWindow[4], 10.0f));
                            buttonsSpeed.push_back(Button(50, 120, 50, 25, textureButtonWindow[0], 0.1f));
                            buttonsSpeed.push_back(Button(110, 120, 50, 25, textureButtonWindow[1], 0.5f));
                            buttonsSpeed.push_back(Button(170, 120, 50, 25, textureButtonWindow[5], 1.2f));
                            buttonsSpeed.push_back(Button(230, 120, 50, 25, textureButtonWindow[6], 1.5f));
                            
                            while (windowSettings.isOpen()) {
                                Event event1;
                                while (windowSettings.pollEvent(event1))
                                {
                                    if (event1.type == Event::KeyReleased && event1.key.code == Keyboard::Escape)
                                    {
                                        windowSettings.close();
                                        pause = false;
                                        clock.restart();
                                    }
                                    else if (event1.type == Event::Closed)
                                    {
                                        windowSettings.close();
                                        pause = false;
                                        clock.restart();
                                    }
                                    else if (event1.type == Event::MouseButtonPressed) 
                                    {
                                        if (event1.mouseButton.button == Mouse::Left) 
                                        {
                                            for (int j = 0; j < buttonsMass.size(); j++)
                                            {
                                                if (collisionButton(buttonsMass[j].getPosition().x, buttonsMass[j].getPosition().y, buttonsMass[j].getSize().x,
                                                    buttonsMass[j].getSize().y, event1.mouseButton.x, event1.mouseButton.y))
                                                {
                                                    planets[i].setMass(planets[i].getMass() * buttonsMass[j].getCoeff());
                                                }
                                            }
                                            for (int j = 0; j < buttonsSpeed.size(); j++)
                                            {
                                                if (collisionButton(buttonsSpeed[j].getPosition().x, buttonsSpeed[j].getPosition().y, buttonsSpeed[j].getSize().x,
                                                    buttonsSpeed[j].getSize().y, event1.mouseButton.x, event1.mouseButton.y))
                                                {
                                                    planets[i].setVelocity(Vector2f(planets[i].getVelocity().x * buttonsSpeed[j].getCoeff(), planets[i].getVelocity().y * buttonsSpeed[j].getCoeff()));
                                                }
                                            }
                                            if (collisionButton(buttonCamera.getPosition().x, buttonCamera.getPosition().y, buttonCamera.getSize().x, buttonCamera.getSize().y,
                                                event1.mouseButton.x, event1.mouseButton.y)) 
                                            {
                                                planets[i].setFocus(true);
                                            }
                                        }
                                    }
                                }   
                                massE << std::scientific << std::setprecision(2) << planets[i].getMass();
                                textMass.setString(L"Масса  " + massE.str());
                                textSpeed.setString(L"Скорость < " + std::to_string(planets[i].getVelocity().x) + ", " + std::to_string(planets[i].getVelocity().y) + " >");
                                textCamera.setString(L"Зафиксировать камеру");
                                windowSettings.clear(Color::Black);
                                windowSettings.draw(textMass);
                                windowSettings.draw(textSpeed);
                                windowSettings.draw(textCamera);
                                for (int j = 0; j < buttonsMass.size(); j++) 
                                {
                                    buttonsMass[j].draw(windowSettings);
                                }
                                for (int j = 0; j < buttonsSpeed.size(); j++)
                                {
                                    buttonsSpeed[j].draw(windowSettings);
                                }
                                buttonCamera.draw(windowSettings);
                                windowSettings.display();
                                massE.str("");
                            }
                        }
                    }
                }
            }
        }
        scaleWorldinWindow = world.getSize().x / window.getSize().x;
        accumulatedTime += clock.restart();
        while (accumulatedTime >= timePerFrame)
        {
            accumulatedTime -= timePerFrame;
            if (pause) continue;
            for (int j = 0; j < planets.size(); j++)
            {
                for (int i = 0; i < planets.size(); i++)
                {
                    if (i == j) continue;

                    if(distance(planets[i].getPosition() + offset(planets[i].getRadius()), planets[j].getPosition() + offset(planets[j].getRadius())) <= planets[i].getRadius() + planets[j].getRadius())
                    {
                        if (planets[i].getMass() > planets[j].getMass()) 
                        {
                            planets[i].setMass(planets[i].getMass() + planets[j].getMass());
                            planets.erase(planets.begin() + j);
                            buttonsPlanet.erase(buttonsPlanet.begin() + j);
                            calculatePanel(panel, buttonsPlanet, window, world, scaleWorldinWindow);
                        }
                        else if (planets[j].getMass() > planets[i].getMass())
                        {
                            planets[j].setMass(planets[j].getMass() + planets[i].getMass());
                            planets.erase(planets.begin() + i);
                            buttonsPlanet.erase(buttonsPlanet.begin() + i);
                            calculatePanel(panel, buttonsPlanet, window, world, scaleWorldinWindow);
                        }
                    }
                }
            }
            parallel_for(0, (int)planets.size(), [&](int j)
                {
                    for (int i = 0; i < planets.size(); i++)
                    {
                        if (i == j) continue;

                        double distan = distance(planets[j].getPosition() + offset(planets[j].getRadius()), planets[i].getPosition() + offset(planets[i].getRadius())) * scalePhy;
                        double a = (double)(G * (planets[j].getMass() * planets[i].getMass()) / pow(distan, 2)) / planets[j].getMass();
                        planets[j].update(normalizeVector(planets[i], planets[j]), a);
                    }
                    planets[j].move();
                });
        }
        accumulatedTime2 += clock2.restart();
        if (unlimited_fps || accumulatedTime2 >= timePerFrame2)
        {
            window.setView(world);
            window.clear(Color::Black);

            if (trackDraw)
            {
                Time time = clock3.getElapsedTime();
                if (time >= interval)
                {
                    for (int i = 0; i < planets.size(); i++)
                    {
                        planets[i].addTrack();
                    }
                    clock3.restart();
                }
            }
            for (int i = 0; i < planets.size(); i++)
            {
                planets[i].drawTrack(window);
            }
            for (int i = 0; i < planets.size(); i++)
            {
                if (planets[i].getFocus())
                {
                    world.setCenter(Vector2f(planets[i].getPosition().x + planets[i].getRadius(), planets[i].getPosition().y + planets[i].getRadius()));
                }
                planets[i].drawPlanet(window); 
            }
            
            calculatePanel(panel, buttonsPlanet, window, world, scaleWorldinWindow);
            window.draw(panel);
            for (int i = 0; i < buttonsPlanet.size(); i++)
            {
                buttonsPlanet[i].draw(window);
            }
            window.display();
            accumulatedTime2 -= timePerFrame2;
        }
    }
    return 0;
}
