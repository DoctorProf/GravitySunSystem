#include "../Headers/Global.hpp"
#include "../Headers/Button.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

using namespace sf;
using namespace global;

int main() 
{
    RenderWindow window(VideoMode(1920, 1080), "Gravity");
    std::setlocale(LC_ALL, "rus");
    Font font;
    font.loadFromFile("C:\\windows\\fonts\\arial.ttf");
    bool pause = false;
    bool trackDraw = true;
    Clock clock;
    Clock clock2;

    std::vector<Planet> planets;
    float G = 6.67e-11;

    double a = 0;
    int count = 120;
    Event event;
    Vector2f normDir;
    Vertex pos;
    Time accumulatedTime = Time::Zero;
    Time accumulatedTime2 = Time::Zero;

    double scalePhy = (double)1e9;
    float scaleGrap = 1;
    Time timePerFrame = seconds(1.0f / count); // tps
    Time timePerFrame2 = seconds(1.0f / count); // fps
    spawnPlanet(std::ref(planets), scaleGrap, window);

    while (window.isOpen()) {
        while (window.pollEvent(event)) 
        {
            if (event.type == Event::Closed) window.close();
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
                planets.clear();
                spawnPlanet(planets, scaleGrap, window);
            }
            else if (event.type == Event::KeyReleased && event.key.code == Keyboard::Space) pause = !pause;
            else if (event.type == Event::KeyReleased && event.key.code == Keyboard::Numpad8)
            {
                planets.clear();
                scalePhy *= 2;
                scaleGrap *= 1.6;
                spawnPlanet(planets, scaleGrap, window);
            } 
            else if (event.type == Event::KeyReleased && event.key.code == Keyboard::Numpad2)
            {
                planets.clear();
                scalePhy /= 2;
                scaleGrap /= 1.6;
                spawnPlanet(planets, scaleGrap, window);
            }
            else if (event.type == Event::MouseButtonPressed) 
            {
                if (event.mouseButton.button == Mouse::Left) 
                {
                    for (int i = 0; i < planets.size(); i++) 
                    {
                        if (pow(event.mouseButton.x - (planets[i].getPosition().x + planets[i].getRadius()), 2) + pow(event.mouseButton.y - (planets[i].getPosition().y + planets[i].getRadius()), 2) <= pow(planets[i].getRadius(), 2))
                        {
                            pause = true;
                            RenderWindow windowSettings(VideoMode(500, 600), planets[i].getName());
                            Text text;
                            std::ostringstream massE;
                            std::vector<Button> buttons;
                            text.setFont(font);
                            text.setFillColor(Color::White);
                            text.setCharacterSize(18);
                            text.setPosition(50, 30);
                            buttons.push_back(Button(50, 60, 50, 30, 0.5));
                            buttons.push_back(Button(150, 60, 50, 30, 10));
                            buttons.push_back(Button(240, 60, 50, 30, 2));
                            
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
                                            for (int j = 0; j < buttons.size(); j++) 
                                            {
                                                if (buttons[j].collisionButton(event1.mouseButton.x, event1.mouseButton.y)) 
                                                {
                                                    planets[i].setMass(planets[i].getMass() * (double)buttons[j].getcoeff());
                                                }
                                            }
                                        }
                                    }
                                }   
                                massE << std::scientific << std::setprecision(2) << planets[i].getMass();
                                text.setString(L"Масса  " + massE.str());
                                windowSettings.clear(Color::Black);
                                windowSettings.draw(text);
                                for (int j = 0; j < buttons.size(); j++) 
                                {
                                    buttons[j].draw(windowSettings, font);
                                }
                                windowSettings.display();
                                massE.str("");
                            }
                        }
                    }
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
                if (trackDraw)
                {
                    if (!(frameCollisionX(planets[j].getPosition().x, planets[j].getRadius()) || frameCollisionY(planets[j].getPosition().y, planets[j].getRadius()))) {
                        pos.position = Vector2f(planets[j].getPosition().x + planets[j].getRadius(), planets[j].getPosition().y + planets[j].getRadius());
                        //pos.position = Vector2f(std::floor(planets[j].getPosition().x + planets[j].getRadius()), std::floor(planets[j].getPosition().y + planets[j].getRadius()));
                        pos.color = planets[j].getColor();
                        planets[j].addTrack(pos);
                    }
                }

                for (int i = 0; i < planets.size(); i++)
                {
                    if (i == j) continue;

                    double distan = distance(planets[j].getPosition() + offset(planets[j].getRadius()), planets[i].getPosition() + offset(planets[i].getRadius())) * scalePhy;
                    a = (double)(G * (planets[j].getMass() * planets[i].getMass()) / pow(distan, 2)) / planets[j].getMass();
                    normDir = normalizeVector(planets[i], planets[j]);
                    planets[j].update(normDir, a);
                }
                planets[j].move();
            }
        }
        accumulatedTime2 += clock2.restart();
        if (accumulatedTime2 >= timePerFrame2)
        {
            window.clear(Color::Black);
            for (int i = 0; i < planets.size(); i++)
            {
                if(planets[i].getTrack().getVertexCount() > 0) planets[i].drawTrack(window);
                continue;
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
