#pragma once
#include "../Animation/AnimationController.h"
#include "../Player/Player.h"
#include "../TileMap/Tilemap.h"
#include <map>

using namespace sf;

enum class swordmanAction
{
	Idle,
	Attack,
	Hit,
	Walk,
	LeftWalk,
	RightWalk,
	Death,
};

class swordman
{
private:

	const float START_swordman_HEALTH = 50; // ���� �ҵ�� ü��
	const float START_swordman_SPEED = 70; // ���� �ҵ�� ���ǵ�
	const float START_swordman_DAMAGE = 20; // ���� �ҵ�� ������

	Vector2f position;	// �ҵ�� ��ġ ��ǥ

	swordmanAction action;	// �ҵ�� �׼� Ŭ������ ����

	Vector2f positionMonster;// ���� ��Ʈ �ڽ�
	RectangleShape shapeMonster;

	Vector2f positionLeftMap;// ���� �� �浹
	RectangleShape shapeLeftMap;

	Vector2f positionRightMap;// ���� �� �浹
	RectangleShape shapeRightMap;

	Sprite sprite;	// �ҵ�� �׸�
	AnimationController animation;	// �ִϸ��̼� ����

	std::map<std::string, Texture> texMap;	// �ҵ�� cvs ���Ϸ� �ִϸ��̼� �ҽ� �׸��� ����

	Vector2f dir;	// 

	FloatRect swordmanBound;	// ���� �׸� ũ���� Rect

	int mHp; // �ҵ�� ���� ü��
	int damage;	 // �ҵ�� ���� ������

	float speed;	// �ҵ�� ���� ���ǵ�

	bool attackReady;	// �ҵ���� �÷��̾� ���� ���� ���� �Ǵ�
	bool hitReady;	// �ҵ���� ���ݿ� ���� ���� ���� ���� �Ǵ�
	float afterAttack; // �ҵ�� ���� ��� �ĵ�����
	float attackDelay;	// ������ �ѹ� �ϰ� ���� ��� �ĵ�����
	float walkDelay;	// action�� �ٽ� walk�� ���ư��� �������� �����̽ð�
	float hitDelay;	// �ҵ������ �߰�Ÿ�� �ִ��� Ȯ���ϴ� �ð�

	bool attackAble;	// �÷��̾� ��Ʈ �ڽ����� �浹�� ���� ���� �Ǵ�
	bool prevMapCollision;	// ������ ���� ���� ���̶� �浹�ߴ��� Ȯ���ϴ� ����
	bool prevRightMapCollision;	// ������ ���� ���� ���̶� �浹�ߴ��� Ȯ���ϴ� ����
	bool leftMapCollision;	// ���� ���� ���̶� �浹�ߴ���, �浹������ Ʈ��
	bool rightMapCollision;	// ���� ���� ���̶� �浹�ߴ���, �ߴٸ� Ʈ��
	bool swordmanHitCollision;	// �÷��̾����� ������ �޾��� ���� �浹ó��
	bool swordmanSkillHitCollision;	// �÷��̾��� ��ų�� �¾��� ���� �浹ó��
public:
	void Init();
	swordman(int x, int y);
	swordman() {};
	~swordman();

	bool OnHitted();

	void Update(float dt, FloatRect playerBound, FloatRect playerAttackBound, FloatRect playerSkiilBound,Vector2f playerPosition, int playerDamage, std::vector<TestRectangle*> rects);

	Sprite GetSprite();

	FloatRect GetGlobalBound();
	FloatRect MonsterGetGlobalBound();
	FloatRect LeftMapGetGlobalBound();
	FloatRect RightMapGetGlobalBound();

	void Draw(RenderWindow& window);
};

