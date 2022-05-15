#pragma once
#include "Scene.h"
#include "../Scene/SceneMapEditor.h"

class SceneMenu : public Scene
{
public:

	SceneMenu(SceneMgr& mgr) : Scene(mgr) {};
	SceneMapEditor map;

	// Scene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Release() override;
	virtual void Start() override;
	virtual void End() override;
	virtual void Update(float dt, RenderWindow *window, View *mainView) override;
	virtual void Draw(sf::RenderWindow *window, View *mainView, View *uiView) override;
};

