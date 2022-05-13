#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class ColliderRect
{
private:
	FloatRect rectangle;
	RectangleShape rectShape;
	Vector2f position;
public:
	ColliderRect(float centerX, float centerY, float width, float height);
	ColliderRect(FloatRect getGlobalBounds, Vector2u mousePosGrid);
	const Vector2f GetPosition();
	const FloatRect GetRect();
	const RectangleShape GetRectShape();
};

