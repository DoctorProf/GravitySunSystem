#include "../Headers/Planet.hpp"

Planet::Planet(double radius, double mass, Vector2f position, Vector2f velocity, Color color, std::string name) :
    radius(radius),
    mass(mass),
    position(position - Vector2f(radius, radius)),
    velocity(velocity),
    color(color),
    name(name)
{
    track.setPrimitiveType(LinesStrip);
    //LinesStrip
    planet.setRadius(radius);
    planet.setPosition(position - Vector2f(radius, radius));
    planet.setFillColor(color);
}
void Planet::addTrack(Vertex pos)
{
    /*
    for (int i = 0; i < track.getVertexCount(); i++) {
        if (track[i].position == pos.position) {
            return;
        }
    }
    */
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