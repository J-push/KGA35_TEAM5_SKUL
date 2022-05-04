#pragma once
#include <SFML/Graphics.hpp>
#include "../Animation/AnimationController.h"
#include <map>
#include "../Manager/InputManager.h"

using namespace sf;

class Player
{
private:
	const float START_PLAYER_HEALTH = 100;		//시작 플레이어 체력;
	const float START_PLAYER_SPEED = 200;		//시작 플레이어 속도;
	const float START_PLAYER_STR = 10;			//시작 플레이어 공격력
	const float GRAVITY_POWER = 980.f;			//중력

	Texture texture;

	Sprite SpritePlayer;						//player 그리기
	Vector2f mPlayerPosition;					//player 좌표
	Vector2f mLastDir;
	AnimationController animation;

	IntRect gameMap;
	Vector2i resolution;

	std::map<std::string, Texture> texMap;


	int mTileSize;								//타일의 크기

	bool isJump;								//점프했니?

	float mSpeed;								//player 속도

	int mMaxPlayerHealth;						//player 최대 체력
	int mCurrentPlayerHealth;					//player 현재 체력

	int mPlayerType;							//뼈 타입? 아직 미정

	bool mPlayerDash;							//player대쉬 유무
	float mDashCoolTime;						//대쉬 쿨타임

	int mPlayerAttackDamage;					//공격 데미지

	float mSkillCoolTime;						//스킬 쿨타임
public:
	void Init();
	void Start();
	void End();

	void Spawn(IntRect arena, Vector2i res, int tileSize);

	void Move(float speed);
	void Dash();
	void Jump();

	void UpdateInput();
	void Update(float dt);

	Sprite GetSprite();

	void Draw(RenderWindow &window);



};

