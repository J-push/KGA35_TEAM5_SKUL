#include "ColliderRect.h"

ColliderRect::ColliderRect(float centerX, float centerY, float width, float height)
{
	rectangle.top = centerY - height * 0.5f;
	rectangle.left = centerX - width * 0.5f;
	rectangle.width = width;
	rectangle.height = height;

	rectShape.setFillColor(Color::White);
	rectShape.setSize(Vector2f(width, height));
	rectShape.setPosition(position);
	rectShape.setOrigin(Vector2f(width * 0.5f, height * 0.5f));
}

ColliderRect::ColliderRect(FloatRect getGlobalBounds, Vector2u mousePosGrid)
{
	position = Vector2f((float)getGlobalBounds.left, (float)getGlobalBounds.top);
	rectangle.top = getGlobalBounds.top;
	rectangle.left = getGlobalBounds.left;
	rectangle.width = getGlobalBounds.width;
	rectangle.height = getGlobalBounds.height;

	rectShape.setFillColor(Color(153, 153, 153, 100));
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
