#include "../Headers/Button.hpp"
#include <sstream>
#include <string>
#include <iomanip>

Button::Button(float x, float y, float sizeX, float sizeY, std::string name)
{
	this->x = x;
	this->y = y;
	this->sizeX = sizeX;
	this->sizeY = sizeY;
	this->name = name;
	button.setPosition(x, y);
	button.setSize(Vector2f(sizeX, sizeY));
	button.setFillColor(Color::Color(122, 122, 122));
	this->text.setFillColor(Color::White);
}
void Button::draw(RenderWindow& window, Font &font)
{
	window.draw(button);
	this->text.setCharacterSize(16);
	this->text.setPosition((x + sizeX / 2) - 20, (y + sizeY / 2) - 10);
	this->text.setFont(font);
	this->text.setString(name);
	window.draw(this->text);
}
bool Button::collisionButton(int x, int y)
{
	return (x >= this->x && x <= this->sizeX + this->x) && (y >= this->y && y <= this->sizeY + this->y);
}
std::string Button::getName()
{
	return this->name;
}
void Button::setPosition(Vector2f position)
{
	this->x = position.x;
	this->y = position.y;
	this->button.setPosition(Vector2f(this->x, this->y));
}
void Button::setSize(Vector2f size)
{
	this->sizeX = size.x;
	this->sizeY = size.y;
	this->button.setSize(Vector2f(this->sizeX, this->sizeY));
}