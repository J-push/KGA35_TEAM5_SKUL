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
	const int TILE_TYPES = 35;
	const int VERTS_IN_QUAD = 4;
	const int BACKGROUND_WIDTH = 3200;
	const int BACKGROUND_HEIGHT = 3200;
	VertexArray tileMap;
	IntRect backGround;
	Sprite spriteTile;
	Texture texTile;
public:
	void Init();
	int CreateBackGround();
	virtual void Draw(sf::RenderWindow *window);
};

