#pragma once
#include "Scene.h"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "../Manager/InputManager.h"
#include <sstream>
#include <iostream>

using namespace sf;
using namespace std;

class Tile;
class SceneMapEditor : public Scene
{
private:
	const int TILE_TYPES = 35;
	const int VERTS_IN_QUAD = 4;
	const int MAPWIDTH = 120; 
	const int MAPHEIGHT = 70;
	const float VIEW_SPEED = 500.f;
	sf::Sprite spriteTile;
	sf::Sprite spriteBackground;
	sf::View *tileView;
	sf::View *uiView;

	Vector2i resolution;

	Vector2i mousePosScreen;
	Vector2i mousePosWindow;
	Vector2f mousePosView;
	Vector2u mousePosGrid;

	Vector2i mousePosScreen2;
	Vector2i mousePosWindow2;
	Vector2f mousePosView2;
	Vector2u mousePosGrid2;

	Vector2u downGrid;
	Vector2u upGrid;
	vector<Vector2u> finalGrid;

	vector<vector <RectangleShape>> tileMap;
	vector <TestRectangle *> blocks;

	Text text;
	Text text2;
	Font font;

	VertexArray palette;
	InputState currentInput;

	RectangleShape sampleSelector;
	RectangleShape tileSelector;
	RectangleShape *drag;


	int fromX;
	int toX;
	int fromY;
	int toY;
	int texIndex;
	int saveNum;

	float gridSizeF = 32.f;
	unsigned gridSizeU;

public:
	SceneMapEditor(SceneMgr &mgr) : Scene(mgr)/*, unsigned gridSizeU(static_cast<unsigned>(gridSizeF)),
		shape(Vector2f(gridSizeF, gridSizeF))*/ {};
	// Scene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Release() override;
	int CreateTile(int c, int r, int idx);

	void CreateBlocks(int fromX, int toX, int fromY, int toY);
	virtual void Update(float dt, RenderWindow *window, View *mainView) override;
	virtual void Start() override;
	virtual void End() override;
	virtual void Draw(sf::RenderWindow *window, View *mainView, View *uiView);
	/*int SelectIndex();
	void SaveMap(int saveNum);
	void LoadMap(int loadNum);*/
};

