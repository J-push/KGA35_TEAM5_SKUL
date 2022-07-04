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

	Vector2f position;  // ������ġ
	Vector2f direction; // �� ����
	float speed;        // �ӵ�
	float distance;     // �̵��Ÿ�

public:
	BossSuper();
	~BossSuper();

	void Shoot(Vector2f pos, Vector2f dir);
	void Update(float dt);


	Sprite GetSprite();
	Sprite GetEffectSprite();

};

