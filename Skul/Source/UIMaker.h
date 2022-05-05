#pragma once

#include "../Source/Manager/ResourceMgr.h"
#include "../Source/Manager/SceneMgr.h"
#include "../Source/Animation/AnimationController.h"
#include "../Source/Utils/ChangeMouse.h"

class UIMaker
{
private:

	SceneMgr mgr;
	Scenes currentScene;
	MouseCursor mouseCursor;


	// Title UI
	AnimationController animationGameStart;
	AnimationController animationMapEdit;

	RectangleShape shapeGameStart;
	RectangleShape shapeMapEdit;

	sf::Sprite spriteStart;
	sf::Sprite spriteMapEdit;

	std::map<std::string, Texture> texMap;


	// Game UI
	Sprite spriteMainFrame;
	Sprite spriteHpBar;
	Sprite SpriteGrimReaperIcon;
	Sprite SpriteGrimReaperSkill;

	float hp = 2.5f;

public:

	const int MAIN_FRAME_X = 30;
	const int MAIN_FRAME_Y = 800;
	const int HP_BAR_X = MAIN_FRAME_X + 108;
	const int HP_BAR_Y = MAIN_FRAME_Y + 110;
	const int PORTRAIT_X = MAIN_FRAME_X - 20;
	const int PORTRAIT_Y = MAIN_FRAME_Y - 16;
	const int SKIIL1_X = MAIN_FRAME_X + 142;
	const int SKIIL1_Y = MAIN_FRAME_Y + 33;


	void Init();

	virtual void Update(float dt);
	virtual void Draw(sf::RenderWindow *window);

};

