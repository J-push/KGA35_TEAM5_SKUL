#include "TestRectangle.h"

TestRectangle::TestRectangle(float xpos, float ypos, float width, float height)
{
	Rectangle.top = ypos - height * 0.5f;
	Rectangle.left = xpos - width * 0.5f;
	Rectangle.width = width;
	Rectangle.height = height;

	rectShape.setFillColor(Color::White);
	rectShape.setSize(Vector2f(width, height));
	rectShape.setPosition(xpos - width *0.5 , ypos - height * 0.5);
	rectShape.setOrigin(position);
}

const Vector2f TestRectangle::GetPosition()
{
	return position;
}


const FloatRect TestRectangle::GetRect()
{
	return Rectangle;
}

const RectangleShape TestRectangle::GetRectShape()
{
	return rectShape;
}
