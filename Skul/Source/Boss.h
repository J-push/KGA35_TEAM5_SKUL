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
	FIREBALL,
	LANDING,
	METEO,
};

class Boss
{
private:
	
	int hp;
	float speed = 100;

	BossStatus action = BossStatus::INTRO;

	Sprite spriteBoss;
	Vector2f bossPosition;


	AnimationController animation;
	std::map<std::string, Texture> texMap;
	Texture texture;

	RectangleShape bossRect; // 보스 피격판정

	const int FIRE_SIZE = 100;
	list<BossFire *> unuseFires;
	list<BossFire *> useFires;

	// 궁 발사용
	int launcher1;
	int launcher2;
	int launcher3;




public:

	~Boss();
	void Init();

	void Fire(Vector2f dir);
	void FireRutine(Vector2f dir);

	void SuperFire(Vector2f dir, Vector2f pos);
	void SuperFireRutine(Vector2f dir);

	void Move(float dt, Vector2f dir);

	void Update(float dt, Vector2f dir);

	void Draw(RenderWindow &window);


};
//void check() { cout << "dsf" << endl; }

