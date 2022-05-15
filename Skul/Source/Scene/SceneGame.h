#pragma once
#include "Scene.h"
#include "../Player/Player.h"
#include "../swordman/swordman.h"
#include "../TileMap/Tilemap.h"
#include "../UIMaker.h"
#include "../Utils/ChangeMouse.h"
#include "../../TestRectangle.h"
#include "../swordman/swordman.h"
#include "../Monster/PinkEnt/PinkEnt.h"
#include <vector>
#include "../Boss.h"


class SceneGame : public Scene
{
private:
	float backGroundX = 1920.f / 1332.f;
	float backGroundY = 1080.f / 850.f;
	Tilemap tilemap;
	sf::Sprite spriteBackground;
	Player player;
	std::vector<swordman*> mSwordMans;	// 소드맨 여러마리 생성
	swordman* mSwordman;

	Boss boss;

	std::vector<PinkEnt*> mPinkEnt;	// 핑크엔트 여러마리 생성
	PinkEnt* pinkEnt;

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
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow* window) override;

	void CreateSwordMan(std::vector<swordman*>& mSwordMans, int count);
	void CreatePinkEnt(std::vector<PinkEnt*>& mpinkEnt, int count);
	int GetMaxPlayerHealthReal();
	/*int GetCurrentPlayerHealthReal();*/
};

