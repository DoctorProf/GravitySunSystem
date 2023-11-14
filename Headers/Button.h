#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Button
{
private:
	RectangleShape button;
	float x;
	float y;
	float sizeX;
	float sizeY;
	Texture textureButtonOn;
	Texture textureButtonOff;
	Texture textureMessage;
	double coeff;
	bool status;
	bool on;
public:
	Button(float x, float y, float sizeX, float sizeY, std::string textureButtonOff, std::string textureButtonOn, std::string texturMessage, double coeff);
	void draw(RenderWindow& window);
	void setPosition(Vector2f positition);
	Vector2f getPosition();
	void setSize(Vector2f size);
	Vector2f getSize();
	double getCoeff();
	Texture getTextureMessage();
	bool getStatus();
	void setStatus(bool status);
	bool getOn();
	void setOn(bool on);
};