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
	ColliderRect(float top, float left, float width, float height);
	ColliderRect(FloatRect rectangle, Vector2u mouseGrid);
	const Vector2f GetPosition();
	const FloatRect GetRect();
	const RectangleShape GetRectShape();
};

