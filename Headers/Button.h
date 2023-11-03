#pragma once
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

using namespace sf;

class Button
{
private:
	RectangleShape button;
	float x;
	float y;
	float sizeX;
	float sizeY;
	Texture texturButton;
	Texture texturMessage;
	double coeff;
	bool status;
public:
	Button(float x, float y, float sizeX, float sizeY, std::string &texturButton, std::string texturMessage, double coeff);
	void draw(RenderWindow& window);
	void setPosition(Vector2f positition);
	Vector2f getPosition();
	void setSize(Vector2f size);
	Vector2f getSize();
	double getCoeff();
	Texture getTextureMessage();
	bool getStatus();
	void setStatus(bool status);
};