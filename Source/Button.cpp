#include "../Headers/Button.h"
#include <sstream>
#include <string>
#include <iomanip>

Button::Button(float x, float y, float sizeX, float sizeY, std::string &textur, double coeff)
{
	this->x = x;
	this->y = y;
	this->sizeX = sizeX;
	this->sizeY = sizeY;
	this->coeff = coeff;
	this->texture.loadFromFile(textur);
	button.setPosition(x, y);
	button.setSize(Vector2f(sizeX, sizeY));
	button.setFillColor(Color::Color(122, 122, 122));
}
void Button::draw(RenderWindow& window)
{
	button.setTexture(&texture);
	window.draw(button);
}
void Button::setPosition(Vector2f position)
{
	this->x = position.x;
	this->y = position.y;
	this->button.setPosition(Vector2f(this->x, this->y));
}
Vector2f Button::getPosition() 
{
	return this->button.getPosition();
}
void Button::setSize(Vector2f size)
{
	this->sizeX = size.x;
	this->sizeY = size.y;
	this->button.setSize(Vector2f(this->sizeX, this->sizeY));
}
Vector2f Button::getSize() 
{
	return this->button.getSize();
}
double Button::getCoeff() 
{
	return this->coeff;
}