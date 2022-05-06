#pragma once

#include "../Manager/InputManager.h"
#include "../Manager/ResourceMgr.h"
#include "../Utils/Utils.h"
#include <iostream>


class MouseCursor
{
private:
	sf::Sprite  spriteCursor;
	FloatRect CursorBounds;

	RectangleShape shape;


public:
	void Init()
	{
		spriteCursor.setTexture(*ResourceMgr::instance()->GetTexture("CURSORTEX"));
		
		
		shape.setSize(Vector2f(10, 10));
		shape.setPosition(0,0);

		//Utils::SetOrigin(spriteCursor, Pivots::CC);

	}

	void Update(float dt)
	{
		spriteCursor.setPosition(Mouse::getPosition().x, Mouse::getPosition().y);
		shape.setPosition(Mouse::getPosition().x, Mouse::getPosition().y);
		
	}

	virtual void Draw(sf::RenderWindow *window)
	{
		window->setMouseCursorVisible(false);
		window->draw(spriteCursor);
	}


	FloatRect GetGlobalBounds()
	{
		return shape.getGlobalBounds();
	}

	Sprite GetSprite()
	{
		return spriteCursor;
	}

};

//Sprite spriteCrosshair;
//Texture textureCrosshair = TextureHorder::GetTexture("graphics/crosshair.png");
//spriteCrosshair.setTexture(textureCrosshair);
//Utils::SetOrigin(spriteCrosshair, Pivots::CC);