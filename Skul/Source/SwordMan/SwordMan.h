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
	const float START_swordman_HEALTH = 50; // ���� �ҵ�� ü��
	const float START_swordman_SPEED = 70; // ���� �ҵ�� ���ǵ�
	const float START_swordman_DAMAGE = 2; // ���� �ҵ�� ������
	const float START_SWORDMAN_KNOCKBACKSPEED = 1000.f;	// �˹鿡�� ������ �Ÿ��� �������� ���ǵ�

	Vector2f position;	// �ҵ�� ��ġ ��ǥ

	swordmanAction action;	// �ҵ�� �׼� Ŭ������ ����

	Vector2f positionMonster;// ���� ��Ʈ �ڽ�
	RectangleShape shapeMonster;

	Vector2f swordManAttackRectPosition;	// �ҵ�� ���� ��Ʈ
	RectangleShape shapeSwordManAttackRect;

	Vector2f positionLeftMap;// ���� �� �浹
	RectangleShape shapeLeftMap;

	Vector2f positionRightMap;// ���� �� �浹
	RectangleShape shapeRightMap;

	Sprite sprite;	// �ҵ�� �׸�
	AnimationController animation;	// �ִϸ��̼� ����

	std::map<std::string, Texture> texMap;	// �ҵ�� cvs ���Ϸ� �ִϸ��̼� �ҽ� �׸��� ����

	Vector2f dir;	// ���� ����
	MoveDir moveDir;

	FloatRect swordmanBound;	// ���� �׸� ũ���� Rect
	FloatRect swordManAttackBound; // ���� ���� �׸� ũ���� Rect

	int mHp; // �ҵ�� ���� ü��
	int damage;	 // �ҵ�� ���� ������

	float speed;	// �ҵ�� ���� ���ǵ�
	float knockBackSpeed; // �˹� ���ǵ�

	bool attackReady;	// �ҵ���� �÷��̾� ���� ���� ���� �Ǵ�
	bool hitReady;	// �ҵ���� ���ݿ� ���� ���� ���� ���� �Ǵ�
	float afterAttack; // �ҵ�� ���� ��� �ĵ�����
	float attackDelay;	// ������ �ѹ� �ϰ� ���� ��� �ĵ�����
	float walkDelay;	// action�� �ٽ� walk�� ���ư��� �������� �����̽ð�
	float hitDelay;	// �ҵ������ �߰�Ÿ�� �ִ��� Ȯ���ϴ� �ð�

	bool attackAble;	// �÷��̾� ��Ʈ �ڽ����� �浹�� ���� ���� �Ǵ�
	bool leftMapCollision;	// ���� ���� ���̶� �浹�ߴ���, �浹������ Ʈ��
	bool rightMapCollision;	// ���� ���� ���̶� �浹�ߴ���, �ߴٸ� Ʈ��
	bool swordmanHitCollision;	// �÷��̾����� ������ �޾��� ���� �浹ó��
	bool swordmanSkillHitCollision;	// �÷��̾��� ��ų�� �¾��� ���� �浹ó��

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

