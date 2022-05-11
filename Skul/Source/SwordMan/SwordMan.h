#pragma once
#include "../Animation/AnimationController.h"
#include "../Player/Player.h"
#include "../TileMap/Tilemap.h"
#include <map>

using namespace sf;

enum class swordmanAction
{
	Idle,
	Attack,
	Hit,
	Walk,
	LeftWalk,
	RightWalk,
	Death,
};

class swordman
{
private:

	const float START_swordman_HEALTH = 50; // 시작 소드맨 체력
	const float START_swordman_SPEED = 70; // 시작 소드맨 스피드
	const float START_swordman_DAMAGE = 20; // 시작 소드맨 데미지

	Vector2f position;	// 소드맨 위치 좌표

	swordmanAction action;	// 소드맨 액션 클래스의 변수

	Vector2f positionMonster;// 몬스터 히트 박스
	RectangleShape shapeMonster;

	Vector2f positionLeftMap;// 좌측 벽 충돌
	RectangleShape shapeLeftMap;

	Vector2f positionRightMap;// 우측 벽 충돌
	RectangleShape shapeRightMap;

	Sprite sprite;	// 소드맨 그림
	AnimationController animation;	// 애니메이션 변수

	std::map<std::string, Texture> texMap;	// 소드맨 cvs 파일로 애니메이션 소스 그리는 변수

	Vector2f dir;	// 

	FloatRect swordmanBound;	// 몬스터 그림 크기의 Rect

	int mHp; // 소드맨 현재 체력
	int damage;	 // 소드맨 현재 데미지

	float speed;	// 소드맨 현재 스피드

	bool attackReady;	// 소드맨이 플레이어 공격 가능 여부 판단
	bool hitReady;	// 소드맨이 공격에 맞을 때의 가능 여부 판단
	float afterAttack; // 소드맨 공격 모션 후딜레이
	float attackDelay;	// 공격을 한번 하고 나서 잠깐 후딜레이
	float walkDelay;	// action이 다시 walk로 돌아가기 전까지의 딜레이시간
	float hitDelay;	// 소드맨한테 추가타가 있는지 확인하는 시간

	bool attackAble;	// 플레이어 히트 박스와의 충돌로 공격 가능 판단
	bool prevMapCollision;	// 이전에 좌측 더미 맵이랑 충돌했는지 확인하는 변수
	bool prevRightMapCollision;	// 이전에 우측 더미 맵이랑 충돌했는지 확인하는 변수
	bool leftMapCollision;	// 현재 좌측 맵이랑 충돌했는지, 충돌했으면 트루
	bool rightMapCollision;	// 현재 우측 맵이랑 충돌했는지, 했다면 트루
	bool swordmanHitCollision;	// 플레이어한테 공격을 받았을 때의 충돌처리
	bool swordmanSkillHitCollision;	// 플레이어의 스킬에 맞았을 때의 충돌처리
public:
	void Init();
	swordman(int x, int y);
	swordman() {};
	~swordman();

	bool OnHitted();

	void Update(float dt, FloatRect playerBound, FloatRect playerAttackBound, FloatRect playerSkiilBound,Vector2f playerPosition, int playerDamage, std::vector<TestRectangle*> rects);

	Sprite GetSprite();

	FloatRect GetGlobalBound();
	FloatRect MonsterGetGlobalBound();
	FloatRect LeftMapGetGlobalBound();
	FloatRect RightMapGetGlobalBound();

	void Draw(RenderWindow& window);
};

