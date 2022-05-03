#pragma once

#include "../Source/Manager/InputManager.h"
#include "../Source/Manager/ResourceMgr.h"


class MouseCursor
{
private:
	sf::Sprite  spriteCursor;
	FloatRect CursorBounds;


public:
	MouseCursor()
	{
		spriteCursor.setTexture(*ResourceMgr::instance()->GetTexture("CURSORTEX"));
	}

	void Update(float dt)
	{
		spriteCursor.setPosition(InputManager::GetMouseWorldPosition());
	}

	virtual void Draw(sf::RenderWindow *window)
	{
		window->setMouseCursorVisible(false);
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