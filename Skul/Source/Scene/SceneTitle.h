#pragma once
#include "Scene.h"

class SceneTitle : public Scene
{
private:
	sf::Sprite spriteTitle;
	sf::Sprite spriteStart1;
	sf::Sprite spriteStart2;
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

