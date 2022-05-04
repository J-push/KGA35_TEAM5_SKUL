#pragma once
#include "Scene.h"
#include "../Animation/AnimationController.h"
#include "../Manager/InputManager.h"
#include "../Utils/ChangeMouse.h"


class SceneTitle : public Scene
{
private:

	MouseCursor mouseCursor;

	AnimationController animationGameStart;
	AnimationController animationMapEdit;

	RectangleShape shapeGameStart;
	Vector2f positionGameStart;

	sf::Sprite spriteStart;
	sf::Sprite spriteMapEdit;

	std::map<std::string, Texture> texMap;

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

