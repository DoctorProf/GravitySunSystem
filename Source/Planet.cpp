#include "../Headers/Planet.h"
#include "../Headers/Texture.h"

Planet::Planet(double radius, double mass, Vector2f position, Vector2f velocity, Color color, std::wstring name):
    radius(radius),
    mass(mass),
    position(position - Vector2f(radius, radius)),
    velocity(velocity),
    color(color),
    name(name)
{
    this->focus = false;
    this->track.setPrimitiveType(LinesStrip);
    this->planet.setRadius(radius);
    this->planet.setPosition(this->position);
    this->planet.setFillColor(color);
    this->planet.setPointCount(60);
    this->menuPlanet = false;
    this->blockMove = false;
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
std::wstring Planet::getName()
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
    if (velocity.x > 50 || velocity.x < -50 || velocity.y > 50 || velocity.y < -50) return;
    this->velocity = velocity;
}
Color Planet::getColor()
{
    return color;
}
void Planet::update(Vector2f normDir, float a)
{
    if (blockMove) return;
    velocity += Vector2f(normDir.x * a, normDir.y * a);
}
void Planet::move() {
    if (blockMove) return;
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
void Planet::setMenuPlanet(bool menuPlanet) 
{
    this->menuPlanet = menuPlanet;
}
bool Planet::getMenuPlanet()
{
    return this->menuPlanet;
}
void Planet::setBlockMove(bool blockMove) 
{
    this->blockMove = blockMove;
}
bool Planet::getBlockMove() 
{
    return this->blockMove;
}