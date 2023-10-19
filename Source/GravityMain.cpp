﻿#include "../Headers/Global.h"
#include "../Headers/Texture.h"
#include <sstream>
#include <string>
#include <iomanip>
#include <ppl.h>

using namespace sf;
using namespace gl;

int main() 
{
   
    //Создание окна
    RenderWindow window(VideoMode::getDesktopMode(), "SpaceSimulator", Style::Titlebar);
    //Создание представления мира, размеры и центр
    View world;
    world.setCenter(Vector2f(window.getSize().x / 2, window.getSize().y / 2));
    world.setSize(Vector2f(window.getSize().x, window.getSize().y));

    //Загрузка стиля текста
    Font font;
    font.loadFromFile("C:\\windows\\fonts\\arial.ttf");

    //Глобальные переменные
    bool pause = false;
    bool trackDraw = false;
    bool speed = false;
    Clock clock;
    Clock clock2;
    Clock clock3;
    Time interval = seconds(0.03);
    double G = 6.67e-11;
    double scalePhy = 1e9;

    //Векторы планет и кнопок на основном экране
    std::vector<Planet> planets;
    std::vector<Button> buttonsPlanet;
    std::vector<Button> buttonsLogic;
    std::vector<Button> buttonsInfo;
    std::vector<RectangleShape> namesPlanet;

    RectangleShape background;
    background.setSize(Vector2f(world.getSize().x, world.getSize().y));
    Texture back;
    back.loadFromFile(textureButton[18]);
    //Панель для кнопок
    RectangleShape panel;
    panel.setFillColor(Color::Color(25,25,25));
    panel.setSize(Vector2f(world.getSize().x / 12.8, world.getSize().y));
    panel.setPosition(Vector2f(0, 0));
    //Панель для информации
    RectangleShape panelInfo;
    panelInfo.setSize(Vector2f(world.getSize().x / 6.4, world.getSize().y / 10.8));
    panelInfo.setPosition(Vector2f(world.getSize().x / 1.19, 0));
    //Масштаб отношение Предсталения к окну
    float scaleWorldinWindow = world.getSize().x / window.getSize().x;
    // инициализация tps и fps
    Time accumulatedTime = Time::Zero;
    Time accumulatedTime2 = Time::Zero;

    Time timePerFrame = seconds(1.0f / 120); // tps
    Time timePerFrame2 = seconds(1.0f / 240); // fps

    //Изначальный спавн планет и кнопок панели
    spawnPlanet(std::ref(planets), window);
    generateButton(planets, buttonsPlanet, buttonsLogic, namesPlanet, buttonsInfo, window);
    
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::W)
            {
                resetFosucPlanet(planets);
                world.move(0, -25);
                calculateNamesPlanet(namesPlanet, window, scaleWorldinWindow);
                calculatePanel(panel,panelInfo, window, world, scaleWorldinWindow);
                calculateBackground(background, window, world);
                calculateButtonPlanet(buttonsPlanet, window, world, scaleWorldinWindow);
                calculateButtonLogic(buttonsLogic, buttonsInfo, window, world, scaleWorldinWindow);
            }
            else if (event.type == Event::KeyPressed && event.key.code == Keyboard::S)
            {
                resetFosucPlanet(planets);
                world.move(0, 25);
                calculateNamesPlanet(namesPlanet, window, scaleWorldinWindow);
                calculatePanel(panel, panelInfo, window, world, scaleWorldinWindow);
                calculateBackground(background, window, world);
                calculateButtonPlanet(buttonsPlanet, window, world, scaleWorldinWindow);
                calculateButtonLogic(buttonsLogic, buttonsInfo, window, world, scaleWorldinWindow);
            }
            else if (event.type == Event::KeyPressed && event.key.code == Keyboard::A)
            {
                resetFosucPlanet(planets);
                world.move(-25, 0);
                calculateNamesPlanet(namesPlanet, window, scaleWorldinWindow);
                calculatePanel(panel, panelInfo, window, world, scaleWorldinWindow);
                calculateBackground(background, window, world);
                calculateButtonPlanet(buttonsPlanet, window, world, scaleWorldinWindow);
                calculateButtonLogic(buttonsLogic, buttonsInfo, window, world, scaleWorldinWindow);
            }
            else if (event.type == Event::KeyPressed && event.key.code == Keyboard::D)
            {
                resetFosucPlanet(planets);
                world.move(25, 0);
                calculateNamesPlanet(namesPlanet, window, scaleWorldinWindow);
                calculatePanel(panel, panelInfo, window, world, scaleWorldinWindow);
                calculateBackground(background, window, world);
                calculateButtonPlanet(buttonsPlanet, window, world, scaleWorldinWindow);
                calculateButtonLogic(buttonsLogic, buttonsInfo, window, world, scaleWorldinWindow);
            }
            else if (event.type == Event::MouseMoved)
            {
                Vector2i mouseCoor = Mouse::getPosition(window);
                bool mouseOnAnyButton = false;
                bool mouseOnAnyButtonPlanet = false;
                for (int i = 0; i < buttonsInfo.size(); i++)
                {
                    Vector2i buttonCoor = window.mapCoordsToPixel(Vector2f(buttonsInfo[i].getPosition().x, buttonsInfo[i].getPosition().y));
                    if (collisionButton(buttonCoor.x, buttonCoor.y, buttonsInfo[i].getSize().x / scaleWorldinWindow, buttonsInfo[i].getSize().y / scaleWorldinWindow,
                        mouseCoor.x, mouseCoor.y))
                    {
                        buttonsInfo[i].setStatus(true);
                        mouseOnAnyButton = true;
                    }
                    else 
                    {
                        buttonsInfo[i].setStatus(false);
                    }
                }
                for (int i = 0; i < buttonsPlanet.size(); i++)
                {
                    Vector2i buttonCoor = window.mapCoordsToPixel(Vector2f(buttonsPlanet[i].getPosition().x, buttonsPlanet[i].getPosition().y));
                    if (collisionButton(buttonCoor.x, buttonCoor.y, buttonsPlanet[i].getSize().x / scaleWorldinWindow, buttonsPlanet[i].getSize().y / scaleWorldinWindow,
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
                if (!mouseOnAnyButton) resetStatuButton(buttonsInfo);
                if (!mouseOnAnyButtonPlanet) resetStatuButton(buttonsPlanet);
            }
            else if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
            {
                for (int i = 0; i < buttonsPlanet.size(); i++) 
                {
                    Vector2i buttonCoor = window.mapCoordsToPixel(Vector2f(buttonsPlanet[i].getPosition().x, buttonsPlanet[i].getPosition().y));
                    if (collisionButton(buttonCoor.x, buttonCoor.y, buttonsPlanet[i].getSize().x / scaleWorldinWindow, buttonsPlanet[i].getSize().y / scaleWorldinWindow, event.mouseButton.x, event.mouseButton.y))
                    {
                        pause = true;
                        RenderWindow windowSettings(VideoMode(500, 600), "", Style::None);
                        
                        Text namePlanet;
                        Text textMass;
                        Text textSpeed;
                        Text textCamera;
                        std::ostringstream massE;
                        //Установка одинакового стиля текста
                        setStyleText(namePlanet, font, Vector2f(50, 20));
                        setStyleText(textMass, font, Vector2f(50, 50));
                        setStyleText(textSpeed, font, Vector2f(50, 120));
                        setStyleText(textCamera, font, Vector2f(150, 180));
                        //Вектора кнопок для панели редактирования планеты
                        std::vector<Button> buttonsMass;
                        std::vector<Button> buttonsSpeed;
                        std::vector<Button> buttonsCamera;
                        Button buttonClose(400, 500, 50, 50, textureButton[16], "", 1);
                        //Добавление всех кнопок на экранчике) да шакал, а кто судит
                        buttonsCamera.push_back(Button(190, 210, 50, 50, textureButtonWindow[7], "", 1));
                        buttonsCamera.push_back(Button(250, 210, 50, 50, textureButtonWindow[8], "", 1));
                        buttonsMass.push_back(Button(50, 80, 50, 25, textureButtonWindow[0], "", 0.1f));
                        buttonsMass.push_back(Button(110, 80, 50, 25, textureButtonWindow[1], "", 0.5f));
                        buttonsMass.push_back(Button(170, 80, 50, 25, textureButtonWindow[2], "", 2.0f));
                        buttonsMass.push_back(Button(230, 80, 50, 25, textureButtonWindow[3], "", 5.0f));
                        buttonsMass.push_back(Button(290, 80, 50, 25, textureButtonWindow[4], "", 10.0f));
                        buttonsSpeed.push_back(Button(50, 150, 50, 25, textureButtonWindow[0], "", 0.1f));
                        buttonsSpeed.push_back(Button(110, 150, 50, 25, textureButtonWindow[1], "", 0.5f));
                        buttonsSpeed.push_back(Button(170, 150, 50, 25, textureButtonWindow[5], "", 1.2f));
                        buttonsSpeed.push_back(Button(230, 150, 50, 25, textureButtonWindow[6], "", 1.5f));


                        while (windowSettings.isOpen()) {
                            Event event1;
                            while (windowSettings.pollEvent(event1))
                            {
                                if (event1.type == Event::MouseButtonPressed && event1.mouseButton.button == Mouse::Left)
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
                                    for (int j = 0; j < buttonsCamera.size(); j++)
                                    {
                                        if (collisionButton(buttonsCamera[j].getPosition().x, buttonsCamera[j].getPosition().y, buttonsCamera[j].getSize().x, buttonsCamera[j].getSize().y,
                                            event1.mouseButton.x, event1.mouseButton.y))
                                        {
                                            if (j == 0) 
                                            {
                                                resetFosucPlanet(planets);
                                                planets[i].setFocus(true);
                                            }
                                            else 
                                            {
                                                resetFosucPlanet(planets);
                                                planets[i].setFocus(false);
                                            }
                                        }
                                    }
                                    if (collisionButton(buttonClose.getPosition().x, buttonClose.getPosition().y, buttonClose.getSize().x, buttonClose.getSize().y,
                                        event1.mouseButton.x, event1.mouseButton.y))
                                    {
                                        windowSettings.close();
                                        pause = false;
                                        clock.restart();
                                    }
                                }
                            }   
                            massE << std::scientific << std::setprecision(2) << planets[i].getMass();
                            namePlanet.setString(planets[i].getName());
                            textMass.setString(L"Масса  " + massE.str());
                            textSpeed.setString(L"Скорость < " + std::to_string(planets[i].getVelocity().x) + ", " + std::to_string(planets[i].getVelocity().y) + " >");
                            textCamera.setString(L"Зафиксировать камеру");

                            windowSettings.clear(Color::Color(50, 50, 50));

                            windowSettings.draw(namePlanet);
                            windowSettings.draw(textMass);
                            windowSettings.draw(textSpeed);
                            windowSettings.draw(textCamera);

                            drawButtons(buttonsMass, windowSettings);
                            drawButtons(buttonsSpeed, windowSettings);
                            drawButtons(buttonsCamera, windowSettings);
                            buttonClose.draw(windowSettings);
                            windowSettings.display();
                            massE.str("");
                        }
                    }
                }
                for (int i = 0; i < buttonsLogic.size(); i++)
                {
                    Vector2i buttonCoor = window.mapCoordsToPixel(Vector2f(buttonsLogic[i].getPosition().x, buttonsLogic[i].getPosition().y));
                    if (collisionButton(buttonCoor.x, buttonCoor.y, buttonsLogic[i].getSize().x / scaleWorldinWindow, buttonsLogic[i].getSize().y / scaleWorldinWindow,
                        event.mouseButton.x, event.mouseButton.y))
                    {
                        if (i == 0)
                        {
                            world.setSize(world.getSize().x * 2, world.getSize().y * 2);
                            break;
                        }
                        else if (i == 1 && scaleWorldinWindow >= 0.03)
                        {
                            world.setSize(world.getSize().x / 2, world.getSize().y / 2);
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
                            world.setCenter(Vector2f(window.getSize().x / 2, window.getSize().y / 2));
                            planets.clear();
                            buttonsPlanet.clear();
                            buttonsLogic.clear();
                            buttonsInfo.clear();
                            spawnPlanet(planets, window);
                            generateButton(planets, buttonsPlanet, buttonsLogic, namesPlanet, buttonsInfo, window);
                        }
                        else if (i == 5) 
                        {
                            pause = !pause;
                        }
                        else if (i == 6) 
                        {
                            speed = !speed;
                            if(speed)
                            {
                                timePerFrame = seconds(1.0f / 800);
                            }
                            else 
                            {
                                timePerFrame = seconds(1.0f / 120);
                            }
                        }
                        if (i == 7)
                        {
                            window.close();
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
            collisionPlanet(planets, buttonsPlanet, window, world, scaleWorldinWindow);
            logicPlanet(planets, G, scalePhy, world);
            Time time = clock3.getElapsedTime();
            if (trackDraw && time >= interval)
            {
                for (int i = 0; i < planets.size(); i++)
                {
                    planets[i].addTrack();
                }
                clock3.restart();
            }
        }
        accumulatedTime2 += clock2.restart();
        
        if (accumulatedTime2 >= timePerFrame2)
        {
            accumulatedTime2 -= timePerFrame2;
            window.setView(world);
            calculateNamesPlanet(namesPlanet, window, scaleWorldinWindow);
            calculatePanel(panel, panelInfo, window, world, scaleWorldinWindow);
            calculateBackground(background, window, world);
            calculateButtonPlanet(buttonsPlanet, window, world, scaleWorldinWindow);
            calculateButtonLogic(buttonsLogic, buttonsInfo, window, world, scaleWorldinWindow);
            background.setTexture(&back);
            window.draw(background);

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
                if (buttonsPlanet[i].getStatus())
                {
                    namesPlanet[i].setPosition(Vector2f(planets[i].getPosition().x + 2 * planets[i].getRadius(), planets[i].getPosition().y));
                    Texture panelTextur = buttonsPlanet[i].getTextureMessage();
                    namesPlanet[i].setTexture(&panelTextur);
                    window.draw(namesPlanet[i]);
                }
            }
            window.draw(panel);
            for (int i = 0; i < buttonsInfo.size(); i++)
            {
                if (buttonsInfo[i].getStatus()) 
                {
                    Texture panelTextur = buttonsInfo[i].getTextureMessage();
                    panelInfo.setTexture(&panelTextur);
                    window.draw(panelInfo);
                }
            }
            
            
            drawButtons(buttonsPlanet, window);
            drawButtons(buttonsLogic, window);
            drawButtons(buttonsInfo, window);
            window.display();
        }
    }
    return 0;
}
