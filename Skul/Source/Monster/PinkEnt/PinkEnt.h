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
	const float START_PINKENT_HEALTH = 50;
	const float START_PINKENT_DAMAGE = 20;
	const float START_PINKENT_SPEED = 10;

	Vector2f position;

	PinkEntAction action;
	
	Sprite sprite;
	AnimationController animation;
	Sprite spriteGas;
	AnimationController animationGas;

	std::map<std::string, Texture> texMap;

	Vector2f dir;

	Vector2f positionMonster;// ���� ��Ʈ �ڽ�
	RectangleShape shapeMonster;

	Vector2f positionMonsterSkiil; // ���� ��ų ��Ʈ�ڽ�
	RectangleShape shapeMonsterSkiil;

	bool attackAble;

	FloatRect pinkEntBound;	// ���� �׸� ũ���� Rect
	FloatRect pinkEntSkillBound; // ���� ��ų�� Rect

	int mHp;
	int damage;
	float speed;

	bool attackReady;
	bool hitReady;
	float afterAttack;
	float attackDelay;
	float walkDelay;
	float hitDelay;
	float changeAction;

	bool pinkEntHitCollision;	// �÷��̾����� ������ �޾��� ���� �浹ó��
	bool pinkEntSkillHitCollision;	// �÷��̾��� ��ų�� �¾��� ���� �浹ó��
	bool pinkEntMoveDir;	// ���Ͱ� �� ���� �����ߴ��� üũ �� ���� �ٲ��� ����
public:
	void Init();
	PinkEnt(int x, int y);
	PinkEnt(){};
	~PinkEnt();

	void Update(float dt, Player& player);

	Sprite GetSprite();

	FloatRect GetGlobalBound();
	FloatRect MonsterGetGlobalBound();
	FloatRect MonsterSkillGetGlobalBound();

	void Draw(RenderWindow& window);
};

