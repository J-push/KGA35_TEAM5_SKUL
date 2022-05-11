#pragma once

#include "../Source/Scene/Scene.h"
#include "../Source/Boss.h"
#include "../Source/Player/Player.h"

// SCORETEX
class SceneEnd : public Scene
{
	

public:

	SceneEnd(SceneMgr &mgr) : Scene(mgr) {};

	// Scene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Release() override;
	virtual void Start() override;
	virtual void End() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow *window) override;


};
