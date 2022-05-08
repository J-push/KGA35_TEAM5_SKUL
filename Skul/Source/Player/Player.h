#pragma once
#include <SFML/Graphics.hpp>
#include "../Animation/AnimationController.h"
#include <map>
#include "../Manager/InputManager.h"
#include "../TileMap/Tilemap.h"
#include "../../TestRectangle.h"
#include "../Utils/Utils.h"

using namespace sf;

enum class PlayerStatus		//추가
{
	IDLE,
	MOVE,
	ATTACK,
	COMBOATTACK,
	JUMP,
	DOWN,
	DASH,
};


class Player
{
private:
	const float PLAYER_SIZE = 1.5f;
	const float LEFT_PLAYER_SIZE = -1.5f;
	const float START_PLAYER_HEALTH = 100;		//시작 플레이어 체력;
	const float START_PLAYER_SPEED = 200;		//시작 플레이어 속도;
	const float START_PLAYER_STR = 10;			//시작 플레이어 공격력
	const float GRAVITY_POWER = 980.f;			//중력

	const float DASH_COOLTIME = 3.f;
	const float ATTACK_DELAY = 0.3f;
	
	
	Texture texture;

	Sprite SpritePlayer;						//player 그리기
	Vector2f mPlayerPosition;					//player 좌표
	Vector2f mLastDir;
	AnimationController animation;
	AnimationController skillAni;

	IntRect gameMap;
	Vector2i resolution;

	std::map<std::string, Texture> texMap;

	Tilemap tileMap;

	RectangleShape playerRect;
	RectangleShape playerAttackRect;
	RectangleShape playerSkillRect;


	float val;									//중력
	int mTileSize;								//타일의 크기

	bool isJump;								//점프했니?
	bool doDown;								//점프후 내려가는지
	float jumpForce = 0.0f;						//점프 위치
	Vector2f oldJumpPos;						//점프 전 위치


	bool isDash;								//대쉬했니?
	bool isAttack;								//공격했니?
	bool isSkill;								//스킬썻니?

	float attackDelay;							//공격딜레이

	bool canUseDash;							//대쉬 사용 가능 유무

	bool isLeft;								//왼쪽으로 바라보는지 오른쪽으로 바라보는지

	Vector2f dirDash;

	float mSpeed;								//player 속도

	int mMaxPlayerHealth;						//player 최대 체력
	int mCurrentPlayerHealth;					//player 현재 체력

	int mPlayerType;							//뼈 타입? 아직 미정

	bool mPlayerDash;							//player대쉬 유무
	float mDashCoolTime;						//대쉬 쿨타임

	int mPlayerAttackDamage;					//공격 데미지

	float mSkillCoolTime;						//스킬 쿨타임


	Sprite spriteSkill;							//스킬 그리기
	Vector2f skillPosition;						//스킬 위치
	float skillDown;
	Vector2f tempPos;



public:
	void Init();
	void SkillInit();
	void Start();
	void End();

	void Spawn(IntRect arena, Vector2i res, int tileSize);

	void Move(float speed);
	void Dash(bool isDash, float dt);
	void Jump(float dt);

	void UpdateInput(float dt);
	void Update(float dt, std::vector<TestRectangle *> rects);


	Vector2f GetPosition();
	Sprite GetSprite();
	virtual FloatRect GetGlobalBound();

	void Draw(RenderWindow &window);

	// 재휘 추가 최대, 현재체력 받아오기
	int GetMaxPlayerHealth();
	int GetCurrentPlayerHealth();




};

