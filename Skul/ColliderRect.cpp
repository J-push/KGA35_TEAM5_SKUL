#include "ColliderRect.h"

ColliderRect::ColliderRect(float xpos, float ypos, float width, float height)
{
	rectangle.top = ypos - height * 0.5f;
	rectangle.left = xpos - width * 0.5f;
	rectangle.width = width;
	rectangle.height = height;

	rectShape.setFillColor(Color::White);
	rectShape.setSize(Vector2f(width, height));
	rectShape.setPosition(xpos - width *0.5 , ypos - height * 0.5);
	rectShape.setOrigin(position);
}

ColliderRect::ColliderRect(FloatRect getGlobalBounds, Vector2u mouseGrid)
{
	position = Vector2f((float)mouseGrid.x * 32.f, (float)mouseGrid.y * 32.f);
	rectangle.top = getGlobalBounds.top;
	rectangle.left = getGlobalBounds.left;
	rectangle.width = getGlobalBounds.width;
	rectangle.height = getGlobalBounds.height;

	rectShape.setFillColor(Color(153, 153, 153));
	rectShape.setSize(Vector2f(getGlobalBounds.width, getGlobalBounds.height));
	rectShape.setPosition(position);
}

const Vector2f ColliderRect::GetPosition()
{
	return position;
}

const FloatRect ColliderRect::GetRect()
{
	return rectangle;
}

const RectangleShape ColliderRect::GetRectShape()
{
	return rectShape;
}
