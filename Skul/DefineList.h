#pragma once


#define TILE_MAP_SIZE_X 60
#define TILE_MAP_SIZE_Y 30

enum class InputState
{
	BLOCK,
	IMAGE,
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
};