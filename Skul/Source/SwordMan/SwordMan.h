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
	const float START_swordman_HEALTH = 50;
	const float START_swordman_SPEED = 70;
	const float START_swordman_DAMAGE = 2;
	const float START_SWORDMAN_KNOCKBACKSPEED = 1000.f;

	Vector2f position;
	swordmanAction action;

	Vector2f positionMonster;
	RectangleShape shapeMonster;

	Vector2f swordManAttackRectPosition;
	RectangleShape shapeSwordManAttackRect;

	Vector2f positionLeftMap;
	RectangleShape shapeLeftMap;

	Vector2f positionRightMap;
	RectangleShape shapeRightMap;

	Sprite sprite;
	AnimationController animation;

	std::map<std::string, Texture> texMap;

	Vector2f dir;
	MoveDir moveDir;

	FloatRect swordmanBound;
	FloatRect swordManAttackBound;

	int mHp;
	int damage;

	float speed;
	float knockBackSpeed; 

	bool attackReady;
	bool hitReady;
	float afterAttack; 

	float attackDelay;
	float walkDelay;
	float hitDelay;


	bool attackAble;	
	bool leftMapCollision;
	bool rightMapCollision;
	bool swordmanHitCollision;
	bool swordmanSkillHitCollision;

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

