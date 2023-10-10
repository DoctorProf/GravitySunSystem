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
	std::string name;
	Text text;
	Font font;
public:
	Button(float x, float y, float sizeX, float sizeY, std::string name);
	void draw(RenderWindow& window, Font &font);
	bool collisionButton(int x, int y);
	std::string getName();
	void setPosition(Vector2f positition);
	void setSize(Vector2f size);
};