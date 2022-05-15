#pragma once
#include "../Source/Animation/AnimationController.h"
#include "../Source/Utils/Utils.h"

#include "../Source/Player/Player.h"
class Player;

class BossFire
{
private:
	const float DEFAULT_SPEED = 500.f;
	const float DEFAULT_DISTANCE = 1000.f;

	Sprite spriteFireBall;
	AnimationController animation;

	Sprite spriteSuperEffect;
	AnimationController animationSuperEffect;

	Sprite spriteBomb;
	AnimationController animationsBomb;


	std::map<std::string, Texture> texMap;

	bool isActive; // 활성화
	bool isSuper;

	RectangleShape fireRect; // 범위

	Vector2f position;  // 생성위치
	Vector2f direction; // 갈 방향
	float speed;        // 속도
	float distance;     // 이동거리

public:

	BossFire();
	~BossFire();


	void SetActive(bool active);
	bool IsActive();

	void Shoot(Vector2f pos, Vector2f dir);
	void SuperShoot(Vector2f pos, Vector2f dir);
	void Stop();

	void Update(float dt);

	Sprite GetSprite();
	Sprite GetSuperEffectSprite();
	Sprite GetBombSprite();

	RectangleShape GetRect();

	FloatRect GetGlobalBound();

	bool UpdateCollision(Player &player);
};
