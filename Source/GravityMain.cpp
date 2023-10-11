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

    for (int i = 0; i < planets.size(); i++)
    {
        Vector2f buttonCoords = window.mapPixelToCoords(Vector2i(25, 20));
        buttonsPlanet.push_back(Button(25, 20 + 50 * i, 100, 30, planets[i].getName(), textureButton[i]));
    }
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
                spawnPlanet(planets, window);
            }
            else if (event.type == Event::KeyReleased && event.key.code == Keyboard::Space)
            {
                pause = !pause;
            }
            else if (event.type == Event::KeyPressed && event.key.code == Keyboard::W)
            {
                world.move(0, -50);
            } 
            else if (event.type == Event::KeyPressed && event.key.code == Keyboard::S)
            {
                world.move(0, 50);
            }
            else if (event.type == Event::KeyPressed && event.key.code == Keyboard::A)
            {
                world.move(-50, 0);
            }
            else if (event.type == Event::KeyPressed && event.key.code == Keyboard::D)
            {
                world.move(50, 0);
            }
            else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Numpad8)
            {
                world.setSize(world.getSize().x * 2, world.getSize().y * 2);
            }
            else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Numpad2)
            {
                world.setSize(world.getSize().x / 2, world.getSize().y / 2);
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
                            RenderWindow windowSettings(VideoMode(500, 600), buttonsPlanet[i].getName());
                            Text textMass;
                            Text textSpeed;
                            std::ostringstream massE;
                            std::vector<Button> buttonsMass;
                            std::vector<Button> buttonsSpeed;
                            setStyleText(textMass, font, Vector2f(50, 30));
                            setStyleText(textSpeed, font, Vector2f(50, 90));
                            
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
                                    /*else if (event1.type == Event::MouseButtonPressed) 
                                    {
                                        if (event1.mouseButton.button == Mouse::Left) 
                                        {
                                            for (int j = 0; j < buttonsMass.size(); j++)
                                            {
                                                if (buttonsMass[j].collisionButton(event1.mouseButton.x, event1.mouseButton.y))
                                                {
                                                    planets[i].setMass(planets[i].getMass() * boost::lexical_cast<double>(buttonsMass[j].getName()));
                                                }
                                            }
                                            for (int j = 0; j < buttonsSpeed.size(); j++)
                                            {
                                                if (buttonsSpeed[j].collisionButton(event1.mouseButton.x, event1.mouseButton.y))
                                                {
                                                    planets[i].setVelocity(Vector2f(planets[i].getVelocity().x * boost::lexical_cast<double>(buttonsSpeed[j].getName()), planets[i].getVelocity().y * boost::lexical_cast<double>(buttonsSpeed[j].getName())));
                                                }
                                            }
                                        }
                                    }*/
                                }   
                                massE << std::scientific << std::setprecision(2) << planets[i].getMass();
                                textMass.setString(L"Масса  " + massE.str());
                                textSpeed.setString(L"Скорость - ( " + std::to_string(planets[i].getVelocity().x) + ", " + std::to_string(planets[i].getVelocity().y) + " )");
                                windowSettings.clear(Color::Black);
                                windowSettings.draw(textMass);
                                windowSettings.draw(textSpeed);
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
                        }
                        else if (planets[j].getMass() > planets[i].getMass())
                        {
                            planets[j].setMass(planets[j].getMass() + planets[i].getMass());
                            planets.erase(planets.begin() + i);
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
                        Vertex pos;
                        pos.position = Vector2f(planets[i].getPosition().x + planets[i].getRadius(), planets[i].getPosition().y + planets[i].getRadius());
                        pos.color = Color::Color(planets[i].getColor().r, planets[i].getColor().g, planets[i].getColor().b, planets[i].getColor().a / 2);
                        planets[i].addTrack(pos);
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
                planets[i].drawPlanet(window);
            }
            
            if (previousWorldSize != world.getSize())
            {
                Vector2f panelCoords = window.mapPixelToCoords(Vector2i(0, 0));
                Vector2f buttonCoords = window.mapPixelToCoords(Vector2i(25, 20));
                panel.setSize(Vector2f(150 * scaleWorldinWindow, world.getSize().y));
                panel.setPosition(Vector2f(panelCoords.x, panelCoords.y));
                for (int i = 0; i < buttonsPlanet.size(); i++)
                {
                    buttonsPlanet[i].setSize(Vector2f(100 * scaleWorldinWindow, 30 * scaleWorldinWindow));
                    buttonsPlanet[i].setPosition(Vector2f(buttonCoords.x, buttonCoords.y + 50 * scaleWorldinWindow * i));
                }
                previousWorldSize = world.getSize();
            }
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
