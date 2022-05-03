#pragma once
#include "Scene.h"
#include "../Player/Player.h"
class SceneGame : public Scene
{
private:
	sf::Sprite spriteBackground;
	Player player;
	
public:
	SceneGame(SceneMgr& mgr) : Scene(mgr) {};

	// Scene��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Release() override;
	virtual void Start() override;
	virtual void End() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow* window) override;
};

