#pragma once
#include "Scene.h"
#include "../Player/Player.h"
#include "../swordman/swordman.h"
#include "../UIMaker.h"
#include "../Utils/ChangeMouse.h"
#include "../../ColliderRect.h"
#include "../swordman/swordman.h"
#include "../Monster/PinkEnt/PinkEnt.h"
#include <vector>
#include "SceneMapEditor.h"
#include "../Boss.h"


class SceneGame : public Scene
{
private:
	float backGroundX = 1920.f / 1332.f;
	float backGroundY = 1080.f / 850.f;
	sf::Sprite spriteBackground;
	sf::Sprite spriteTile;
	Player player;
	std::vector<swordman*> mSwordMans;	// 소드맨 여러마리 생성
	swordman* mSwordman;

	Boss boss;

	Vector2i resolution;
	View *playerView;

	std::vector<PinkEnt*> mPinkEnt;	// 핑크엔트 여러마리 생성
	PinkEnt* pinkEnt;
	SceneMapEditor rect;
	SceneMapEditor tileMap;
	Clock forCheckTime;
	Time playTime;
	Time check;

	int damage;
public:

	int curHp;
	int maxHp;

	SceneGame(SceneMgr& mgr) : Scene(mgr) {};

	virtual void Init() override;
	virtual void Release() override;
	virtual void Start() override;
	virtual void End() override;
	virtual void Update(float dt, RenderWindow *window, View *mainView) override;
	virtual void Draw(sf::RenderWindow *window, View *mainView, View *uiView) override;
	
	void CreateSwordMan(std::vector<swordman*>& mSwordMans, int count);
	void CreatePinkEnt(std::vector<PinkEnt*>& mpinkEnt, int count);
	int GetMaxPlayerHealthReal();
	/*int GetCurrentPlayerHealthReal();*/
};

