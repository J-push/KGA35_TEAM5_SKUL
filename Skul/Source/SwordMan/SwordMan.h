#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "../Animation/AnimationController.h"
#include <map>

using namespace sf;
class Player;

enum class swordmanAction
{
	Idle,
	Attack,
	Hit,
	Walk,
	Death,
};

enum class MoveDir
{
	None = 0,
	Left,
	Right,
};

class swordman
{
private:
	const float START_swordman_HEALTH = 50; // 시작 소드맨 체력
	const float START_swordman_SPEED = 70; // 시작 소드맨 스피드
	const float START_swordman_DAMAGE = 2; // 시작 소드맨 데미지
	const float START_SWORDMAN_KNOCKBACKSPEED = 1000.f;	// 넉백에서 움직일 거리를 설정해줄 스피드

	Vector2f position;	// 소드맨 위치 좌표

	swordmanAction action;	// 소드맨 액션 클래스의 변수

	Vector2f positionMonster;// 몬스터 히트 박스
	RectangleShape shapeMonster;

	Vector2f swordManAttackRectPosition;	// 소드맨 공격 렉트
	RectangleShape shapeSwordManAttackRect;

	Vector2f positionLeftMap;// 좌측 벽 충돌
	RectangleShape shapeLeftMap;

	Vector2f positionRightMap;// 우측 벽 충돌
	RectangleShape shapeRightMap;

	Sprite sprite;	// 소드맨 그림
	AnimationController animation;	// 애니메이션 변수

	std::map<std::string, Texture> texMap;	// 소드맨 cvs 파일로 애니메이션 소스 그리는 변수

	Vector2f dir;	// 방향 설정
	MoveDir moveDir;

	FloatRect swordmanBound;	// 몬스터 그림 크기의 Rect
	FloatRect swordManAttackBound; // 몬스터 공격 그림 크기의 Rect

	int mHp; // 소드맨 현재 체력
	int damage;	 // 소드맨 현재 데미지

	float speed;	// 소드맨 현재 스피드
	float knockBackSpeed; // 넉백 스피드

	bool attackReady;	// 소드맨이 플레이어 공격 가능 여부 판단
	bool hitReady;	// 소드맨이 공격에 맞을 때의 가능 여부 판단
	float afterAttack; // 소드맨 공격 모션 후딜레이
	float attackDelay;	// 공격을 한번 하고 나서 잠깐 후딜레이
	float walkDelay;	// action이 다시 walk로 돌아가기 전까지의 딜레이시간
	float hitDelay;	// 소드맨한테 추가타가 있는지 확인하는 시간

	bool attackAble;	// 플레이어 히트 박스와의 충돌로 공격 가능 판단
	bool leftMapCollision;	// 현재 좌측 맵이랑 충돌했는지, 충돌했으면 트루
	bool rightMapCollision;	// 현재 우측 맵이랑 충돌했는지, 했다면 트루
	bool swordmanHitCollision;	// 플레이어한테 공격을 받았을 때의 충돌처리
	bool swordmanSkillHitCollision;	// 플레이어의 스킬에 맞았을 때의 충돌처리

	Sound attack;
public:
	void Init();
	swordman(int x, int y);
	swordman() {};
	~swordman();

	void Update(float dt, Player& player);
	void AnimationUpdate(float dt, Player& player);
	void SetAction(swordmanAction swordManAction, Player& player);
	void Attack(float dt, Player& player);
	void Hit(float dt, Player& player);
	void Move(float dt);
	void Death(float dt);

	Sprite GetSprite();

	FloatRect GetGlobalBound();
	FloatRect MonsterGetGlobalBound();
	FloatRect LeftMapGetGlobalBound();
	FloatRect RightMapGetGlobalBound();
	FloatRect MonsterAttackGetGlobalBound();

	void GetActionIdle();
	void swordManAttackRectDirLeft();
	void swordManAttackRectDirRight();
	void HitKnockBack(float dt, Player& player);

	int SwordManDamage();
	bool IsAttackAble(float dt);

	void Draw(RenderWindow& window);
};

