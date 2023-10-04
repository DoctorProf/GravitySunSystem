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
	double coeff;
	Text text;
	Font font;
public:
	Button(float x, float y, float sizeX, float sizeY, double coeff);
	void draw(RenderWindow& window, Font &font);
	bool collisionButton(int x, int y);
	double getcoeff();
};