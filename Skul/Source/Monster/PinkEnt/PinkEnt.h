#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "../../Animation/AnimationController.h"
#include "../../Player/Player.h"
#include <map>

using namespace sf;

class Player;

enum class PinkEntAction
{
	Idle,
	Attack,
	Hit,
	Walk,
	Death,
};

enum class PinkEntMoveDir
{
	None = 0,
	Left,
	Right,
};

class PinkEnt
{
private:
	const float START_PINKENT_HEALTH = 50; // ���� ü��
	const float START_PINKENT_DAMAGE = 4; // ���� ������
	const float START_PINKENT_SPEED = 25; // ���� �������� ���ǵ�
	const float START_PINKENT_KNOCKBACKSPEED = 1000.f;	// �˹鿡�� ������ �Ÿ��� �������� ���ǵ�

	Vector2f position;	// PinkEnt�� ��ġ ��ǥ

	PinkEntAction action;	// ������ ���� �׼�

	Sprite sprite;	// ���� �׸�
	AnimationController animation;	// ���� �ִϸ��̼� ȿ�� 
	Sprite spriteGas;	// ���� ��ų ���� �׸�
	AnimationController animationGas;	//���� ��ų ���� �ִϸ��̼�

	std::map<std::string, Texture> texMap;

	Vector2f dir;	// ���� ��ǥ
	PinkEntMoveDir moveDir;

	Vector2f positionMonster;// ���� ��Ʈ �ڽ�
	RectangleShape shapeMonster;

	Vector2f positionMonsterSkiil; // ���� ��ų ��Ʈ�ڽ�
	RectangleShape shapeMonsterSkiil;

	bool attackAble;	// �浹Ȯ���� ���� ���� ���� Ȯ�� ����

	FloatRect pinkEntBound;	// ���� �׸� ũ���� Rect
	FloatRect pinkEntSkillBound; // ���� ��ų�� Rect

	int mHp;	// ü��
	int damage;	// ������
	float speed;	// ���ǵ�
	float knockBackSpeed; // �˹� ���ǵ�

	bool hitReady;	// ������ ���� �� �ִ��� Ȯ�� ����
	float attackDelay; // ���� ���ݱ����� �ĵ�����
	float walkDelay;	// ���� �̵������� ������
	float hitDelay;	// ���� ������ ���� �������� ������

	bool pinkEntHitCollision;	// �÷��̾����� ������ �޾��� ���� �浹ó��
	bool pinkEntSkillHitCollision;	// �÷��̾��� ��ų�� �¾��� ���� �浹ó��
	Sound attack;
public:
	bool attackReady;	// ���� ���� Ȯ�� ����

	void Init();
	PinkEnt(int x, int y);
	PinkEnt() {};
	~PinkEnt();

	void Update(float dt, Player& player);
	void AnimationUpdate(float dt, Player& player);
	void SetAction(PinkEntAction entAction, Player& player);
	void Attack(float dt, Player& player);
	void Hit(float dt, Player& player);
	void Move(float dt);
	void Death();

	Sprite GetSprite();

	FloatRect GetGlobalBound();
	FloatRect MonsterGetGlobalBound();
	FloatRect MonsterSkillGetGlobalBound();

	void GetActionIdle();
	void HitKnockBack(float dt, Player& player);

	int PinkEntDamage();
	bool IsAttackAble(float dt);
	bool IsAttackCollision(float dt, Player& player);

	void Draw(RenderWindow& window);
};

