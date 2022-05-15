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
	const float START_swordman_HEALTH = 50; //  留 泥대
	const float START_swordman_SPEED = 70; //  留 ㅽ쇰
	const float START_swordman_DAMAGE = 2; //  留 곕�吏
	const float START_SWORDMAN_KNOCKBACKSPEED = 1000.f;	// 諛깆 吏 嫄곕━瑜 ㅼ댁 ㅽ쇰

	Vector2f position;	// 留 移 醫

	swordmanAction action;	// 留 ≪ 대ㅼ 蹂

	Vector2f positionMonster;// 紐ъㅽ  諛
	RectangleShape shapeMonster;

	Vector2f swordManAttackRectPosition;	// 留 怨듦꺽 �
	RectangleShape shapeSwordManAttackRect;

	Vector2f positionLeftMap;// 醫痢 踰 異⑸
	RectangleShape shapeLeftMap;

	Vector2f positionRightMap;// 곗륫 踰 異⑸
	RectangleShape shapeRightMap;

	Sprite sprite;	// 留 洹몃┝
	AnimationController animation;	// 硫댁 蹂

	std::map<std::string, Texture> texMap;	// 留 cvs 쇰 硫댁  洹몃━ 蹂

	Vector2f dir;	// 諛⑺ ㅼ
	MoveDir moveDir;

	FloatRect swordmanBound;	// 紐ъㅽ 洹몃┝ ш린 Rect
	FloatRect swordManAttackBound; // 紐ъㅽ 怨듦꺽 洹몃┝ ш린 Rect

	int mHp; // 留  泥대
	int damage;	 // 留  곕�吏

	float speed;	// 留  ㅽ쇰
	float knockBackSpeed; // 諛 ㅽ쇰

	bool attackReady;	// 留⑥ �댁 怨듦꺽 媛 щ 
	bool hitReady;	// 留⑥ 怨듦꺽 留  媛 щ 
	float afterAttack; // 留 怨듦꺽 紐⑥ �
	float attackDelay;	// 怨듦꺽 踰 怨  源 �
	float walkDelay;	// action ㅼ walk濡 媛湲 �源吏 �댁媛
	float hitDelay;	// 留⑦ 異媛媛 吏 명 媛

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

