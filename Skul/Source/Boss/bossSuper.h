#pragma once

#include "../Animation/AnimationController.h"
#include "../Utils/Utils.h"


class BossSuper
{
private:
	const float DEFAULT_SPEED = 500.f;
	const float DEFAULT_DISTANCE = 1000.f;

	Sprite spriteSuper;
	AnimationController animationSuper;

	Sprite spriteSuperEffect;
	AnimationController animationSuperEffect;
	std::map<std::string, Texture> texMap;

	Vector2f position;  // 생성위치
	Vector2f direction; // 갈 방향
	float speed;        // 속도
	float distance;     // 이동거리

public:
	BossSuper();
	~BossSuper();

	void Shoot(Vector2f pos, Vector2f dir);
	void Update(float dt);


	Sprite GetSprite();
	Sprite GetEffectSprite();

};

