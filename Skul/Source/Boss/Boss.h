#pragma once
#include "../Animation/AnimationController.h"
#include "../Player/Player.h"
#include <map>

using namespace sf;

enum class BossAction
{
	Attack1FireBall = 1,
	Attack2DropSkill,
	Attack4Meteo,
	Walk,
	Potion,
};

enum class BossStatus
{
	Intro1,
	Intro2,
	Idle,
	Attack,
	Groggy,
	Hit,
	Death,
};

class Boss
{
private:
	const float START_BOSS_HEALTH = 100; // 시작 보스 체력
	const float START_BOSS_SPEED = 200; // 시작 보스 스피드
	const float START_BOSS_DAMAGE = 20; // 시작 보스 데미지

	Vector2f position;	// 보스 위치 좌표

	BossAction action;	// 보스 액션 클래스의 변수
	BossStatus status;	// 보스 스테이터스 클래스의 변수

	Sprite sprite;	// 보스 그림
	AnimationController animation;	// 애니메이션 변수

	std::map<std::string, Texture> texMap;	// 보스 cvs 파일로 애니메이션 소스 그리는 변수

	int mHp; // 보스 현재 체력
	int damage;	 // 보스 현재 데미지

	int frame;
	int speed;	// 보스 현재 스피드

	int testNum;	// 보스 액션 클래스에 대한 테스트 숫자

	float mIntro2Time;	// 보스 인트로 2번의 시작 시간
	float mActionTime;	// 보스 공격 타임의 시작 시간
	float mAttack2Time;	// 보스 낙하 공격 스킬의 시작 시간
	float mOutroTime;	// 보스 죽었을 때의 퇴장 시간

	bool attackReady;	// 보스가 플레이어 공격 가능 여부 판단
	bool hitReady;	// 보스가 공격에 맞을 때의 가능 여부 판단

	bool afterIdle;

	float mNextAttackTime;	// 다음 공격까지의 대시 시간
	float attackDelay;	// 공격을 한번 하고 나서 잠깐 후딜레이

public:
	void Init();
	~Boss();

	bool OnHitted();

	void UpdateInput(Event event);
	void Update(float dt);

	void Attack(float dt);
	void Idle();
	void Hit();
	void Damage(int Damage);
	void AttackDamage();

	void MoveReset();
	bool AttackCheck(int area);

	void Animation();

	bool UpdateCollision();

	FloatRect GetGlobalBound();

	void Draw(RenderWindow& window);
};

