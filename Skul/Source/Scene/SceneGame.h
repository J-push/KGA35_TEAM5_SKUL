#pragma once
#include "Scene.h"
#include "../Player/Player.h"
#include "../swordman/swordman.h"
#include "../TileMap/Tilemap.h"
#include "../UIMaker.h"
#include "../Utils/ChangeMouse.h"
#include "../../TestRectangle.h"
#include "../swordman/swordman.h"
#include <vector>




class SceneGame : public Scene
{
private:
	float backGroundX = 1920.f / 1332.f;
	float backGroundY = 1080.f / 850.f;
	Tilemap tilemap;
	sf::Sprite spriteBackground;
	Player player;
	std::vector<swordman*> mSwordMans;	// 좀비 여러마리 생성
	swordman* mSwordman;
	swordman* mSwordman1;
	swordman* mSwordman2;
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
	int GetMaxPlayerHealthReal();
	/*int GetCurrentPlayerHealthReal();*/
};

