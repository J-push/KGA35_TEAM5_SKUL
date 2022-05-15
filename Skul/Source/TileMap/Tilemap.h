#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "../Utils/Utils.h"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "../Manager/ResourceMgr.h"
#include "../../ColliderRect.h"
#include "../../DefineList.h"

using namespace sf;
class Tilemap
{
private:
	const int TILE_SIZE = 32;
	const int TILE_TYPES = 35;
	const int VERTS_IN_QUAD = 4;
	const int BACKGROUND_WIDTH = 3200;
	const int BACKGROUND_HEIGHT = 3200;
	const int WIN_X = 1920;
	const int WIN_Y = 1080;
	std::vector <ColliderRect*> rects;
	VertexArray tileMap;
	IntRect backGround;
	Sprite spriteTile;
	int texIndex;

public:
	void Init();
	int CreateBackGround();
	void CreateTestRect();

	std::vector<ColliderRect*> GetRects();
	virtual void Draw(sf::RenderWindow *window);
};

