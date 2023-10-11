#include "../Headers/Planet.h"

Planet::Planet(double radius, double mass, Vector2f position, Vector2f velocity, Color color, std::string name):
    radius(radius),
    mass(mass),
    position(position - Vector2f(radius, radius)),
    velocity(velocity),
    color(color),
    name(name)
{
    this->focus = false;
    track.setPrimitiveType(LinesStrip);
    planet.setRadius(radius);
    planet.setPosition(position - Vector2f(radius, radius));
    planet.setFillColor(color);
}
void Planet::addTrack()
{
    Vertex pos;
    pos.position = Vector2f(position.x + radius, position.y + radius);
    pos.color = Color::Color(color.r, color.g, color.b, color.a / 2);
    track.append(pos);
}
void Planet::clearTrack()
{
    track.clear();
}
VertexArray Planet::getTrack()
{
    return track;
}
double Planet::getRadius()
{
    return radius;
}
double Planet::getMass()
{
    return mass;
}
void Planet::setMass(double mass)
{
    this->mass = mass;
}
std::string Planet::getName()
{
    return name;
}
Vector2f Planet::getPosition()
{
    return position;
}
Vector2f Planet::getVelocity() 
{
    return velocity;
}
void Planet::setPosition(Vector2f position)
{
    this->position = position;
}
void Planet::setVelocity(Vector2f velocity)
{
    this->velocity = velocity;
}
Color Planet::getColor()
{
    return color;
}
void Planet::update(Vector2f normDir, float a)
{
    velocity += Vector2f(normDir.x * a, normDir.y * a);
}
void Planet::move() {
    position += velocity;
}
void Planet::drawTrack(RenderWindow& window)
{
    window.draw(track);
}
void Planet::drawPlanet(RenderWindow& window)
{
    planet.setPosition(position);
    window.draw(planet);
}
void Planet::setFocus(bool focus) 
{
    this->focus = focus;
}
bool Planet::getFocus()
{
    return this->focus;
}