#include "../Headers/Global.h"
#include "../Headers/Texture.h"
#include <sstream>
#include <string>
#include <iomanip>
#include "SFML/Audio.hpp"
using namespace sf;
using namespace gl;

int main() 
{
    //Все для звука фона
    SoundBuffer spaceBuffer;
    spaceBuffer.loadFromFile("spaceSound.mp3");
    Sound spaceSound;
    spaceSound.setBuffer(spaceBuffer);
    Clock clockSound;
    //Стиль текста
    Font font;
    font.loadFromFile("C:/Windows/Fonts/Calibri.ttf");
    //Создание окна
    RenderWindow window(VideoMode::getDesktopMode(), "SpaceSimulator", Style::Fullscreen);
    window.setVerticalSyncEnabled(true);
    //Создание представления мира, размеры и центр
    View world;
    world.setCenter(Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f));
    world.setSize(Vector2f(window.getSize().x, window.getSize().y));
    View guiPanel;
    guiPanel.setCenter(Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f));
    guiPanel.setSize(Vector2f(window.getSize().x, window.getSize().y));
    //Глобальные переменныe
    bool pause = false;
    bool trackDraw = true;
    int speed = 0;
    bool systemBoundary = false;
    Clock clock;
    Clock clock2;
    Clock clock3;
    Time interval = seconds(0.01);
    double G = 6.67e-11;
    double scalePhy = 1e9;

    //Векторы планет и кнопок на основном экране
    std::vector<Planet> planets;
    std::vector<Button> buttonsPlanet;
    std::vector<Button> buttonsLogic;
    std::vector<RectangleShape> namesPlanet;

    RectangleShape background;
    background.setSize(Vector2f(guiPanel.getSize().x, guiPanel.getSize().y));
    Texture back;
    back.loadFromFile(textureBackground[0]);
    //Панель для кнопок
    RectangleShape panel;
    panel.setFillColor(Color::Color(25,25,25));
    panel.setSize(Vector2f(guiPanel.getSize().x / 12.8, guiPanel.getSize().y));
    panel.setPosition(Vector2f(0, 0));
    //Панель для информации
    RectangleShape panelInfo;
    panelInfo.setSize(Vector2f(guiPanel.getSize().x / 6.4, guiPanel.getSize().y / 10.8));
    panelInfo.setPosition(Vector2f(guiPanel.getSize().x / 1.19, 0));
    //Панель для планеты
    RectangleShape panelPlanet;
    panelPlanet.setFillColor(Color::Color(50, 50, 50));
    panelPlanet.setSize(Vector2f(guiPanel.getSize().x / 4.8, guiPanel.getSize().y / 3.6));
    panelPlanet.setPosition(Vector2f(guiPanel.getSize().x / 1.26, guiPanel.getSize().y / 1.385));
    //Масштаб отношение Предсталения к окну
    double scaleWorldinWindow = world.getSize().x / window.getSize().x;
    // инициализация tps и fps
    Time accumulatedTime = Time::Zero;
    Time accumulatedTime2 = Time::Zero;

    Time timePerFrame = seconds(1.0f / 30.0f); // tps
    Time timePerFrame2 = seconds(1.0f / 60.0f); // fps    
    
    //Вектора кнопок для панели редактирования планеты
    std::vector<Button> buttonsMass;
    std::vector<Button> buttonsSpeed;
    std::vector<Button> buttonsLogicPanelPlanet;
    //Изначальный спавн планет и кнопок панели
    spawnPlanet(planets, window);
    generateButton(planets, buttonsPlanet, buttonsLogic, namesPlanet, window);
    spaceSound.play();
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::MouseWheelScrolled)
            {
                if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
                {
                    if (event.mouseWheelScroll.delta > 0 && scaleWorldinWindow >= 0.003)
                    {
                        world.setSize(world.getSize().x / 2.0f, world.getSize().y / 2.0f);
                        break;
                    }
                    else if (event.mouseWheelScroll.delta < 0 && scaleWorldinWindow < 1e3)
                    {
                        world.setSize(world.getSize().x * 2.0f, world.getSize().y * 2.0f);
                        break;
                    }
                }
            }
            else if (event.type == Event::KeyReleased && event.key.code == Keyboard::Space)
            {
                pause = !pause;
                
            }
            else if (event.type == Event::KeyReleased && event.key.code == Keyboard::Escape)
            {
                buttonsMass.clear();
                buttonsSpeed.clear();
                buttonsLogicPanelPlanet.clear();
                resetMenuPlanets(planets);
            }
            else if (event.type == Event::MouseMoved)
            {
                Vector2i mouseCoor = Mouse::getPosition(window);
                bool mouseOnAnyButton = false;
                bool mouseOnAnyButtonPlanet = false;
                bool mouseOnAnyButtonLogicPanelPlanet = false;
                for (int i = 0; i < buttonsLogicPanelPlanet.size(); i++)
                {
                    if (collisionButton(buttonsLogicPanelPlanet[i].getPosition().x, buttonsLogicPanelPlanet[i].getPosition().y, buttonsLogicPanelPlanet[i].getSize().x, buttonsLogicPanelPlanet[i].getSize().y,
                        mouseCoor.x, mouseCoor.y))
                    {
                        buttonsLogicPanelPlanet[i].setStatus(true);
                        mouseOnAnyButtonLogicPanelPlanet = true;
                    }
                    else
                    {
                        buttonsLogicPanelPlanet[i].setStatus(false);
                    }
                }
                for (int i = 0; i < buttonsLogic.size(); i++)
                {
                    if (collisionButton(buttonsLogic[i].getPosition().x, buttonsLogic[i].getPosition().y, buttonsLogic[i].getSize().x, buttonsLogic[i].getSize().y,
                        mouseCoor.x, mouseCoor.y))
                    {
                        buttonsLogic[i].setStatus(true);
                        mouseOnAnyButton = true;
                    }
                    else
                    {
                        buttonsLogic[i].setStatus(false);
                    }
                }
                for (int i = 0; i < buttonsPlanet.size(); i++)
                {
                    if (collisionButton(buttonsPlanet[i].getPosition().x, buttonsPlanet[i].getPosition().y, buttonsPlanet[i].getSize().x, buttonsPlanet[i].getSize().y,
                        mouseCoor.x, mouseCoor.y))
                    {
                        buttonsPlanet[i].setStatus(true);
                        mouseOnAnyButtonPlanet = true;
                    }
                    else
                    {
                        buttonsPlanet[i].setStatus(false);
                    }
                }
                if (!mouseOnAnyButton) resetStatusButton(buttonsLogic);
                if (!mouseOnAnyButtonPlanet) resetStatusButton(buttonsPlanet);
                if (!mouseOnAnyButtonLogicPanelPlanet) resetStatusButton(buttonsLogicPanelPlanet);
            }
            else if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
            {
                for (int i = 0; i < buttonsPlanet.size(); i++)
                {
                    if (collisionButton(buttonsPlanet[i].getPosition().x, buttonsPlanet[i].getPosition().y, buttonsPlanet[i].getSize().x, buttonsPlanet[i].getSize().y, event.mouseButton.x, event.mouseButton.y))
                    {
                        resetMenuPlanets(planets);
                        buttonsMass.clear();
                        buttonsSpeed.clear();
                        buttonsLogicPanelPlanet.clear();
                        planets[i].setMenuPlanet(true);
                        genButtonMenu(buttonsMass, buttonsSpeed, buttonsLogicPanelPlanet, window);
                    }
                }
                for (int i = 0; i < buttonsLogic.size(); i++)
                {
                    if (collisionButton(buttonsLogic[i].getPosition().x, buttonsLogic[i].getPosition().y, buttonsLogic[i].getSize().x, buttonsLogic[i].getSize().y,
                        event.mouseButton.x, event.mouseButton.y))
                    {
                        if (i == 0 && scaleWorldinWindow < 1e3)
                        {
                            world.setSize(world.getSize().x * 2.0f, world.getSize().y * 2.0f);
                            break;
                        }
                        else if (i == 1 && scaleWorldinWindow >= 0.003)
                        {
                            world.setSize(world.getSize().x / 2.0f, world.getSize().y / 2.0f);
                            break;
                        }
                        else if (i == 2)
                        {
                            trackDraw = true;
                        }
                        else if (i == 3)
                        {
                            trackDraw = false;
                            for (int i = 0; i < planets.size(); i++)
                            {
                                planets[i].clearTrack();
                            }
                        }
                        else if (i == 4)
                        {
                            world.setSize(window.getSize().x, window.getSize().y);
                            world.setCenter(Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f));
                            planets.clear();
                            buttonsPlanet.clear();
                            buttonsLogic.clear();
                            buttonsMass.clear();
                            buttonsSpeed.clear();
                            namesPlanet.clear();
                            buttonsLogicPanelPlanet.clear();
                            spawnPlanet(planets, window);
                            generateButton(planets, buttonsPlanet, buttonsLogic, namesPlanet, window);
                        }
                        else if (i == 5)
                        {
                            pause = !pause;
                        }
                        else if (i == 6)
                        { 
                            if (speed == 0)
                            {
                                speed++;
                                timePerFrame = seconds(1.0f / 300.0f);
                            }
                            else if(speed == 1)
                            {
                                speed++;
                                timePerFrame = seconds(1.0f / 600.0f);
                            }
                            else if (speed == 2)
                            {
                                speed++;
                                timePerFrame = seconds(1.0f / 900.0f);
                            }
                            else if (speed == 3) 
                            {
                                timePerFrame = seconds(1.0f / 30.0f);
                                speed = 0;
                            }
                        }
                        if (i == 7) 
                        {
                            systemBoundary = !systemBoundary;
                        }
                        if (i == 8)
                        {
                            window.close();
                        }
                    }
                }
                for (int i = 0; i < planets.size(); i++) 
                {
                    if (planets[i].getMenuPlanet()) 
                    {
                        for (int j = 0; j < buttonsMass.size(); j++) 
                        {
                            if (collisionButton(buttonsMass[j].getPosition().x, buttonsMass[j].getPosition().y, buttonsMass[j].getSize().x, buttonsMass[j].getSize().y,
                                event.mouseButton.x, event.mouseButton.y)) 
                            {
                                planets[i].setMass(planets[i].getMass() * buttonsMass[j].getCoeff());
                            }
                        }
                        for (int j = 0; j < buttonsSpeed.size(); j++)
                        {
                            if (collisionButton(buttonsSpeed[j].getPosition().x, buttonsSpeed[j].getPosition().y, buttonsSpeed[j].getSize().x, buttonsSpeed[j].getSize().y,
                                event.mouseButton.x, event.mouseButton.y))
                            {
                                planets[i].setVelocity(Vector2f(planets[i].getVelocity().x * buttonsSpeed[j].getCoeff(), planets[i].getVelocity().y * buttonsSpeed[j].getCoeff()));
                            }
                        }
                        for (int j = 0; j < buttonsLogicPanelPlanet.size(); j++)
                        {
                            if (collisionButton(buttonsLogicPanelPlanet[j].getPosition().x, buttonsLogicPanelPlanet[j].getPosition().y, buttonsLogicPanelPlanet[j].getSize().x, buttonsLogicPanelPlanet[j].getSize().y,
                                event.mouseButton.x, event.mouseButton.y))
                            {
                                if (j == 1)
                                {
                                    resetFosucPlanet(planets);
                                    planets[i].setFocus(true);
                                }
                                else if(j == 2)
                                {
                                    resetFosucPlanet(planets);
                                    planets[i].setFocus(false);
                                }
                            }
                        }
                        for (int j = 0; j < buttonsLogicPanelPlanet.size(); j++)
                        {
                            if (collisionButton(buttonsLogicPanelPlanet[j].getPosition().x, buttonsLogicPanelPlanet[j].getPosition().y, buttonsLogicPanelPlanet[j].getSize().x, buttonsLogicPanelPlanet[j].getSize().y,
                                event.mouseButton.x, event.mouseButton.y))
                            {
                                if (j == 0)
                                {
                                    buttonsMass.clear();
                                    buttonsSpeed.clear();
                                    buttonsLogicPanelPlanet.clear();
                                    resetMenuPlanets(planets);
                                    planets.erase(planets.begin() + i);
                                    buttonsPlanet.erase(buttonsPlanet.begin() + i);
                                }
                                else if (j == 3)
                                {
                                    planets[i].setBlockMove(!planets[i].getBlockMove());
                                }
                                else if (j == 4) 
                                {
                                    buttonsMass.clear();
                                    buttonsSpeed.clear();
                                    buttonsLogicPanelPlanet.clear();
                                    resetMenuPlanets(planets);
                                }
                            }
                        }
                    }
                }
            }
        }
        
        accumulatedTime += clock.restart();
        while (accumulatedTime >= timePerFrame)
        {
            scaleWorldinWindow = world.getSize().x / window.getSize().x;
            accumulatedTime -= timePerFrame;
            if (Keyboard::isKeyPressed(Keyboard::W))
            {
                resetFosucPlanet(planets);
                world.move(0, -10.0f * scaleWorldinWindow);
            }
            if(Keyboard::isKeyPressed(Keyboard::S))
            {
                resetFosucPlanet(planets);
                world.move(0, 10.0f * scaleWorldinWindow);
            }
            if (Keyboard::isKeyPressed(Keyboard::A))
            {
                resetFosucPlanet(planets);
                world.move(-10.0f * scaleWorldinWindow, 0);
            }
            if (Keyboard::isKeyPressed(Keyboard::D))
            {
                resetFosucPlanet(planets);
                world.move(10.0f * scaleWorldinWindow, 0);
            }
            if (pause) continue;
            if (systemBoundary)
            {
                beyondSolarSystem(planets, buttonsPlanet);
            }
            collisionPlanet(planets, buttonsPlanet, window, world, scaleWorldinWindow);
            logicPlanet(planets, G, scalePhy, world);    
        }
        
        calculateNamesPlanet(namesPlanet, window, scaleWorldinWindow);
        Time time = clock3.getElapsedTime();
        if (trackDraw && time >= interval)
        {
            for (int i = 0; i < planets.size(); i++)
            {
                planets[i].addTrack();
            }
            clock3.restart();
        }
        if (clockSound.getElapsedTime().asSeconds() > 268) 
        {
            spaceSound.play();
            clockSound.restart();
        }
        accumulatedTime2 += clock2.restart();
        if (accumulatedTime2 >= timePerFrame2)
        {
            accumulatedTime2 -= timePerFrame2;            
            background.setTexture(&back);
            window.setView(guiPanel);
            window.draw(background);
            window.setView(world);

            for (int i = 0; i < planets.size(); i++)
            {
                planets[i].drawTrack(window);
            }
            for (int i = 0; i < planets.size(); i++)
            {
                planets[i].drawPlanet(window); 
            }
            for (int i = 0; i < buttonsPlanet.size(); i++)
            {
                if (buttonsPlanet[i].getStatus() || planets[i].getFocus() || planets[i].getMenuPlanet())
                {
                    namesPlanet[i].setPosition(Vector2f(planets[i].getPosition().x + 2.0f * planets[i].getRadius(), planets[i].getPosition().y));
                    Texture panelTextur = buttonsPlanet[i].getTextureMessage();
                    namesPlanet[i].setTexture(&panelTextur);
                    window.draw(namesPlanet[i]);
                }
            }
            window.setView(guiPanel);
            window.draw(panel);
            for (int i = 0; i < buttonsLogic.size(); i++)
            {
                if (buttonsLogic[i].getStatus())
                {
                    Texture panelTextur = buttonsLogic[i].getTextureMessage();
                    panelInfo.setTexture(&panelTextur);
                    window.draw(panelInfo);
                }
            }
            for (int i = 0; i < buttonsLogicPanelPlanet.size(); i++)
            {
                if (buttonsLogicPanelPlanet[i].getStatus())
                {
                    Texture panelTextur = buttonsLogicPanelPlanet[i].getTextureMessage();
                    panelInfo.setTexture(&panelTextur);
                    window.draw(panelInfo);
                }
            }
            
            drawButtons(buttonsPlanet, window);
            drawButtons(buttonsLogic, window);
            for (int i = 0; i < planets.size(); i++) 
            {
                if (planets[i].getMenuPlanet()) 
                {
                    std::wstring namePlanet = planets[i].getName();
                    std::ostringstream massPlanet;
                    std::ostringstream speedPlanet;
                    std::ostringstream distancePlanet;
                    Text name;
                    Text mass;
                    Text speed;
                    Text distancePlanetToPlanet;
                    setStyleText(name, font);
                    setStyleText(mass, font);
                    setStyleText(speed, font);
                    setStyleText(distancePlanetToPlanet, font);
                    name.setPosition(Vector2f(window.getSize().x / 1.247, window.getSize().y / 1.355));
                    mass.setPosition(Vector2f(window.getSize().x / 1.247, window.getSize().y / 1.315));
                    speed.setPosition(Vector2f(window.getSize().x / 1.247, window.getSize().y / 1.23));
                    distancePlanetToPlanet.setPosition(Vector2f(window.getSize().x / 1.247, window.getSize().y / 1.2));
                    massPlanet << "Mass " << std::scientific << std::setprecision(2) << planets[i].getMass();
                    speedPlanet << "Speed " << std::setprecision(5) << pow(pow(planets[i].getVelocity().x, 2) + pow(planets[i].getVelocity().y, 2), 0.5);
                    for (Planet planet : planets) 
                    {
                        for (Planet planet : planets)
                        {


                        }
                    }
                    name.setString(namePlanet);
                    mass.setString(massPlanet.str());
                    speed.setString(speedPlanet.str());
                    distancePlanetToPlanet.setString(distancePlanet.str());
                    window.draw(panelPlanet);
                    window.draw(name);
                    window.draw(mass);
                    window.draw(speed);
                    window.draw(distancePlanetToPlanet);
                    drawButtons(buttonsMass, window);
                    drawButtons(buttonsSpeed, window);
                    drawButtons(buttonsLogicPanelPlanet, window);
                }
            }
            window.display();
        }
    }
    return 0;
}