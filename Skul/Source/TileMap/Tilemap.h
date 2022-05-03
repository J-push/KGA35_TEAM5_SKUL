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
};

/******************************************************************************
* ���� : Ÿ�ϸ��� �� �ε�������
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
	const int TILE_TYPES = 4;
	const int VERTS_IN_QUAD = 4;
	const int GROUND_WIDTH = 3200;
	const int GROUND_HEIGHT = 3200;
	sf::VertexArray tileMap;
	sf::IntRect normalGround;

public:
	Tilemap();
	void CreateGrass();
	void CreateWall();
	int CreateBackGround();
	virtual ~Tilemap();
};

