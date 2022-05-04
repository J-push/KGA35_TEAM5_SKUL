#pragma once

#include "../Source/Manager/InputManager.h"
#include "../Source/Manager/ResourceMgr.h"
#include "../Source/Utils/Utils.h"

#include <iostream>


class MouseCursor
{
private:
	sf::Sprite  spriteCursor;
	FloatRect CursorBounds;

public:
	void Init()
	{
		spriteCursor.setTexture(*ResourceMgr::instance()->GetTexture("CURSORTEX"));

		//Utils::SetOrigin(spriteCursor, Pivots::CC);

	}

	void Update(float dt)
	{
		spriteCursor.setPosition(InputManager::GetMouseWorldPosition());

		spriteCursor.setPosition().x = 100;


		std::cout << spriteCursor.getPosition().x;
	}

	virtual void Draw(sf::RenderWindow *window)
	{
		window->draw(spriteCursor);
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