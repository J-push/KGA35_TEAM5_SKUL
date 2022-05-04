#pragma once

#include "../Source/Manager/ResourceMgr.h"

class UIMaker
{
private:
	Sprite spriteMainFrame;
	Sprite spriteHpBar;

	Sprite SpriteGrimReaperIcon;
	Sprite SpriteGrimReaperSkill;

public:

	void Init();
	virtual void Draw(sf::RenderWindow *window);

};

