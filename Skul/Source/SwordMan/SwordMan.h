#pragma once
#include "../Animation/AnimationController.h"
#include "../Player/Player.h"
#include <map>

using namespace sf;

enum class SwordManAction
{
	Idle,
	Attack,
	Hit,
	Walk,
	Death,
};

class SwordMan
{
private:

	const float START_SwordMan_HEALTH = 100; // ���� ���� ü��
	const float START_SwordMan_SPEED = 200; // ���� ���� ���ǵ�
	const float START_SwordMan_DAMAGE = 20; // ���� ���� ������

	Vector2f position;	// ���� ��ġ ��ǥ

	SwordManAction action;	// ���� �׼� Ŭ������ ����

	Vector2f positionRange;	// �÷��̾� �ν� ���� ����Ʋ
	RectangleShape shape;

	Sprite sprite;	// ���� �׸�
	AnimationController animation;	// �ִϸ��̼� ����

	std::map<std::string, Texture> texMap;	// ���� cvs ���Ϸ� �ִϸ��̼� �ҽ� �׸��� ����

	Player player;

	int mHp; // ���� ���� ü��
	int damage;	 // ���� ���� ������

	int frame;
	int speed;	// ���� ���� ���ǵ�

	int testNum;	// ���� �׼� Ŭ������ ���� �׽�Ʈ ����

	float mActionTime;	// ���� ���� Ÿ���� ���� �ð�
	float mAttack2Time;	// ���� ���� ���� ��ų�� ���� �ð�

	bool attackReady;	// ������ �÷��̾� ���� ���� ���� �Ǵ�
	bool hitReady;	// ������ ���ݿ� ���� ���� ���� ���� �Ǵ�

	bool afterIdle;

	float mNextAttackTime;	// ���� ���ݱ����� ��� �ð�
	float attackDelay;	// ������ �ѹ� �ϰ� ���� ��� �ĵ�����

	FloatRect rangeBound;	// �÷��̾� �ν� ���� Ʋ���� �浹 ó�� üũ
	bool attackAble;
public:
	void Init();
	~SwordMan();

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

	FloatRect RangeGetGlobalBound();
	const RectangleShape GetShape();

	void Draw(RenderWindow& window);
};

