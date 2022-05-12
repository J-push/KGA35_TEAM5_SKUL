#pragma once

#include "../Source/Animation/AnimationController.h"
#include "../Source/Utils/Utils.h"
#include <map>
#include "../Source/BossFire.h"
#include "../Source/Manager/RandomMgr.h"

// 실험용
#include "../Source/Manager/InputManager.h"


enum class BossStatus		
{
	INTRO,
	IDLE,
	MOVE,
	LANDING,
	FIREBALL,
	METEO,
};

class Boss
{
private:
	int maxHp = 400;
	int currentHp = 400;
	float speed = 100;

	BossStatus action;

	Sprite spriteBoss;
	Vector2f bossPosition;


	AnimationController animation;
	std::map<std::string, Texture> texMap;
	Texture texture;

	RectangleShape bossRect; // 보스 피격판정

	const int FIRE_SIZE = 1;
	list<BossFire *> unuseFires;
	list<BossFire *> useFires;

	int introCount;
	int count;
	int superCount;
	bool bossLook; // ture면 walkback

	float timer = 100;
	int moveWhere;
	int whatAction;

	Time lastHit;


public:

	~Boss();
	void Init();

	void Intro(float dt);

	void Fire(Vector2f dir);
	void FireRutine(Vector2f dir, float dt);

	void SuperFire(Vector2f dir, Vector2f pos);
	void SuperFireRutine(Vector2f dir , float dt);

	void Landing(Vector2f dir);

	void FirstMove(Vector2f dir, int moving);
	void Move(float dt, Vector2f dir, int moving);

	void Idle();

	FloatRect GetGlobalBound();

	void Update(float dt, Vector2f dir);
	void Draw(RenderWindow &window);


	int GetMaxHp();
	int GetCurrentHp();
	bool underAttack(Time timeHit);
	void SetBossHp(int damage);


	void SetStateIdle();

};


