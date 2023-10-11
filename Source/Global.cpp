#include "../Headers/Global.h"

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

void global::setStyleText(Text &text, Font &font, Vector2f position) 
{
    text.setFont(font);
    text.setFillColor(Color::White);
    text.setCharacterSize(18);
    text.setPosition(position.x, position.y);
}
bool global::collisionButton(float x, float y, float sizeX, float sizeY, float mouseX, float mouseY)
{
    return (mouseX >= x && mouseX <= sizeX + x) && (mouseY >= y && mouseY <= sizeY + y);
}
