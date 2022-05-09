#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "../Utils/Utils.h"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
enum class TileType
{
	Null,
	Wall,
	Ground,
	HalfGround,
	Start,
	Exit,
};

/******************************************************************************
* 설명 : 타일마다 뭐 부딪히는지
*******************************************************************************/
enum class ColliderTag
{
	None,
	Ground,
	HalfGround,
	Player,
	Monster,
	Exit,
	NPC,
	RayCast,
	PlayerAttack,
	MonsterAttack,
};

using namespace sf;
class Tilemap
{
private:
	const int TILE_SIZE = 32;
	const int TILE_TYPES = 3;
	const int VERTS_IN_QUAD = 4;
	const int BACKGROUND_WIDTH = 3200;
	const int BACKGROUND_HEIGHT = 3200;
	sf::VertexArray tileMap;
	sf::IntRect backGround;

public:
	Tilemap();
	void CreateGrass();
	void CreateWall();
	int CreateBackGround();
	virtual ~Tilemap();
};

