#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "../../Animation/AnimationController.h"
#include "../../Player/Player.h"
#include <map>

using namespace sf;

class Player;

enum class PinkEntAction
{
	Idle,
	Attack,
	Hit,
	Walk,
	Death,
};

enum class PinkEntMoveDir
{
	None = 0,
	Left,
	Right,
};

class PinkEnt
{
private:
	const float START_PINKENT_HEALTH = 50; // 현재 체력
	const float START_PINKENT_DAMAGE = 4; // 현재 데미지
	const float START_PINKENT_SPEED = 25; // 현재 움직임의 스피드
	const float START_PINKENT_KNOCKBACKSPEED = 1000.f;	// 넉백에서 움직일 거리를 설정해줄 스피드

	Vector2f position;	// PinkEnt의 위치 좌표

	PinkEntAction action;	// 몬스터의 상태 액션

	Sprite sprite;	// 몬스터 그림
	AnimationController animation;	// 몬스터 애니메이션 효과 
	Sprite spriteGas;	// 몬스터 스킬 가스 그림
	AnimationController animationGas;	//몬스터 스킬 가스 애니메이션

	std::map<std::string, Texture> texMap;

	Vector2f dir;	// 방향 좌표
	PinkEntMoveDir moveDir;

	Vector2f positionMonster;// 몬스터 히트 박스
	RectangleShape shapeMonster;

	Vector2f positionMonsterSkiil; // 몬스터 스킬 히트박스
	RectangleShape shapeMonsterSkiil;

	bool attackAble;	// 충돌확인을 통해 공격 가능 확인 변수

	FloatRect pinkEntBound;	// 몬스터 그림 크기의 Rect
	FloatRect pinkEntSkillBound; // 몬스터 스킬의 Rect

	int mHp;	// 체력
	int damage;	// 데미지
	float speed;	// 스피드
	float knockBackSpeed; // 넉백 스피드

	bool hitReady;	// 공격을 받을 수 있는지 확인 변수
	float attackDelay; // 다음 공격까지의 후딜레이
	float walkDelay;	// 다음 이동까지의 딜레이
	float hitDelay;	// 다음 공격을 받을 때까지의 딜레이

	bool pinkEntHitCollision;	// 플레이어한테 공격을 받았을 때의 충돌처리
	bool pinkEntSkillHitCollision;	// 플레이어의 스킬에 맞았을 때의 충돌처리
	Sound attack;
public:
	bool attackReady;	// 공격 가능 확인 변수

	void Init();
	PinkEnt(int x, int y);
	PinkEnt() {};
	~PinkEnt();

	void Update(float dt, Player& player);
	void AnimationUpdate(float dt, Player& player);
	void SetAction(PinkEntAction entAction, Player& player);
	void Attack(float dt, Player& player);
	void Hit(float dt, Player& player);
	void Move(float dt);
	void Death();

	Sprite GetSprite();

	FloatRect GetGlobalBound();
	FloatRect MonsterGetGlobalBound();
	FloatRect MonsterSkillGetGlobalBound();

	void GetActionIdle();
	void HitKnockBack(float dt, Player& player);

	int PinkEntDamage();
	bool IsAttackAble(float dt);
	bool IsAttackCollision(float dt, Player& player);

	void Draw(RenderWindow& window);
};

