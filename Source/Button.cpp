#include "../Headers/Button.h"
#include <sstream>
#include <string>
#include <iomanip>

Button::Button(float x, float y, float sizeX, float sizeY, std::string &texturButton, std::string texturMessage, double coeff)
{
	this->x = x;
	this->y = y;
	this->sizeX = sizeX;
	this->sizeY = sizeY;
	this->coeff = coeff;
	this->texturButton.loadFromFile(texturButton);
	this->texturMessage.loadFromFile(texturMessage);
	this->status = false;
	this->button.setPosition(x, y);
	this->button.setSize(Vector2f(sizeX, sizeY));
}
void Button::draw(RenderWindow& window)
{
	button.setTexture(&texturButton);
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
Texture Button::getTextureMessage() 
{
	return this->texturMessage;
}
bool Button::getStatus() 
{
	return this->status;
}
void Button::setStatus(bool status)
{
	this->status = status;
}
