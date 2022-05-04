#pragma once
#include "Scene.h"
#include "../Player/Player.h"
#include "../TileMap/Tilemap.h"

class SceneGame : public Scene
{
private:
	float backGroundX = 1920.f / 1332.f;
	float backGroundY = 1080.f / 850.f;
	Tilemap tilemap;
	sf::Sprite spriteBackground;
	Player player;
public:
	SceneGame(SceneMgr& mgr) : Scene(mgr) {};

	// SceneÀ»(¸¦) ÅëÇØ »ó¼ÓµÊ
	virtual void Init() override;
	virtual void Release() override;
	virtual void Start() override;
	virtual void End() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow* window) override;
};

