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
	Texture texture;
	double coeff;
public:
	Button(float x, float y, float sizeX, float sizeY, std::string &textur, double coeff);
	void draw(RenderWindow& window);
	void setPosition(Vector2f positition);
	Vector2f getPosition();
	void setSize(Vector2f size);
	Vector2f getSize();
	double getCoeff();
	void setTexture(std::string& texture);
};