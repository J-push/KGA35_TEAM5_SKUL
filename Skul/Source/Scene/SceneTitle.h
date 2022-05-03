#pragma once
#include "Scene.h"
#include "../Animation/AnimationController.h"



class SceneTitle : public Scene
{
private:

	AnimationController animation;
	std::map<std::string, Texture> texMap;

	sf::Sprite spriteTitle;
	sf::Sprite spriteStart1;
	sf::Sprite spriteStart2;

	sf::Sprite spriteStart;

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

