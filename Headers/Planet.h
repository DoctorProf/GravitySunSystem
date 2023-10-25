#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Planet
{
private:
    CircleShape planet;
    double radius;
    double mass;
    Vector2f position;
    Vector2f velocity;
    VertexArray track;
    Color color;
    std::wstring name;
    bool focus;
    bool menuPlanet;
public:
    Planet(double radius, double mass, Vector2f position, Vector2f velocity, Color color, std::wstring name);
    void addTrack();
    void clearTrack();
    VertexArray getTrack();
    double getRadius();
    double getMass();
    void setMass(double mass);
    std::wstring getName();
    Vector2f getPosition();
    Vector2f getVelocity();
    void setPosition(Vector2f position);
    void setVelocity(Vector2f velocity);
    Color getColor();
    void update(Vector2f normDir, float a);
    void drawTrack(RenderWindow& window);
    void drawPlanet(RenderWindow& window);
    void move();
    void setFocus(bool focus);
    bool getFocus();
    void setMenuPlanet(bool menuPlanet);
    bool getMenuPlanet();
};