#include "../Headers/Global.hpp"
#include "../Headers/Button.hpp"
#include "SFML/Audio.hpp"
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
    
    RectangleShape panel;
    panel.setFillColor(Color::Color(25,25,25));
    const float G = 6.67e-11;
    bool run = true;
    double scalePhy = 1e9;
    float coeffPanel = 1;
    const int frameRate = 120;
    Time accumulatedTime = Time::Zero;
    Time accumulatedTime2 = Time::Zero;

    bool unlimited_fps = false;

    Time timePerFrame = seconds(1.0f / frameRate); // tps
    Time timePerFrame2 = seconds(1.0f / frameRate); // fps
    spawnPlanet(std::ref(planets), window);
    for (int i = 0; i < planets.size(); i++)
    {
        buttonsPlanet.push_back(Button(world.getCenter().x - world.getSize().x / 2 + 25, world.getCenter().y - world.getSize().y / 2 + 20 + 50 * i, 100, 30, planets[i].getName()));
    }
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
                world.setCenter(Vector2f(960, 540));
                coeffPanel = 1;
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
                world.setCenter(window.getSize().x / 2, window.getSize().y / 2);
            }
            else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Numpad2)
            {
                world.setSize(world.getSize().x / 2, world.getSize().y / 2);
                world.setCenter(window.getSize().x / 2, window.getSize().y / 2);
            }
            else if (event.type == Event::MouseButtonPressed) 
            {
                if (event.mouseButton.button == Mouse::Left) 
                {
                    for (int i = 0; i < buttonsPlanet.size(); i++) 
                    {
                        Vector2i worldCoords = Vector2i(event.mouseButton.x, event.mouseButton.y);
                        if (buttonsPlanet[i].collisionButton(worldCoords.x, worldCoords.y))
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
                            buttonsMass.push_back(Button(50, 60, 50, 30, "0.5"));
                            buttonsMass.push_back(Button(150, 60, 50, 30, "2"));
                            buttonsMass.push_back(Button(240, 60, 50, 30, "10"));
                            buttonsSpeed.push_back(Button(50, 120, 50, 30, "0.75"));
                            buttonsSpeed.push_back(Button(150, 120, 50, 30, "1.25"));
                            buttonsSpeed.push_back(Button(240, 120, 50, 30, "1.5"));
                            
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
            panel.setSize(Vector2f(world.getSize().x * 1/13, world.getSize().y));
            panel.setPosition(Vector2f(world.getCenter().x - world.getSize().x / 2, world.getCenter().y - world.getSize().y / 2));
            window.draw(panel);
            for (int i = 0; i < buttonsPlanet.size(); i++) 
            {
                
                buttonsPlanet[i].setPosition(Vector2f(panel.getPosition().x + panel.getSize().x * 1/96, panel.getPosition().y + 20 + 50 * i));
                buttonsPlanet[i].setSize(Vector2f(panel.getSize().x * 2/3, panel.getSize().y * 1/36));
                buttonsPlanet[i].draw(window,font);
            }
            window.display();
            accumulatedTime2 -= timePerFrame2;
        }
    }
    return 0;
}
