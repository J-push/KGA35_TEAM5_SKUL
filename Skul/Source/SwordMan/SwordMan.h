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

	Vector2f positionRange;	// �÷��̾� �ν� ���� ����Ʋ
	RectangleShape shape;

	Vector2f positionMonster;// ���� ��Ʈ �ڽ�
	RectangleShape shapeMonster;

	Vector2f positionLeftMap;// ���� �� �浹
	RectangleShape shapeLeftMap;

	Vector2f positionRightMap;// ���� �� �浹
	RectangleShape shapeRightMap;

	Vector2f positionPlayer;// �÷��̾� �ν� ����
	RectangleShape shapeScope;

	Sprite sprite;	// �ҵ�� �׸�
	AnimationController animation;	// �ִϸ��̼� ����

	std::map<std::string, Texture> texMap;	// �ҵ�� cvs ���Ϸ� �ִϸ��̼� �ҽ� �׸��� ����

	Vector2f dir;	// 

	int mHp; // �ҵ�� ���� ü��
	int damage;	 // �ҵ�� ���� ������

	float speed;	// �ҵ�� ���� ���ǵ�

	bool attackReady;	// �ҵ���� �÷��̾� ���� ���� ���� �Ǵ�
	bool hitReady;	// �ҵ���� ���ݿ� ���� ���� ���� ���� �Ǵ�
	float afterAttack; // �ҵ�� ���� ��� �ĵ�����
	float attackDelay;	// ������ �ѹ� �ϰ� ���� ��� �ĵ�����
	float walkDelay;	// action�� �ٽ� walk�� ���ư��� �������� �����̽ð�
	float hitDelay;	// �ҵ������ �߰�Ÿ�� �ִ��� Ȯ���ϴ� �ð�

	FloatRect rangeBound;	// �÷��̾� �ν� ���� Ʋ���� �浹 ó�� üũ
	bool attackAble;

	FloatRect swordmanBound;	// ���� �׸� ũ���� Rect
	FloatRect swordmanScope;	// ���� �� �ν� ���� Rect

	bool prevMapCollision;	// ������ ���� ���� ���̶� �浹�ߴ��� Ȯ���ϴ� ����
	bool prevRightMapCollision;	// ������ ���� ���� ���̶� �浹�ߴ��� Ȯ���ϴ� ����
	bool leftMapCollision;	// ���� ���� ���̶� �浹�ߴ���, �浹������ Ʈ��
	bool rightMapCollision;	// ���� ���� ���̶� �浹�ߴ���, �ߴٸ� Ʈ��
	bool swordmanScopeCollision;	// ���� ����x, ���� �÷��̾� �νĹ����� �� ���� �־ ���ܸ� ������
	bool swordmanHitCollision;	// �÷��̾����� ������ �޾��� ���� �浹ó��
public:
	void Init();
	void Init2();
	swordman(int x, int y);
	swordman() {};
	~swordman();

	bool OnHitted();

	void Update(float dt, FloatRect playerBound, FloatRect playerAttackBound, Vector2f playerPosition, int playerDamage, std::vector<TestRectangle*> rects);

	Sprite GetSprite();

	FloatRect GetGlobalBound();
	FloatRect MonsterGetGlobalBound();
	FloatRect RangeGetGlobalBound();
	const RectangleShape GetShape();
	FloatRect LeftMapGetGlobalBound();
	FloatRect RightMapGetGlobalBound();
	FloatRect ScopeGetGlobalBound();

	void Draw(RenderWindow& window);
};

