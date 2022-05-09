#pragma once

#include "../Source/Animation/AnimationController.h"

enum class BossStatus		
{
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


	Sprite spriteBoss;
	Vector2f bossPosition;


	AnimationController animation;
	std::map<std::string, Texture> texMap;

	RectangleShape bossRect; // ���� �ǰ�����



public:
	Boss();

	void Init();

	virtual void Update(float dt);

	void Draw(RenderWindow &window);

};

