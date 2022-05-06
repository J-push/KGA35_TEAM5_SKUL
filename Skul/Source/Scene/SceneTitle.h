#pragma once
#include "Scene.h"
#include "../Animation/AnimationController.h"
#include "../Manager/InputManager.h"
#include "../Utils/ChangeMouse.h"
#include "../UIMaker.h"



class SceneTitle : public Scene
{
private:

	MouseCursor mouseCursor;
	UIMaker ui;

	Sprite spriteTitle;




public:
	SceneTitle(SceneMgr& mgr) : Scene(mgr) {};

	// Scene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Release() override;
	virtual void Start() override;
	virtual void End() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow* window) override;


};

