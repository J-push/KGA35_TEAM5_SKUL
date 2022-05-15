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

	virtual void Init();
	virtual void Release();

	virtual void Start();
	virtual void End();

	virtual void Update(float dt, RenderWindow *window, View *mainView);
	virtual void Draw(sf::RenderWindow *window, View *mainView, View *uiView);
};

