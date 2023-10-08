#include "../Headers/Global.hpp"
#include "../Headers/Button.hpp"
#include "SFML/Audio.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <ppl.h>

using namespace sf;
using namespace global;
using namespace Concurrency;

int main() 
{
    View world;
    world.setCenter(Vector2f(960, 540));
    world.setSize(Vector2f(5760, 3240));
    RenderWindow window(VideoMode(1920, 1080), "Gravity");
    std::setlocale(LC_ALL, "rus");

    Font font;
    font.loadFromFile("C:\\windows\\fonts\\arial.ttf");
    bool pause = false;
    bool trackDraw = false;
    Clock clock;
    Clock clock2;
    Clock clock3;
    Time interval = seconds(0.1);
    std::vector<Planet> planets;
    const float G = 6.67e-11;
    bool run = true;
    double scalePhy = 1e9;
    const int frameRate = 120;
    Time accumulatedTime = Time::Zero;
    Time accumulatedTime2 = Time::Zero;

    bool unlimited_fps = false;

    Time timePerFrame = seconds(1.0f / frameRate); // tps
    Time timePerFrame2 = seconds(1.0f / frameRate); // fps
    spawnPlanet(std::ref(planets), window);

    while (run) {
        Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == Event::Closed)
            {
                run = false;
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
                    for (int i = 0; i < planets.size(); i++) 
                    {
                        Vector2i worldCoords = Vector2i(event.mouseButton.x, event.mouseButton.y);
                        Vector2i viewPlanetPosition = window.mapCoordsToPixel(Vector2f(planets[i].getPosition().x + planets[i].getRadius(), planets[i].getPosition().y + planets[i].getRadius()));
                        if (pow(worldCoords.x - viewPlanetPosition.x, 2) + pow(worldCoords.y - viewPlanetPosition.y, 2) <= pow(planets[i].getRadius(), 2))
                        {
                            pause = true;
                            RenderWindow windowSettings(VideoMode(500, 600), planets[i].getName());
                            Text textMass;
                            Text textSpeed;
                            std::ostringstream massE;
                            std::vector<Button> buttonsMass;
                            std::vector<Button> buttonsSpeed;
                            setStyleText(textMass, font, Vector2f(50, 30));
                            setStyleText(textSpeed, font, Vector2f(50, 90));
                            buttonsMass.push_back(Button(50, 60, 50, 30, 0.5));
                            buttonsMass.push_back(Button(150, 60, 50, 30, 2));
                            buttonsMass.push_back(Button(240, 60, 50, 30, 10));
                            buttonsSpeed.push_back(Button(50, 120, 50, 30, 0.75));
                            buttonsSpeed.push_back(Button(150, 120, 50, 30, 1.25));
                            buttonsSpeed.push_back(Button(240, 120, 50, 30, 1.5));
                            
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
                                                if (buttonsMass[j].collisionButton(event1.mouseButton.x, event1.mouseButton.y))
                                                {
                                                    planets[i].setMass(planets[i].getMass() * (double)buttonsMass[j].getcoeff());
                                                }
                                            }
                                            for (int j = 0; j < buttonsSpeed.size(); j++)
                                            {
                                                if (buttonsSpeed[j].collisionButton(event1.mouseButton.x, event1.mouseButton.y))
                                                {
                                                    planets[i].setVelocity(Vector2f(planets[i].getVelocity().x * (double)buttonsSpeed[j].getcoeff(), planets[i].getVelocity().y * (double)buttonsSpeed[j].getcoeff()));
                                                }
                                            }
                                        }
                                    }
                                }   
                                massE << std::scientific << std::setprecision(2) << planets[i].getMass();
                                textMass.setString(L"Масса  " + massE.str());
                                textSpeed.setString(L"Скорость - ( " + std::to_string(planets[i].getVelocity().x) + ", " + std::to_string(planets[i].getVelocity().y) + " )");
                                windowSettings.clear(Color::Black);
                                windowSettings.draw(textMass);
                                windowSettings.draw(textSpeed);
                                for (int j = 0; j < buttonsMass.size(); j++)
                                {
                                    buttonsMass[j].draw(windowSettings, font);
                                }
                                for (int j = 0; j < buttonsSpeed.size(); j++)
                                {
                                    buttonsSpeed[j].draw(windowSettings, font);
                                }
                                windowSettings.display();
                                massE.str("");
                            }
                        }
                    }
                }
                else if (event.mouseButton.button == Mouse::Right) 
                {
                    Vector2f mouseCoords = window.mapPixelToCoords(Vector2i(event.mouseButton.x, event.mouseButton.y));
                    planets.push_back(Planet(30, 940e18, mouseCoords, Vector2f(0.6, 0), Color::Color(128, 128, 128), "BlackHole"));
                }
            }
        }
           
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
            /*
            for (int j = 0; j < planets.size(); j++)
            {
                for (int i = 0; i < planets.size(); i++)
                {
                    if (i == j) continue;

                    double distan = distance(planets[j].getPosition() + offset(planets[j].getRadius()), planets[i].getPosition() + offset(planets[i].getRadius())) * 1e9;
                    double a = (double)(G * (planets[j].getMass() * planets[i].getMass()) / pow(distan, 2)) / planets[j].getMass();
                    planets[j].update(normalizeVector(planets[i], planets[j]), a);
                }
                planets[j].move();
            }
            */
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
            window.display();
            accumulatedTime2 -= timePerFrame2;
        }
    }
    return 0;
}
