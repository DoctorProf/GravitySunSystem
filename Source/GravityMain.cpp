#include "../Headers/Global.h"
#include "../Headers/Texture.h"
#include <sstream>
#include <string>
#include <iomanip>
#include "SFML/Audio.hpp"
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
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
    //Создание окна
    RenderWindow window(VideoMode::getDesktopMode(), "SpaceSimulator", Style::Fullscreen);
    window.setVerticalSyncEnabled(true);
    //Создание представления мира, размеры и центр
    View world;
    world.setCenter(Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f));
    world.setSize(Vector2f(window.getSize().x, window.getSize().y));

    //Загрузка стиля текста
    Font font;
    font.loadFromFile("C:\\windows\\fonts\\arial.ttf");
    //Глобальные переменныe
    bool flag = false;
    bool pause = false;
    bool trackDraw = false;
    bool speed = false;
    bool panelPlanetOn = false;
    Clock clock;
    Clock clock2;
    Clock clock3;
    Time interval = seconds(0.02);
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
    //Панель для планеты
    RectangleShape panelPlanet;
    panelPlanet.setFillColor(Color::Color(50, 50, 50));
    panelPlanet.setSize(Vector2f(world.getSize().x / 3.84, world.getSize().y / 1.8));
    panelPlanet.setPosition(Vector2f(world.getSize().x / 2.74, world.getSize().y / 4.5));
    //Масштаб отношение Предсталения к окну
    double scaleWorldinWindow = world.getSize().x / window.getSize().x;
    // инициализация tps и fps
    Time accumulatedTime = Time::Zero;
    Time accumulatedTime2 = Time::Zero;

    Time timePerFrame = seconds(1.0f / 60.0f); // tps
    Time timePerFrame2 = seconds(1.0f / 60.0f); // fps    
    
    //Вектора кнопок для панели редактирования планеты
    std::vector<Button> buttonsMass;
    std::vector<Button> buttonsSpeed;
    std::vector<Button> buttonsCamera;
    std::vector<Button> buttonsCloseAndDelete;
    
    //Изначальный спавн планет и кнопок панели
    spawnPlanet(planets, window);
    generateButton(planets, buttonsPlanet, buttonsLogic, namesPlanet, buttonsInfo, window);
    spaceSound.play();
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::W)
            {
                resetFosucPlanet(planets);
                world.move(0, -25.0f * scaleWorldinWindow);
            }
            else if (event.type == Event::KeyPressed && event.key.code == Keyboard::S)
            {
                resetFosucPlanet(planets);
                world.move(0, 25.0f * scaleWorldinWindow);
            }
            else if (event.type == Event::KeyPressed && event.key.code == Keyboard::A)
            {
                resetFosucPlanet(planets);
                world.move(-25.0f * scaleWorldinWindow, 0);
            }
            else if (event.type == Event::KeyPressed && event.key.code == Keyboard::D)
            {
                resetFosucPlanet(planets);
                world.move(25.0f * scaleWorldinWindow, 0);
            }
            else if (event.type == Event::MouseMoved)
            {
                if (!panelPlanetOn)
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
                    if (!mouseOnAnyButton) resetStatusButton(buttonsInfo);
                    if (!mouseOnAnyButtonPlanet) resetStatusButton(buttonsPlanet);
                }
            }
            else if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
            {
                if (!panelPlanetOn)
                {
                    for (int i = 0; i < buttonsPlanet.size(); i++) 
                    {
                        Vector2i buttonCoor = window.mapCoordsToPixel(Vector2f(buttonsPlanet[i].getPosition().x, buttonsPlanet[i].getPosition().y));
                        if (collisionButton(buttonCoor.x, buttonCoor.y, buttonsPlanet[i].getSize().x / scaleWorldinWindow, buttonsPlanet[i].getSize().y / scaleWorldinWindow, event.mouseButton.x, event.mouseButton.y))
                        {
                            if (pause) 
                            {
                                flag = true;
                            } 
                            else 
                            {
                                pause = true;
                            }    
                            planets[i].setMenuPlanet(true);
                            panelPlanetOn = true;
                            genButtonMenu(buttonsMass, buttonsSpeed, buttonsCamera, buttonsCloseAndDelete, window);
                        }
                    }
                    for (int i = 0; i < buttonsLogic.size(); i++)
                    {
                        Vector2i buttonCoords = window.mapCoordsToPixel(Vector2f(buttonsLogic[i].getPosition().x, buttonsLogic[i].getPosition().y));
                        if (collisionButton(buttonCoords.x, buttonCoords.y, buttonsLogic[i].getSize().x / scaleWorldinWindow, buttonsLogic[i].getSize().y / scaleWorldinWindow,
                            event.mouseButton.x, event.mouseButton.y))
                        {
                            if (i == 0 && scaleWorldinWindow < 1e15)
                            {
                                world.setSize(world.getSize().x * 2.0f, world.getSize().y * 2.0f);
                                break;
                            }
                            else if (i == 1 && scaleWorldinWindow >= 0.03)
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
                                buttonsInfo.clear();
                                buttonsMass.clear();
                                buttonsSpeed.clear();
                                buttonsCamera.clear();
                                buttonsCloseAndDelete.clear();
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
                                if (speed)
                                {
                                    timePerFrame = seconds(1.0f / 600.0f);
                                }
                                else
                                {
                                    timePerFrame = seconds(1.0f / 120.0f);
                                }
                            }
                            if (i == 7)
                            {
                                window.close();
                            }
                        }
                    }
                }
                else 
                {
                    for (int i = 0; i < planets.size(); i++) 
                    {
                        if (planets[i].getMenuPlanet()) 
                        {
                            for (int j = 0; j < buttonsMass.size(); j++) 
                            {
                                Vector2i buttonCoords = window.mapCoordsToPixel(Vector2f(buttonsMass[j].getPosition().x, buttonsMass[j].getPosition().y));
                                if (collisionButton(buttonCoords.x, buttonCoords.y, buttonsMass[j].getSize().x / scaleWorldinWindow, buttonsMass[j].getSize().y / scaleWorldinWindow,
                                    event.mouseButton.x, event.mouseButton.y)) 
                                {
                                    planets[i].setMass(planets[i].getMass() * buttonsMass[j].getCoeff());
                                }
                            }
                            for (int j = 0; j < buttonsSpeed.size(); j++)
                            {
                                Vector2i buttonCoords = window.mapCoordsToPixel(Vector2f(buttonsSpeed[j].getPosition().x, buttonsSpeed[j].getPosition().y));
                                if (collisionButton(buttonCoords.x, buttonCoords.y, buttonsSpeed[j].getSize().x / scaleWorldinWindow, buttonsSpeed[j].getSize().y / scaleWorldinWindow,
                                    event.mouseButton.x, event.mouseButton.y))
                                {
                                    planets[i].setVelocity(Vector2f(planets[i].getVelocity().x * buttonsSpeed[j].getCoeff(), planets[i].getVelocity().y * buttonsSpeed[j].getCoeff()));
                                }
                            }
                            for (int j = 0; j < buttonsCamera.size(); j++)
                            {
                                Vector2i buttonCoords = window.mapCoordsToPixel(Vector2f(buttonsCamera[j].getPosition().x, buttonsCamera[j].getPosition().y));
                                if (collisionButton(buttonCoords.x, buttonCoords.y, buttonsCamera[j].getSize().x / scaleWorldinWindow, buttonsCamera[j].getSize().y / scaleWorldinWindow,
                                    event.mouseButton.x, event.mouseButton.y))
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
                            for (int j = 0; j < buttonsCloseAndDelete.size(); j++)
                            {
                                Vector2i buttonCoords = window.mapCoordsToPixel(Vector2f(buttonsCloseAndDelete[j].getPosition().x, buttonsCloseAndDelete[j].getPosition().y));
                                if (collisionButton(buttonCoords.x, buttonCoords.y, buttonsCloseAndDelete[j].getSize().x / scaleWorldinWindow, buttonsCloseAndDelete[j].getSize().y / scaleWorldinWindow,
                                    event.mouseButton.x, event.mouseButton.y))
                                {
                                    if (j == 0) 
                                    {
                                        if (flag)
                                        {
                                            pause = true;
                                        }
                                        else
                                        {
                                            pause = false;
                                        }
                                        buttonsMass.clear();
                                        buttonsSpeed.clear();
                                        buttonsCamera.clear();
                                        buttonsCloseAndDelete.clear();
                                        resetMenuPlanets(planets);
                                        panelPlanetOn = false;
                                        flag = false;
                                        planets.erase(planets.begin() + i);
                                        buttonsPlanet.erase(buttonsPlanet.begin() + i);
                                        clock.restart();
                                    }
                                    else 
                                    {
                                        if (flag)
                                        {
                                            pause = true;
                                        }
                                        else
                                        {
                                            pause = false;
                                        }
                                        buttonsMass.clear();
                                        buttonsSpeed.clear();
                                        buttonsCamera.clear();
                                        buttonsCloseAndDelete.clear();
                                        clock.restart();
                                        panelPlanetOn = false;
                                        flag = false;
                                        resetMenuPlanets(planets);
                                    }
                                }
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
            beyondSolarSystem(planets, buttonsPlanet);
            collisionPlanet(planets, buttonsPlanet, window, world, scaleWorldinWindow);
            logicPlanet(planets, G, scalePhy, world);
            std::cout << planets[0].getPosition().x << " " << planets[0].getPosition().y << "Size view " << world.getSize().x << " " << world.getSize().y << "\n";
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
        if (clockSound.getElapsedTime().asSeconds() > 268) 
        {
            spaceSound.play();
            clockSound.restart();
        }
        if (accumulatedTime2 >= timePerFrame2)
        {
            accumulatedTime2 -= timePerFrame2;
            window.setView(world);
            calculateNamesPlanet(namesPlanet, window, scaleWorldinWindow);
            calculatePanel(panel, panelInfo, panelPlanet, window, world, scaleWorldinWindow);
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
                if (buttonsPlanet[i].getStatus() || planets[i].getFocus())
                {
                    namesPlanet[i].setPosition(Vector2f(planets[i].getPosition().x + 2.0f * planets[i].getRadius(), planets[i].getPosition().y));
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
            for (int i = 0; i < planets.size(); i++) 
            {
                if (planets[i].getMenuPlanet()) 
                {
                    calculateButtonMenu(buttonsMass, buttonsSpeed, buttonsCamera, buttonsCloseAndDelete, window, world, scaleWorldinWindow);
                    tgui::Gui gui{ window };
                    std::wstring name = "<color=white>" + planets[i].getName() + "</color>";
                    std::ostringstream mass;
                    std::ostringstream speed;
                    mass << "<color=white>" << "Mass " << std::scientific << std::setprecision(2) << planets[i].getMass() << "</color>";
                    speed << "<color=white>Speed (" << std::setprecision(4) << planets[i].getVelocity().x << ", " << std::setprecision(4) << planets[i].getVelocity().y << " )</color>";
                    tgui::RichTextLabel::Ptr labelName = tgui::RichTextLabel::create();
                    tgui::RichTextLabel::Ptr labelMass = tgui::RichTextLabel::create();
                    tgui::RichTextLabel::Ptr labelSpeed = tgui::RichTextLabel::create();
                    labelName->setText(name);
                    labelName->setPosition(window.getSize().x / 2.56, window.getSize().y / 4.15);
                    labelName->setTextSize(window.getSize().x / 106.7);
                    labelMass->setText(mass.str());
                    labelMass->setPosition(window.getSize().x / 2.56, window.getSize().y / 3.72);
                    labelMass->setTextSize(window.getSize().x / 106.7);
                    labelSpeed->setText(speed.str());
                    labelSpeed->setPosition(window.getSize().x / 2.56, window.getSize().y / 3.0f);
                    labelSpeed->setTextSize(window.getSize().x / 106.7);
                    gui.add(labelName);
                    gui.add(labelMass);
                    gui.add(labelSpeed);
                    window.draw(panelPlanet);
                    gui.draw();
                    drawButtons(buttonsMass, window);
                    drawButtons(buttonsSpeed, window);
                    drawButtons(buttonsCamera, window);
                    drawButtons(buttonsCloseAndDelete, window);
                }
            }
            window.display();
        }
    }
    return 0;
}