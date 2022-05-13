#pragma once
#include <SFML/Graphics.hpp>
#include "../Animation/AnimationController.h"
#include <map>
#include "../Manager/InputManager.h"
#include "../TileMap/Tilemap.h"
#include "../../TestRectangle.h"
#include "../Utils/Utils.h"
#include "../SwordMan/SwordMan.h"

using namespace sf;

enum class PlayerState		//추가
{
	IDLE,
	MOVE,
	ATTACK,
	SKILLATTACK,
	COMBOATTACK,
	JUMP,
	DOWN,
	DASH,
};


class Player
{
private:
	const float PLAYER_SIZE = 1.5f;				//플레이어 scale 크기
	const float LEFT_PLAYER_SIZE = -1.5f;		//플레이어 애니매이션 반전
	const float START_PLAYER_HEALTH = 100;		//시작 플레이어 체력;
	const float START_PLAYER_SPEED = 200;		//시작 플레이어 속도;
	const float START_PLAYER_STR = 10;			//시작 플레이어 공격력
	const float GRAVITY_POWER = 980.f;			//중력
	const float DASH_COOLTIME = 3.f;			//대쉬 쿨타임
	const float ATTACK_DELAY = 0.3f;			//공격 딜레이
	
	PlayerState currentAction = PlayerState::IDLE;					//플레이어 상태값


	Texture texture;

	Sprite SpritePlayer;						//player 그리기
	Vector2f playerPosition;					//player 좌표

	Sprite spriteSkill;							//스킬 그리기
	Vector2f skillPosition;						//스킬 위치

	AnimationController animation;				//player 애니메이션
	AnimationController skillAnimation;				//스킬 애니메이션


	IntRect gameMap;

	Vector2i resolution;

	std::map<std::string, Texture> texMap;		//맵관련
	Tilemap tileMap;							//맵관련


	//사각형 rect 3개
	RectangleShape playerRect;
	RectangleShape playerAttackRect;
	RectangleShape playerSkillRect;

	float stateDt;								//델타타임

	float valocity;							//중력

	bool isLeft;								//왼쪽으로 바라보는지 오른쪽으로 바라보는지

	bool isDash;								//대쉬했니?

	

	bool isJump;								//점프했니?
	bool isDoubleJump;	//2단점프가능?
	bool isGround;
	bool isDown;								//점프후 내려가는지
	bool isAttack;								//공격했니?
	bool isSkill;								//스킬썻니?


	float jumpForce = 0.0f;						//점프 위치
	Vector2f oldJumpPos;						//점프 전 위치

	float attackDelay;							//공격딜레이


	Vector2f dashPosition;						

	float playerSpeed;							//player 속도

	int maxPlayerHealth;						//player 최대 체력
	int currentPlayerHealth;					//player 현재 체력

	int playerAttackDamage;						//공격 데미지

	float skillDown;							//스킬 내려오는 속도
	Vector2f tempPos;




public:
	void Init();
	void SkillInit();

	
	void Spawn(IntRect arena, Vector2i res, int tileSize);

	void UpdateInput(float dt);
	void Update(float dt, std::vector<TestRectangle*> rects);

	void AnimationUpdate(float dt);
	void SetState(PlayerState newAction);

	void Move();
	void Attack();
	void SkillAttack();
	void Dash();
	void Jump();
	void PlayerConllision(std::vector<TestRectangle*> rects);




	Vector2f GetPosition();
	Sprite GetSprite();
	virtual FloatRect GetGlobalBound();
	void Draw(RenderWindow &window);


	// 재휘 추가 최대, 현재체력 받아오기
	int GetMaxPlayerHealth();
	int GetCurrentPlayerHealth();
	void JeaHit();
	Vector2f GetPlayerPosition();

	FloatRect GetPlayerRect();
	FloatRect GetPlayerAttackRect();
	FloatRect GetPlayerSkiilRect();

	int GetPlayerDamage();	// 평타 데미지

	
	void GetStateIdle();
};

