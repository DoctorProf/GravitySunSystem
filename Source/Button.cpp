#include "../Headers/Button.hpp"
#include <sstream>
#include <string>
#include <iomanip>

Button::Button(float x, float y, float sizeX, float sizeY, double coeff)
{
	this->x = x;
	this->y = y;
	this->sizeX = sizeX;
	this->sizeY = sizeY;
	this->coeff = coeff;
	button.setPosition(x, y);
	button.setSize(Vector2f(sizeX, sizeY));
	button.setFillColor(Color::Color(122, 122, 122));
	this->text.setPosition((x + sizeX / 2) - 10, (y + sizeY / 2) - 10);
	this->text.setFillColor(Color::White);
	this->text.setCharacterSize(16);
}
void Button::draw(RenderWindow& window, Font &font)
{
	std::ostringstream textCoeff;
	textCoeff << std::setprecision(2) << coeff;
	window.draw(button);
	this->text.setFont(font);
	this->text.setString(textCoeff.str());
	window.draw(this->text);
	textCoeff.str("");
}
bool Button::collisionButton(int x, int y)
{
	return (x >= this->x && x <= this->sizeX + this->x) && (y >= this->y && y <= this->sizeY + this->y);
}
double Button::getcoeff()
{
	return coeff;
}