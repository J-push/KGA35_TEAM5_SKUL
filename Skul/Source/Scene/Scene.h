#pragma once
#include <SFML/Graphics.hpp>
#include "../Manager/SceneMgr.h"
#include "../Manager/ResourceMgr.h"
#include "../UIMaker.h"


class Scene
{
protected:
	Sprite spriteScoreFrame;
	UIMaker ui;
	SceneMgr& mgr;


public:
	Scene(SceneMgr& mgr);

	virtual void Init() = 0;
	virtual void Release() = 0;

	virtual void Start() = 0;
	virtual void End() = 0;

	virtual void Update(float dt) = 0;
	virtual void Draw(sf::RenderWindow* window) = 0;
};

