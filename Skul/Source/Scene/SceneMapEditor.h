#pragma once
#include "Scene.h"

class SceneMapEditor : public Scene
{
private:
	sf::Sprite spriteTile;
public:
	SceneMapEditor(SceneMgr& mgr) : Scene(mgr) {};

	// Scene��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Start() override;
	virtual void End() override;
	virtual void Draw(sf::RenderWindow* window) override;
};

