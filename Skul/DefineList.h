#pragma once


#define TILE_MAP_SIZE_X 60
#define TILE_MAP_SIZE_Y 30

enum class InputState
{
	BLOCK,
	GROUND,
	NONE
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