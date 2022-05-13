#pragma once
#include "SFML/Graphics.hpp"
#include "../../Animation/AnimationController.h"
#include "../../Player/Player.h"
#include <map>

using namespace sf;

enum class PinkEntAction
{
	Idle,
	Attack,
	Hit,
	Walk,
	Death,
};

class PinkEnt
{
private:
	const float START_PINKENT_HEALTH = 50; // ���� ü��
	const float START_PINKENT_DAMAGE = 20; // ���� ������
	const float START_PINKENT_SPEED = 10; // ���� �������� ���ǵ�

	Vector2f position;	// PinkEnt�� ��ġ ��ǥ

	PinkEntAction action;	// ������ ���� �׼�
	
	Sprite sprite;	// ���� �׸�
	AnimationController animation;	// ���� �ִϸ��̼� ȿ�� 
	Sprite spriteGas;	// ���� ��ų ���� �׸�
	AnimationController animationGas;	//���� ��ų ���� �ִϸ��̼�

	std::map<std::string, Texture> texMap;

	Vector2f dir;	// ���� ��ǥ

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

	bool attackReady;	// ���� ���� Ȯ�� ����
	bool hitReady;	// ������ ���� �� �ִ��� Ȯ�� ����
	float attackDelay; // ���� ���ݱ����� �ĵ�����
	float walkDelay;	// ���� �̵������� ������
	float hitDelay;	// ���� ������ ���� �������� ������

	bool pinkEntHitCollision;	// �÷��̾����� ������ �޾��� ���� �浹ó��
	bool pinkEntSkillHitCollision;	// �÷��̾��� ��ų�� �¾��� ���� �浹ó��
	bool pinkEntMoveDir;	// ���Ͱ� �� ���� �����ߴ��� üũ �� ���� �ٲ��� ����
public:
	void Init();
	PinkEnt(int x, int y);
	PinkEnt(){};
	~PinkEnt();

	void Update(float dt, Player& player);
	void AnimationUpdate(float dt, Player& player);
	void SetAction(PinkEntAction entAction, Player& player);
	void Attack(float dt, Player& player);
	void Hit(float dt, Player& player);
	void Move(float dt);
	void Death(float dt);

	Sprite GetSprite();

	FloatRect GetGlobalBound();
	FloatRect MonsterGetGlobalBound();
	FloatRect MonsterSkillGetGlobalBound();

	void GetActionIdle();

	void Draw(RenderWindow& window);
};

