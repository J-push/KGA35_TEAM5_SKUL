#pragma once
#include "Scene.h"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "../Manager/InputManager.h"
#include "../Player/Player.h"
#include <sstream>
#include <iostream>
#include "../Animation/rapidcsv.h"
#include "../TileMap/Map.h"
#include "../../DefineList.h"

using namespace sf;
using namespace std;

class Player;
class SceneMapEditor
{
private:
	const int TILE_TYPES = 35;
	const int VERTS_IN_QUAD = 4;
	const float VIEW_SPEED = 500.f;

	sf::Sprite spriteTile;
	sf::Sprite spriteBackground;
	sf::View *tileView;
	sf::View *uiView;

	RectangleShape shape;
	RectangleShape sampleSelector;
	RectangleShape tileSelector;
	RectangleShape *drag;

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
	vector <ColliderRect*> rects;

	Text text;
	Text text2;
	Font font;

	VertexArray palette;
	InputState currentInputState;

	string name;
	bool currentMousePosition;
	bool isDraw;
	bool currentState;

	int mapWidth = 120;
	int mapHeight = 70;
	int currentIndex;
	int texIndex;
	int saveNum;
	
	float gridSizeF = 32.f;
	unsigned gridSizeU;

public:
	void Init();
	void Release();
	void ChangeMode();
	int CreateTile(int c, int r, int idx);
	void CreateRects();
	void DeleteRects();
	void MoveMap(float dt);
	void SetView(RenderWindow *window);
    void Update(float dt, RenderWindow *window, View *mainView);
	void Draw(sf::RenderWindow *window, View *mainView, View *uiView);
	void DrawMap(sf::RenderWindow *window, View *mainView, View *uiView)
	{
		window->draw(palette, ResourceMgr::instance()->GetTexture("TILETEX"));
	}
	void LoadRect();
	void LoadImage();
	void InitMapData();
	VertexArray Getpalette();
	vector <ColliderRect *> Getrects();
	vector<vector <RectangleShape>> Gettile();
};

