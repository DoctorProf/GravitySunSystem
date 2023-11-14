#include "../Headers/Button.h"
#include <sstream>
#include <string>
#include <iomanip>

Button::Button(float x, float y, float sizeX, float sizeY, std::string textureButtonOff, std::string textureButtonOn, std::string texturMessage, double coeff)
{
	this->x = x;
	this->y = y;
	this->sizeX = sizeX;
	this->sizeY = sizeY;
	this->coeff = coeff;
	this->textureButtonOff.loadFromFile(textureButtonOff);
	this->textureButtonOn.loadFromFile(textureButtonOn);
	if (texturMessage != "")
	{
		this->textureMessage.loadFromFile(texturMessage);
	}
	this->status = false;
	this->on = false;
	this->button.setPosition(x, y);
	this->button.setSize(Vector2f(sizeX, sizeY));
}
void Button::draw(RenderWindow& window)
{
	if (this->on)
	{
		this->button.setTexture(&textureButtonOn);
	}
	else 
	{
		this->button.setTexture(&textureButtonOff);
	}
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
	return this->textureMessage;
}
bool Button::getStatus() 
{
	return this->status;
}
void Button::setStatus(bool status)
{
	this->status = status;
}
bool Button::getOn()
{
	return this->on;
}
void Button::setOn(bool on)
{
	this->on = on;
}