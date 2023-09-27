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
    std::string name;

public:
    Planet(double radius, double mass, Vector2f position, Vector2f velocity, Color color, std::string name);
    void addTrack(Vertex pos);
    void clearTrack();
    VertexArray getTrack();
    double getRadius();
    double getMass();
    void setMass(double mass);
    std::string getName();
    Vector2f getPosition();
    Color getColor();
    void update(Vector2f normDir, float a);
    void drawTrack(RenderWindow& window);
    void drawPlanet(RenderWindow& window);
    void move();
};