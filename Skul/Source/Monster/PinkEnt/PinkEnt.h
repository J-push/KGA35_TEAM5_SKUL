#pragma once
#include "SFML/Graphics.hpp"
#include "../../Animation/AnimationController.h"
#include "../../Player/Player.h"
#include <map>

using namespace sf;

enum class PinkEntAction
{
	Idle,
	Attack,
	Hit,
	Walk,
	Death,
};

class PinkEnt
{
private:
	const float START_PINKENT_HEALTH = 50;
	const float START_PINKENT_DAMAGE = 20;
	const float START_PINKENT_SPEED = 10;

	Vector2f position;

	PinkEntAction action;
	
	Sprite sprite;
	AnimationController animation;
	Sprite spriteGas;
	AnimationController animationGas;

	std::map<std::string, Texture> texMap;

	Vector2f dir;

	Vector2f positionMonster;// 몬스터 히트 박스
	RectangleShape shapeMonster;

	Vector2f positionMonsterSkiil; // 몬스터 스킬 히트박스
	RectangleShape shapeMonsterSkiil;

	bool attackAble;

	FloatRect pinkEntBound;	// 몬스터 그림 크기의 Rect
	FloatRect pinkEntSkillBound; // 몬스터 스킬의 Rect

	int mHp;
	int damage;
	float speed;

	bool attackReady;
	bool hitReady;
	float afterAttack;
	float attackDelay;
	float walkDelay;
	float hitDelay;
	float changeAction;

	bool pinkEntHitCollision;	// 플레이어한테 공격을 받았을 때의 충돌처리
	bool pinkEntSkillHitCollision;	// 플레이어의 스킬에 맞았을 때의 충돌처리
	bool pinkEntMoveDir;	// 몬스터가 맵 끝에 도달했는지 체크 후 방향 바꿔줄 변수
public:
	void Init();
	PinkEnt(int x, int y);
	PinkEnt(){};
	~PinkEnt();

	void Update(float dt, Player& player);

	Sprite GetSprite();

	FloatRect GetGlobalBound();
	FloatRect MonsterGetGlobalBound();
	FloatRect MonsterSkillGetGlobalBound();

	void Draw(RenderWindow& window);
};

