#pragma once
#include <SFML/Graphics.hpp>
#include "../Manager/SceneMgr.h"

class Scene
{
protected:
	//Text test;
	//Texture texture;
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

