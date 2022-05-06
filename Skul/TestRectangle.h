#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class TestRectangle
{
private:
	FloatRect Rectangle;
	RectangleShape rectShape;
	Vector2f position;
public:
	TestRectangle(float top, float left, float width, float height);
	const Vector2f GetPosition();
	const FloatRect GetRect();
	const RectangleShape GetRectShape();
};

