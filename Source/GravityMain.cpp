#include "../Headers/Planet.hpp"
#include "../Headers/Global.hpp"
#include "../Headers/Button.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

using namespace sf;

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

    double F = 0;
    double a = 0;
    int count = 0;


    Time accumulatedTime = Time::Zero;
    Time accumulatedTime2 = Time::Zero;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
            if (event.type == Event::KeyReleased && event.key.code == Keyboard::Num1 && count == 0)
            {
                planets.push_back(Planet(30 / SCALEGRAP, 2e30, Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f), Vector2f(0, 0.0), Color::Color(255, 255, 0), "Sun"));
                //planets.push_back(Planet(6 / SCALEGRAP, 3.33e23, Vector2f(planets[0].getPosition().x + planets[0].getRadius() + 58 / SCALEGRAP, planets[0].getPosition().y + planets[0].getRadius()), Vector2f(0, 1.5 / SCALEGRAP), Color::Color(128, 128, 128), "Mercury"));
                //planets.push_back(Planet(12 / SCALEGRAP, 4.87e24, Vector2f(planets[0].getPosition().x + planets[0].getRadius() + 108 / SCALEGRAP, planets[0].getPosition().y + planets[0].getRadius()), Vector2f(0, 1.1 / SCALEGRAP), Color::Color(234, 205, 177), "Venus"));
                //planets.push_back(Planet(12 / SCALEGRAP, 5.97e24, Vector2f(planets[0].getPosition().x + planets[0].getRadius() + 150 / SCALEGRAP, planets[0].getPosition().y + planets[0].getRadius()), Vector2f(0, 0.95 / SCALEGRAP), Color::Color(154, 205, 50), "Earth"));
                planets.push_back(Planet(8 / SCALEGRAP, 6.42e23, Vector2f(planets[0].getPosition().x + planets[0].getRadius() + 228 / SCALEGRAP, planets[0].getPosition().y + planets[0].getRadius()), Vector2f(0, 0.75 / SCALEGRAP), Color::Color(228, 64, 3), "Mars"));
                //planets.push_back(Planet(54 / SCALEGRAP, 1.89e27, Vector2f(planets[0].getPosition().x + planets[0].getRadius() + 778 / SCALEGRAP, planets[0].getPosition().y + planets[0].getRadius()), Vector2f(0, 1.2 / SCALEGRAP), Color::Color(255, 226, 183), "Jupiter"));
                //planets.push_back(Planet(36 / SCALEGRAP, 5.68e26, Vector2f(planets[0].getPosition().x + planets[0].getRadius() + 1400 / SCALEGRAP, planets[0].getPosition().y + planets[0].getRadius()), Vector2f(0, 1 / SCALEGRAP), Color::Color(255, 219, 139), "Saturn"));
                //planets.push_back(Planet(36 / SCALEGRAP, 8.68e25, Vector2f(planets[0].getPosition().x + planets[0].getRadius() + 2800 / SCALEGRAP, planets[0].getPosition().y + planets[0].getRadius()), Vector2f(0, 0.8 / SCALEGRAP), Color::Color(150, 229, 233), "Uranus"));
                //planets.push_back(Planet(36 / SCALEGRAP, 1.024e26, Vector2f(planets[0].getPosition().x + planets[0].getRadius() + 4550 / SCALEGRAP, planets[0].getPosition().y + planets[0].getRadius()), Vector2f(0, 0.8 / SCALEGRAP), Color::Color(0, 0, 255), "Neptune"));
                count++;
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
                planets.clear();
                count = 0;
            }
            else if (event.type == Event::KeyReleased && event.key.code == Keyboard::Space)
            {
                pause = !pause;
            }
            else if (event.type == Event::KeyReleased && event.key.code == Keyboard::Numpad8)
            {
                planets.clear();
                count = 0;
                SCALEPHY *= 2;
                SCALEGRAP *= 1.6;
            }
            
            else if (event.type == Event::KeyReleased && event.key.code == Keyboard::Numpad2)
            {
                planets.clear();
                count = 0;
                SCALEPHY /= 2;
                SCALEGRAP /= 1.6;
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
                            buttons.push_back(Button(50, 60, 50, 30, 0.1));
                            buttons.push_back(Button(150, 60, 50, 30, 10));
                            
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
        while (accumulatedTime >= TIMEPERFRAME)
        {
            accumulatedTime -= TIMEPERFRAME;
            if (pause) continue;
            for (int j = 0; j < planets.size(); j++)
            {
                for (int i = 0; i < planets.size(); i++)
                {
                    if (i == j) continue;

                    if (trackDraw)
                    {
                        Vertex pos(Vector2f(planets[j].getPosition().x + planets[j].getRadius(), planets[j].getPosition().y + planets[j].getRadius()));
                        pos.color = planets[j].getColor();
                        planets[j].addTrack(pos);
                    }

                    double distan = distance(planets[j].getPosition() + offset(planets[j].getRadius()), planets[i].getPosition() + offset(planets[i].getRadius())) * SCALEPHY;
                    F = (double)G * (planets[j].getMass() * planets[i].getMass()) / pow(distan, 2);
                    a = (double)F / planets[j].getMass();
                    Vector2f normDir = normalizeVector(planets[i], planets[j]);
                    planets[j].update(normDir, a);
                }
                planets[j].move();
            }
        }
        accumulatedTime2 += clock2.restart();
        if (accumulatedTime2 >= TIMEPERFRAME2)
        {
            window.clear(Color::Black);

            for (int i = 0; i < planets.size(); i++)
            {
                if (planets[i].getTrack().getVertexCount() > 1)
                {
                    planets[i].drawTrack(window);
                }
            }
            for (int i = 0; i < planets.size(); i++)
            {
                planets[i].drawPlanet(window);
            }
            window.display();
            accumulatedTime2 -= TIMEPERFRAME2;
        }
    }
    return 0;
}
