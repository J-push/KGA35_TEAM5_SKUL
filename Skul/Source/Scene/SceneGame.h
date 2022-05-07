#pragma once
#include "Scene.h"
#include "../Player/Player.h"
#include "../SwordMan/SwordMan.h"
#include "../TileMap/Tilemap.h"
#include "../UIMaker.h"
#include "../Utils/ChangeMouse.h"
#include "../../TestRectangle.h"
#include <vector>




class SceneGame : public Scene
{
private:
	float backGroundX = 1920.f / 1332.f;
	float backGroundY = 1080.f / 850.f;
	Tilemap tilemap;
	sf::Sprite spriteBackground;
	Player player;

	SwordMan SwordMan;
	MouseCursor mouseCursor;
	UIMaker ui;

public:
	SceneGame(SceneMgr& mgr) : Scene(mgr) {};

	virtual void Init() override;
	virtual void Release() override;
	virtual void Start() override;
	virtual void End() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow* window) override;
};

