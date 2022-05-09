#pragma once
#include "Scene.h"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "../TileMap/Tilemap.h"

class SceneMapEditor : public Scene
{
private:
	sf::Sprite spriteTile;
	sf::Sprite spriteBackground;
	sf::View *tileView;
	sf::View *mapSampleView;
	Vector2i resolution;
	int saveNum;

	Vector2f selectTile;

public:
	SceneMapEditor(SceneMgr& mgr) : Scene(mgr) {};
	
	// Scene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Start() override;
	virtual void End() override;
	virtual void Draw(sf::RenderWindow* window) override;

	int SelectIndex();
	void SaveMap(int saveNum);
	void LoadMap(int loadNum);
};

