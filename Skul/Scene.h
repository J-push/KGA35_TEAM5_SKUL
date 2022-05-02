#pragma once
#include <SFML/Graphics.hpp>
#include "SceneMgr.h"

class Scene
{
protected:
	sf::Text test;
	SceneMgr& mgr;
	sf::Texture texture;

public:
	Scene(SceneMgr& mgr);

	virtual void Init() = 0;
	virtual void Release() = 0;

	virtual void Start() = 0;
	virtual void End() = 0;

	virtual void Update(float dt) = 0;
	virtual void Draw(sf::RenderWindow* window) = 0;
};

