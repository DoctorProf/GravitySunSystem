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
	Texture texture;
public:
	Button(float x, float y, float sizeX, float sizeY, std::string name, std::string &textur);
	void draw(RenderWindow& window);
	std::string getName();
	void setPosition(Vector2f positition);
	Vector2f getPosition();
	void setSize(Vector2f size);
	Vector2f getSize();
};