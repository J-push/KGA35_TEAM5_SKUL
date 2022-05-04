#pragma once
#include "../Animation/AnimationController.h"
#include "../Player/Player.h"
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
	const float START_BOSS_HEALTH = 100; // ���� ���� ü��
	const float START_BOSS_SPEED = 200; // ���� ���� ���ǵ�
	const float START_BOSS_DAMAGE = 20; // ���� ���� ������

	Vector2f position;	// ���� ��ġ ��ǥ

	BossAction action;	// ���� �׼� Ŭ������ ����
	BossStatus status;	// ���� �������ͽ� Ŭ������ ����

	Sprite sprite;	// ���� �׸�
	AnimationController animation;	// �ִϸ��̼� ����

	std::map<std::string, Texture> texMap;	// ���� cvs ���Ϸ� �ִϸ��̼� �ҽ� �׸��� ����

	int mHp; // ���� ���� ü��
	int damage;	 // ���� ���� ������

	int frame;
	int speed;	// ���� ���� ���ǵ�

	int testNum;	// ���� �׼� Ŭ������ ���� �׽�Ʈ ����

	float mIntro2Time;	// ���� ��Ʈ�� 2���� ���� �ð�
	float mActionTime;	// ���� ���� Ÿ���� ���� �ð�
	float mAttack2Time;	// ���� ���� ���� ��ų�� ���� �ð�
	float mOutroTime;	// ���� �׾��� ���� ���� �ð�

	bool attackReady;	// ������ �÷��̾� ���� ���� ���� �Ǵ�
	bool hitReady;	// ������ ���ݿ� ���� ���� ���� ���� �Ǵ�

	bool afterIdle;

	float mNextAttackTime;	// ���� ���ݱ����� ��� �ð�
	float attackDelay;	// ������ �ѹ� �ϰ� ���� ��� �ĵ�����

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

