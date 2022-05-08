#pragma once
#include "../Animation/AnimationController.h"
#include "../Player/Player.h"
#include "../TileMap/Tilemap.h"
#include <map>

using namespace sf;

enum class SwordManAction
{
	Idle,
	Attack,
	Hit,
	Walk,
	LeftWalk,
	RightWalk,
	Death,
};

class SwordMan
{
private:

	const float START_SwordMan_HEALTH = 100; // ���� ���� ü��
	const float START_SwordMan_SPEED = 70; // ���� ���� ���ǵ�
	const float START_SwordMan_DAMAGE = 20; // ���� ���� ������

	Vector2f position;	// ���� ��ġ ��ǥ

	SwordManAction action;	// ���� �׼� Ŭ������ ����

	Vector2f positionRange;	// �÷��̾� �ν� ���� ����Ʋ
	RectangleShape shape;

	Vector2f positionMonster;// ���� ��Ʈ �ڽ�
	RectangleShape shapeMonster;

	Vector2f positionLeftMap;// ���� �� �浹
	RectangleShape shapeLeftMap;

	Vector2f positionRightMap;// ���� �� �浹
	RectangleShape shapeRightMap;

	Sprite sprite;	// ���� �׸�
	AnimationController animation;	// �ִϸ��̼� ����

	std::map<std::string, Texture> texMap;	// ���� cvs ���Ϸ� �ִϸ��̼� �ҽ� �׸��� ����

	Vector2f dir;

	int mHp; // ���� ���� ü��
	int damage;	 // ���� ���� ������

	int frame;
	float speed;	// ���� ���� ���ǵ�

	bool attackReady;	// ������ �÷��̾� ���� ���� ���� �Ǵ�
	bool hitReady;	// ������ ���ݿ� ���� ���� ���� ���� �Ǵ�
	float afterAttack; // ���� ���� ��� �ĵ�����
	float IdleDelay;
	float attackDelay;	// ������ �ѹ� �ϰ� ���� ��� �ĵ�����
	float walkDelay;

	FloatRect rangeBound;	// �÷��̾� �ν� ���� Ʋ���� �浹 ó�� üũ
	bool attackAble;

	FloatRect swordManBound;	// ���� �׸� ũ���� Rect

	bool playerCollision;
	bool prevMapCollision;
	bool prevRightMapCollision;
	bool swordManCollision;
	bool leftMapCollision;
	bool rightMapCollision;
public:
	void Init();
	~SwordMan();

	bool OnHitted();

	void Update(float dt, FloatRect playerBound, std::vector<TestRectangle*> rects);

	Sprite GetSprite();

	FloatRect GetGlobalBound();
	FloatRect MonsterGetGlobalBound();
	FloatRect RangeGetGlobalBound();
	const RectangleShape GetShape();
	FloatRect LeftMapGetGlobalBound();
	FloatRect RightMapGetGlobalBound();

	void InitialLeftDir();
	void InitialRightDir();

	void Draw(RenderWindow& window);
};

