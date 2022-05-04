#pragma once
#include "../Animation/AnimationController.h"
#include <map>

using namespace sf;

enum class BossAction
{
	Attack1FireBall = 1,
	Attack2DropSkill,
	Attack4Meteo,
	Walk,
	Potion,
};

enum class BossStatus
{
	Intro1,
	Intro2,
	Idle,
	Attack,
	Groggy,
	Hit,
	Death,
};

class Boss
{
private:
	const float START_BOSS_HEALTH = 100;
	const float START_BOSS_SPEED = 200;
	const float START_BOSS_DAMAGE = 20;

	Vector2f prevPosition;
	Vector2f position;
	Vector2f currentPosition;

	BossAction action;
	BossStatus status;

	Sprite sprite;
	AnimationController animation;

	Sprite spriteAttackDrop;
	AnimationController aniAttackDrop;

	Sprite spriteIntro;
	AnimationController aniIntro;

	std::map<std::string, Texture> texMap;

	int mHp;
	int damage;

	int frame;
	int speed;

	bool Idlestart;
	bool Intro1start;
	bool Intro2start;

	int randomNum;
	int testNum;

	float mIntroTime;
	float mIntro2Time;
	float mActionTime;
	float mAttack2Time;
	float mOutroTime;

	bool attackReady;
	bool hitReady;
	float mNextAttackTime;
	float attackDelay;

public:
	void Init();
	~Boss();

	bool OnHitted();

	void UpdateInput(Event event);
	void Update(float dt);

	void Attack(float dt);
	void Idle();
	void Hit();
	void Damage(int Damage);
	void AttackDamage();

	void MoveReset();
	bool AttackCheck(int area);

	void Animation();

	bool UpdateCollision();

	FloatRect GetGlobalBound();

	void Draw(RenderWindow& window);
};

