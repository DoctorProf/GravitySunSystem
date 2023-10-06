#include "../Headers/Global.hpp"

using namespace sf;


bool global::frameCollisionX(float x, float radius)
{
    return (x + radius > 1920 || x + radius < 0);
}
bool global::frameCollisionY(float y, float radius)
{
    return (y + radius > 1080 || y + radius < 0);
}
double global::distance(Vector2f vec1, Vector2f vec2)
{
    double dx = vec1.x - vec2.x;
    double dy = vec1.y - vec2.y;
    return std::sqrt(dx * dx + dy * dy);
}
Vector2f global::offset(double radius)
{
    return Vector2f(radius, radius);
}
Vector2f global::normalizeVector(Planet planet1, Planet planet2)
{
    Vector2f vec = (planet1.getPosition() + offset(planet1.getRadius())) - (planet2.getPosition() + offset(planet2.getRadius()));
    double distan = distance(planet1.getPosition() + offset(planet1.getRadius()), planet2.getPosition() + offset(planet2.getRadius()));
    return Vector2f((float)vec.x / distan, (float)vec.y / distan);
}
void global::spawnPlanet(std::vector<Planet>& planets, RenderWindow& window)
{
    planets.push_back(Planet(30, 2e30, Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f), Vector2f(0, 0.0), Color::Color(255, 255, 0), "Sun"));
    planets.push_back(Planet(4, 3.33e23, Vector2f(planets[0].getPosition().x + planets[0].getRadius() + 58, planets[0].getPosition().y + planets[0].getRadius()), Vector2f(0, 1.5), Color::Color(128, 128, 128), "Mercury"));
    planets.push_back(Planet(12, 4.87e24, Vector2f(planets[0].getPosition().x + planets[0].getRadius() + 108, planets[0].getPosition().y + planets[0].getRadius()), Vector2f(0, 1.1), Color::Color(234, 205, 177), "Venus"));
    planets.push_back(Planet(12, 5.97e24, Vector2f(planets[0].getPosition().x + planets[0].getRadius() + 150, planets[0].getPosition().y + planets[0].getRadius()), Vector2f(0, 0.95), Color::Color(154, 205, 50), "Earth"));
    planets.push_back(Planet(8, 6.42e23, Vector2f(planets[0].getPosition().x + planets[0].getRadius() + 228, planets[0].getPosition().y + planets[0].getRadius()), Vector2f(0, 0.75), Color::Color(228, 64, 3), "Mars"));
    planets.push_back(Planet(28, 1.89e27, Vector2f(planets[0].getPosition().x + planets[0].getRadius() + 778, planets[0].getPosition().y + planets[0].getRadius()), Vector2f(0, -0.42), Color::Color(255, 226, 183), "Jupiter"));
    planets.push_back(Planet(24, 5.68e26, Vector2f(planets[0].getPosition().x + planets[0].getRadius() + 1400, planets[0].getPosition().y + planets[0].getRadius()), Vector2f(0, -0.32), Color::Color(255, 219, 139), "Saturn"));
    planets.push_back(Planet(24, 8.68e25, Vector2f(planets[0].getPosition().x + planets[0].getRadius() + 2800, planets[0].getPosition().y + planets[0].getRadius()), Vector2f(0, -0.23), Color::Color(150, 229, 233), "Uranus"));
    planets.push_back(Planet(24, 1.024e26, Vector2f(planets[0].getPosition().x + planets[0].getRadius() + 4550, planets[0].getPosition().y + planets[0].getRadius() ), Vector2f(0, -0.18), Color::Color(0, 0, 255), "Neptune"));

    planets.push_back(Planet(16, 1.309e22, Vector2f(planets[0].getPosition().x + planets[0].getRadius() + 5910, planets[0].getPosition().y + planets[0].getRadius()), Vector2f(0, -0.15), Color::Color(96, 96, 96), "Pluton"));
}
void global::setStyleText(Text &text, Font &font, Vector2f position) 
{
    text.setFont(font);
    text.setFillColor(Color::White);
    text.setCharacterSize(18);
    text.setPosition(position.x, position.y);
}