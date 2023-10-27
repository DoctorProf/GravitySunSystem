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

    //Глобальные переменныe
    bool pause = false;
    bool trackDraw = false;
    int speed = 0;
    bool systemBoundary = false;
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
    std::vector<RectangleShape> namesPlanet;

    RectangleShape background;
    background.setSize(Vector2f(world.getSize().x, world.getSize().y));
    Texture back;
    back.loadFromFile(textureBackground[0]);
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
    panelPlanet.setSize(Vector2f(world.getSize().x / 4.8, world.getSize().y / 3.6));
    panelPlanet.setPosition(Vector2f(world.getSize().x / 1.26, world.getSize().y / 1.385));
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
                    if (event.mouseWheelScroll.delta > 0 && scaleWorldinWindow >= 0.03)
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
                buttonsCamera.clear();
                buttonsCloseAndDelete.clear();
                resetMenuPlanets(planets);
            }
            else if (event.type == Event::MouseMoved)
            {
                Vector2i mouseCoor = Mouse::getPosition(window);
                bool mouseOnAnyButton = false;
                bool mouseOnAnyButtonPlanet = false;
                bool mouseOnAnyButtonCamera = false;
                bool mouseOnAnyButtonCloseAndDelete = false;
                for (int i = 0; i < buttonsCamera.size(); i++)
                {
                    Vector2i buttonCoor = window.mapCoordsToPixel(Vector2f(buttonsCamera[i].getPosition().x, buttonsCamera[i].getPosition().y));
                    if (collisionButton(buttonCoor.x, buttonCoor.y, buttonsCamera[i].getSize().x / scaleWorldinWindow, buttonsCamera[i].getSize().y / scaleWorldinWindow,
                        mouseCoor.x, mouseCoor.y))
                    {
                        buttonsCamera[i].setStatus(true);
                        mouseOnAnyButtonCamera = true;
                    }
                    else
                    {
                        buttonsCamera[i].setStatus(false);
                    }
                }
                for (int i = 0; i < buttonsCloseAndDelete.size(); i++)
                {
                    Vector2i buttonCoor = window.mapCoordsToPixel(Vector2f(buttonsCloseAndDelete[i].getPosition().x, buttonsCloseAndDelete[i].getPosition().y));
                    if (collisionButton(buttonCoor.x, buttonCoor.y, buttonsCloseAndDelete[i].getSize().x / scaleWorldinWindow, buttonsCloseAndDelete[i].getSize().y / scaleWorldinWindow,
                        mouseCoor.x, mouseCoor.y))
                    {
                        buttonsCloseAndDelete[i].setStatus(true);
                        mouseOnAnyButtonCloseAndDelete = true;
                    }
                    else
                    {
                        buttonsCloseAndDelete[i].setStatus(false);
                    }
                }
                for (int i = 0; i < buttonsLogic.size(); i++)
                {
                    Vector2i buttonCoor = window.mapCoordsToPixel(Vector2f(buttonsLogic[i].getPosition().x, buttonsLogic[i].getPosition().y));
                    if (collisionButton(buttonCoor.x, buttonCoor.y, buttonsLogic[i].getSize().x / scaleWorldinWindow, buttonsLogic[i].getSize().y / scaleWorldinWindow,
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
                if (!mouseOnAnyButton) resetStatusButton(buttonsLogic);
                if (!mouseOnAnyButtonPlanet) resetStatusButton(buttonsPlanet);
                if (!mouseOnAnyButtonCamera) resetStatusButton(buttonsCamera);
                if (!mouseOnAnyButtonCloseAndDelete) resetStatusButton(buttonsCloseAndDelete);
            }
            else if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
            {
                for (int i = 0; i < buttonsPlanet.size(); i++)
                {
                    Vector2i buttonCoor = window.mapCoordsToPixel(Vector2f(buttonsPlanet[i].getPosition().x, buttonsPlanet[i].getPosition().y));
                    if (collisionButton(buttonCoor.x, buttonCoor.y, buttonsPlanet[i].getSize().x / scaleWorldinWindow, buttonsPlanet[i].getSize().y / scaleWorldinWindow, event.mouseButton.x, event.mouseButton.y))
                    {
                        resetMenuPlanets(planets);
                        buttonsMass.clear();
                        buttonsSpeed.clear();
                        buttonsCamera.clear();
                        buttonsCloseAndDelete.clear();
                        planets[i].setMenuPlanet(true);
                        genButtonMenu(buttonsMass, buttonsSpeed, buttonsCamera, buttonsCloseAndDelete, window);
                    }
                }
                for (int i = 0; i < buttonsLogic.size(); i++)
                {
                    Vector2i buttonCoords = window.mapCoordsToPixel(Vector2f(buttonsLogic[i].getPosition().x, buttonsLogic[i].getPosition().y));
                    if (collisionButton(buttonCoords.x, buttonCoords.y, buttonsLogic[i].getSize().x / scaleWorldinWindow, buttonsLogic[i].getSize().y / scaleWorldinWindow,
                        event.mouseButton.x, event.mouseButton.y))
                    {
                        if (i == 0 && scaleWorldinWindow < 1e3)
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
                            buttonsMass.clear();
                            buttonsSpeed.clear();
                            buttonsCamera.clear();
                            namesPlanet.clear();
                            buttonsCloseAndDelete.clear();
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
                                timePerFrame = seconds(1.0f / 400.0f);
                            }
                            else if(speed == 1)
                            {
                                speed++;
                                timePerFrame = seconds(1.0f / 700.0f);
                            }
                            else if (speed == 2)
                            {
                                speed++;
                                timePerFrame = seconds(1.0f / 1100.0f);
                            }
                            else if (speed == 3) 
                            {
                                timePerFrame = seconds(1.0f / 60.0f);
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
                                    buttonsMass.clear();
                                    buttonsSpeed.clear();
                                    buttonsCamera.clear();
                                    buttonsCloseAndDelete.clear();
                                    resetMenuPlanets(planets);
                                    planets.erase(planets.begin() + i);
                                    buttonsPlanet.erase(buttonsPlanet.begin() + i);
                                }
                                else if (j == 1)
                                {
                                    planets[i].setBlockMove(!planets[i].getBlockMove());
                                }
                                else if (j == 2) 
                                {
                                    buttonsMass.clear();
                                    buttonsSpeed.clear();
                                    buttonsCamera.clear();
                                    buttonsCloseAndDelete.clear();
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
        calculatePanel(panel, panelInfo, panelPlanet, window, world, scaleWorldinWindow);
        calculateBackground(background, window, world);
        calculateButtonPlanet(buttonsPlanet, window, world, scaleWorldinWindow);
        calculateButtonLogic(buttonsLogic, window, world, scaleWorldinWindow);
        accumulatedTime2 += clock2.restart();
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
        if (accumulatedTime2 >= timePerFrame2)
        {
            accumulatedTime2 -= timePerFrame2;
            window.setView(world);
            
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
                if (buttonsPlanet[i].getStatus() || planets[i].getFocus() || planets[i].getMenuPlanet())
                {
                    namesPlanet[i].setPosition(Vector2f(planets[i].getPosition().x + 2.0f * planets[i].getRadius(), planets[i].getPosition().y));
                    Texture panelTextur = buttonsPlanet[i].getTextureMessage();
                    namesPlanet[i].setTexture(&panelTextur);
                    window.draw(namesPlanet[i]);
                }
            }
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
            for (int i = 0; i < buttonsCamera.size(); i++)
            {
                if (buttonsCamera[i].getStatus())
                {
                    Texture panelTextur = buttonsCamera[i].getTextureMessage();
                    panelInfo.setTexture(&panelTextur);
                    window.draw(panelInfo);
                }
            }
            for (int i = 0; i < buttonsCloseAndDelete.size(); i++)
            {
                if (buttonsCloseAndDelete[i].getStatus())
                {
                    Texture panelTextur = buttonsCloseAndDelete[i].getTextureMessage();
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
                    calculateButtonMenu(buttonsMass, buttonsSpeed, buttonsCamera, buttonsCloseAndDelete, window, world, scaleWorldinWindow);
                    tgui::Gui gui{ window };
                    std::wstring name = "<color=white>" + planets[i].getName() + "</color>";
                    std::ostringstream mass;
                    std::ostringstream speed;
                    mass << "<color=white>" << "Mass " << std::scientific << std::setprecision(2) << planets[i].getMass() << "</color>";
                    speed << "<color=white>Speed " << std::setprecision(5) << pow( pow(planets[i].getVelocity().x, 2) + pow(planets[i].getVelocity().y, 2), 0.5) << " </color>";
                    tgui::RichTextLabel::Ptr labelName = tgui::RichTextLabel::create();
                    tgui::RichTextLabel::Ptr labelMass = tgui::RichTextLabel::create();
                    tgui::RichTextLabel::Ptr labelSpeed = tgui::RichTextLabel::create();
                    labelName->setText(name);
                    labelName->setPosition(window.getSize().x / 1.247, window.getSize().y / 1.355);
                    labelName->setTextSize(window.getSize().x / 106.7);
                    labelMass->setText(mass.str());
                    labelMass->setPosition(window.getSize().x / 1.247, window.getSize().y / 1.315);
                    labelMass->setTextSize(window.getSize().x / 106.7);
                    labelSpeed->setText(speed.str());
                    labelSpeed->setPosition(window.getSize().x / 1.247, window.getSize().y / 1.23);
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