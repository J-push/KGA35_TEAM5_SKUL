#pragma once

#include "../Manager/ResourceMgr.h"
#include "../Manager/SceneMgr.h"
#include "../Animation/AnimationController.h"
#include "../Utils/ChangeMouse.h"
#include "../Manager/InputManager.h"
#include "../Player/Player.h"
#include "../Monster/PinkEnt/PinkEnt.h"

class SceneGame;

enum class Heads
{
	NONE,
	LITTLEBORN,
	REAPER,
};

class UIMaker
{
private:


	Scenes currentScene;
	MouseCursor mouseCursor;

	// Title UI
	AnimationController animationGameStart;
	AnimationController animationMapEdit;

	RectangleShape shapeGameStart;
	RectangleShape shapeMapEdit;

	Sprite spriteStart;
	Sprite spriteMapEdit;

	std::map<std::string, Texture> texMap;

	bool clickGameStart;


	// Game UI
	Sprite spriteMainFrame;
	Sprite spriteHpBar;
	Sprite spriteAbutton;
	
	Sprite spriteGrimReaperIcon1;
	Sprite spriteGrimReaperIcon3;
	Sprite spriteGrimReaperSkill;

	Sprite spriteLittleBoneIcon1;
	Sprite spriteLittleBoneIcon3;

	int nowHead = 1;
	int subHead = 2;

	float hp;
	float bossHpText = 7.0f;

	Text textHp;

	// ���� UI
	Sprite spriteBossFrame; // BOSSFRAMETEX
	Sprite spriteBossHpBar; // BOSSHPBARTEX

	// �ҵ�� UI
	Sprite spriteSwordManFrame; // SWORDMANFRAMETEX
	Sprite spriteSwordManHpBar; // SWORDMANHPBARTEX


	float swordManHp;
	float bossHp;

	// DamageText
	Text underAttackText;
	float textSpeed;
	float deleteDistance;
	bool isActive;
	bool lookBoss;




public:

	const int MAIN_FRAME_X = 30;
	const int MAIN_FRAME_Y = 800;
	const int HP_BAR_X = MAIN_FRAME_X + 108;
	const int HP_BAR_Y = MAIN_FRAME_Y + 110;
	const int PORTRAIT_X = MAIN_FRAME_X - 20;
	const int PORTRAIT_Y = MAIN_FRAME_Y - 16;
	const int SKIIL1_X = MAIN_FRAME_X + 142;
	const int SKIIL1_Y = MAIN_FRAME_Y + 33;
	const int A_X = MAIN_FRAME_X + 160;
	const int A_Y = MAIN_FRAME_Y + 15;
	const int MINI_HEAD_X = MAIN_FRAME_X;
	const int MINI_HEAD_Y = MAIN_FRAME_Y + 80;

	const int BOSS_FRAME_X = 2420;
	const int BOSS_FRAME_Y = 0;

	UIMaker();
	UIMaker(SceneGame *hp);

	void Init();

	virtual void Update(float dt);
	//virtual void Draw(sf::RenderWindow *window);

	bool GetClickGameStart();

	FloatRect GetMouseBound();
	void SetHpbarText(int CurHp, int MaxHp);
	void SetHpbarSize(int CurHp, int MaxHp);

	void SetBossHpbarSize(int CurHp, int MaxHp);


	// Damage
	void UnderAttack(Vector2f position, float dt);

	void SetUiPosition(Vector2f position);

	virtual void DrawSceneTitle(sf::RenderWindow *window);
	virtual void DrawSceneGame(sf::RenderWindow *window);
};
