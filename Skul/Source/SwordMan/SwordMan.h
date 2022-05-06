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

	Vector2f positionLeftMap;	// ���� �� �浹 ���� ����Ʋ
	RectangleShape shapeLeftMap;

	Vector2f positionRightMap;	// ���� �� �浹 ���� ����Ʋ
	RectangleShape shapeRightMap;

	Sprite sprite;	// ���� �׸�
	AnimationController animation;	// �ִϸ��̼� ����

	std::map<std::string, Texture> texMap;	// ���� cvs ���Ϸ� �ִϸ��̼� �ҽ� �׸��� ����

	int mHp; // ���� ���� ü��
	int damage;	 // ���� ���� ������

	int frame;
	int speed;	// ���� ���� ���ǵ�

	bool attackReady;	// ������ �÷��̾� ���� ���� ���� �Ǵ�
	bool hitReady;	// ������ ���ݿ� ���� ���� ���� ���� �Ǵ�

	float attackDelay;	// ������ �ѹ� �ϰ� ���� ��� �ĵ�����
	float walkDelay;

	FloatRect rangeBound;	// �÷��̾� �ν� ���� Ʋ���� �浹 ó�� üũ
	bool attackAble;

	FloatRect leftMapBound;	// ���� �ʰ��� �浹 ó�� üũ
	bool leftMapCrash;

	FloatRect rightMapBound;	// ���� �ʰ��� �浹 ó�� üũ
	bool rightMapCrash;

public:
	void Init();
	~SwordMan();

	bool OnHitted();

	void UpdateInput(Event event);
	void Update(float dt, FloatRect playerBound);

	void Attack(float dt);
	void Idle();
	void Hit();
	void Damage(int Damage);
	void AttackDamage();

	void MoveReset();
	bool AttackCheck(int area);

	void Animation();

	bool UpdateCollision();

	Sprite GetSprite();

	FloatRect GetGlobalBound();

	FloatRect RangeGetGlobalBound();
	const RectangleShape GetShape();

	FloatRect LeftMapGetGlobalBound();
	const RectangleShape GetLeftMapShape();

	FloatRect RightMapGetGlobalBound();
	const RectangleShape GetRightMapShape();

	void Draw(RenderWindow& window);
};

