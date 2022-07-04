#pragma once

#include "../Animation/AnimationController.h"
#include "../Utils/Utils.h"
#include "../Manager/ResourceMgr.h"
#include <map>
#include "../Boss/BossFire.h"
#include "../Manager/RandomMgr.h"

// �����
#include "../Manager/InputManager.h"
#include "../Player/Player.h"

enum class BossStatus
{
	INTRO,
	IDLE,
	MOVE,
	LANDING,
	FIREBALL,
	METEO,
	DIE
};

class Boss
{
private:
	int maxHp = 400;
	int currentHp = 400;
	float speed = 100;

	Sprite spriteText;

	BossStatus action;

	Sprite spriteBoss;
	Vector2f bossPosition;

	Sprite spriteEffect;
	Sprite spriteAttackEffect;

	AnimationController animation;
	AnimationController animationEffect;
	AnimationController animationAttackEffect;

	std::map<std::string, Texture> texMap;
	Texture texture;

	RectangleShape bossRect; // ���� �ǰ�����
	RectangleShape bossLandingRect; // ���� ����

	const int FIRE_SIZE = 10;
	list<BossFire *> unuseFires;
	list<BossFire *> useFires;

	int introCount;
	int count;
	int superCount = 0;
	int dieCount = 0;
	bool bossLook; // ture�� walkback

	float timer = 100;
	float dietimer = 100;
	int moveWhere;
	int whatAction;

	float hitTimer = 100;
	bool isHit;

	bool isFireAttacking;
	bool isLandingAttacking;
	bool alive;

	Time lastHit;


public:

	~Boss();
	void Init();

	void Intro(float dt);

	void Fire(Vector2f dir);
	void FireRutine(Vector2f dir, float dt);
	void SuperFire(Vector2f dir, Vector2f pos);
	void SuperFireRutine(Vector2f dir, float dt);
	void SuperFireHp();
	void Landing(Vector2f dir);

	void FirstMove(Vector2f dir, int moving);
	void Move(float dt, Vector2f dir, int moving);

	void Die(float dt);

	void Idle();

	FloatRect GetGlobalBound();
	FloatRect GetBossLanding();


	void Update(float dt, Vector2f dir);
	void Draw(RenderWindow &window);


	int GetMaxHp();
	int GetCurrentHp();


	bool underAttack(float dt);
	void SetBossHp(int damage);

	bool isAlive();

	bool UpdateCollision(Player &player);
};