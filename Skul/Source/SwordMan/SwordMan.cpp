/******************************************************************************
* 작 성 자 : 진 현 섭
* 작 성 일 : 2022-05-13
* 내    용 : swordman의 동작을 구현한다.
* 수 정 일 :
*******************************************************************************/
/*include될 헤더*/
#include "../swordman/swordman.h"
#include "../Animation/rapidcsv.h"
#include <iostream>
#include <ctime>
#include <random>
#include "../Player/Player.h"


/**********************************************************
* 설명 : 소드맨를 초기화한다.
***********************************************************/
void swordman::Init()
{
	sprite.setScale(2.f, 2.f);
	sprite.setOrigin(15, 53);
	sprite.setPosition(position);
	animation.SetTarget(&sprite);

	rapidcsv::Document clipsSwordMan("data_tables/animations/swordman/swordman_animation_clips.csv");
	std::vector<std::string> colId = clipsSwordMan.GetColumn<std::string>("ID"); // 일반화인자를 받음
	std::vector<int> colFps = clipsSwordMan.GetColumn<int>("FPS");
	std::vector<int> colLoop = clipsSwordMan.GetColumn<int>("LOOP TYPE(0:Single, 1:Loop)");
	std::vector<std::string> colPath = clipsSwordMan.GetColumn<std::string>("CLIP PATH");

	int totalclips = colId.size();

	for (int i = 0; i < totalclips; ++i)
	{
		AnimationClip clip;
		clip.id = colId[i];
		clip.fps = colFps[i];
		clip.loopType = (AnimationLoopTypes)colLoop[i];

		//std::string path = colPath[i];
		rapidcsv::Document frames(colPath[i]);
		std::vector<std::string> colTexture = frames.GetColumn<std::string>("TEXTURE PATH");
		std::vector<int> colL = frames.GetColumn<int>("L");
		std::vector<int> colT = frames.GetColumn<int>("T");
		std::vector<int> colW = frames.GetColumn<int>("W");
		std::vector<int> colH = frames.GetColumn<int>("H");

		int totalFrames = colTexture.size();
		for (int j = 0; j < totalFrames; ++j)
		{
			if (texMap.find(colTexture[j]) == texMap.end())
			{
				auto& ref = texMap[colTexture[j]];
				ref.loadFromFile(colTexture[j]);
			}
			clip.frames.push_back(AnimationFrame(texMap[colTexture[j]], IntRect(colL[j], colT[j], colW[j], colH[j])));
		}
		animation.AddClip(clip);
	}

	mHp = START_swordman_HEALTH;
	damage = START_swordman_DAMAGE;
	speed = START_swordman_SPEED;
	knockBackSpeed = START_SWORDMAN_KNOCKBACKSPEED;
	hitReady = true;
	attackReady = false;

	attackDelay = 3.f;
	walkDelay = 2;
	afterAttack = 3;
	hitDelay = 1.f;
	moveDir = MoveDir::Left;

	shapeMonster.setSize(Vector2f(60.f, 100.f));
	shapeMonster.setPosition(position.x - 30, position.y - 100);
	shapeMonster.setFillColor(Color::Transparent);
	shapeMonster.setOutlineColor(Color::Yellow);
	shapeMonster.setOutlineThickness(2);

	shapeLeftMap.setPosition(1050, 800);
	shapeLeftMap.setSize(Vector2f(100.f, 100.f));
	shapeLeftMap.setFillColor(Color::Transparent);
	shapeLeftMap.setOutlineColor(Color::Blue);
	shapeLeftMap.setOutlineThickness(2);

	shapeRightMap.setPosition(1600, 800);
	shapeRightMap.setSize(Vector2f(100.f, 100.f));
	shapeRightMap.setFillColor(Color::Transparent);
	shapeRightMap.setOutlineColor(Color::Magenta);
	shapeRightMap.setOutlineThickness(2);

	dir.x = -1.f;
	dir.y = 0.f;
	float length = sqrt(dir.x * dir.x + dir.y * dir.y);
	if (length > 0)
	{
		dir /= length;
	}

	action = swordmanAction::Idle;
}

/**********************************************************
* 설명 : 몬스터의 위치를 설정해준다.
***********************************************************/
swordman::swordman(int x, int y)
{
	position = Vector2f(x, y);
}

swordman::~swordman()
{
}

/**********************************************************
* 설명 : 몬스터의 상태 및 애니메이션을 업데이트 해준다.
***********************************************************/
void swordman::Update(float dt, Player& player)
{
	animation.Update(dt);
	AnimationUpdate(dt, player);

	swordmanBound = shapeMonster.getGlobalBounds();
	swordManAttackBound = shapeSwordManAttackRect.getGlobalBounds();

	attackAble = swordManAttackBound.intersects(player.GetPlayerRect());

	leftMapCollision = swordmanBound.intersects(shapeLeftMap.getGlobalBounds());
	rightMapCollision = swordmanBound.intersects(shapeRightMap.getGlobalBounds());
	swordmanHitCollision = swordmanBound.intersects(player.GetPlayerAttackRect());
	swordmanSkillHitCollision = swordmanBound.intersects(player.GetPlayerSkiilRect());

	if (dir.x == -1.f)
	{
		swordManAttackRectDirLeft();
	}
	else if (dir.x == 1.f)
	{
		swordManAttackRectDirRight();
	}
}

/**********************************************************
* 설명 : 몬스터의 상태에 따른 애니메이션을 업데이트 해준다.
***********************************************************/
void swordman::AnimationUpdate(float dt, Player& player)
{
	switch (action)
	{
	case swordmanAction::Idle:
		if (player.GetPlayerPosition().x < position.x)
		{
			animation.PlayQueue("Idle(Left)");
		}
		else
		{
			animation.PlayQueue("Idle(Right)");
		}
		sprite.setOrigin(15, 53);

		shapeMonster.setSize(Vector2f(60.f, 100.f));
		shapeMonster.setPosition(position.x - 30, position.y - 100);

		walkDelay -= dt;
		if (!attackAble && walkDelay < 0)
		{
			walkDelay = 2;
			SetAction(swordmanAction::Walk, player);
		}
		if (swordmanHitCollision || swordmanSkillHitCollision)
		{
			SetAction(swordmanAction::Hit, player);
		}

		if (attackAble)
		{
			IsAttackAble(dt);

			if (attackReady)
			{
				attackReady = false;
				SetAction(swordmanAction::Attack, player);
			}
		}
		break;
	case swordmanAction::Attack:

		shapeMonster.setSize(Vector2f(75.f, 100.f));
		shapeMonster.setPosition(position.x - 45, position.y - 100);

		Attack(dt, player);

		sprite.setOrigin(40, 60);
		if (swordmanHitCollision || swordmanSkillHitCollision)
		{
			SetAction(swordmanAction::Hit, player);
		}
		break;
	case swordmanAction::Hit:
		hitDelay -= dt;
		hitReady = false;
		if (hitDelay < 0)
		{
			hitDelay = 0.5f;
			Hit(dt, player);
		}

		shapeMonster.setSize(Vector2f(60.f, 100.f));
		shapeMonster.setPosition(position.x - 30, position.y - 100);

		if (!swordmanHitCollision && !swordmanSkillHitCollision)
		{
			SetAction(swordmanAction::Idle, player);
		}
		if (mHp <= 0)
		{
			SetAction(swordmanAction::Death, player);
		}
		break;
	case swordmanAction::Walk:
		Move(dt);

		shapeMonster.setSize(Vector2f(60.f, 100.f));
		shapeMonster.setPosition(position.x - 30, position.y - 100);

		if (attackAble)
		{
			SetAction(swordmanAction::Attack, player);
		}
		if (swordmanHitCollision || swordmanSkillHitCollision)
		{
			SetAction(swordmanAction::Hit, player);
		}
		break;
	case swordmanAction::Death:
		Death(dt);
		break;
	default:
		break;
	}
}

/**********************************************************
* 설명 : 몬스터의 상태를 설정해준다.
***********************************************************/
void swordman::SetAction(swordmanAction swordManAction, Player& player)
{
	action = swordManAction;

	switch (swordManAction)
	{
	case swordmanAction::Idle:
		break;
	case swordmanAction::Attack:
		player.Hit(2);

		if (player.GetPlayerPosition().x < position.x)
		{
			moveDir = MoveDir::Left;
			animation.Play("Attack(Left)");
		}
		else
		{
			moveDir = MoveDir::Right;
			animation.Play("Attack(Right)");
		}

		animation.OnComplete = std::bind(&swordman::GetActionIdle, this);
		break;
	case swordmanAction::Hit:
		if (player.GetPlayerPosition().x < position.x)
		{
			moveDir = MoveDir::Left;
			animation.Play("Hit(Left)");
		}
		else
		{
			moveDir = MoveDir::Right;
			animation.Play("Hit(Right)");
		}
		break;
	case swordmanAction::Walk:
		if (moveDir == MoveDir::Left)
		{
			animation.Play("Walk(Left)");
		}
		else if (moveDir == MoveDir::Right)
		{
			animation.Play("Walk(Right)");
		}
		break;
	case swordmanAction::Death:
		break;
	default:
		break;
	}
}

/**********************************************************
* 설명 : 몬스터의 공격 함수
***********************************************************/
void swordman::Attack(float dt, Player& player)
{
}

/**********************************************************
* 설명 : 몬스터가 공격을 받았을 때의 처리 함수
***********************************************************/
void swordman::Hit(float dt, Player& player)
{
	sprite.setOrigin(30, 48);
	hitReady = true;
	hitDelay = 0.5f;
	swordmanHitCollision = false;
	swordmanSkillHitCollision = false;
	mHp -= player.GetPlayerDamage();
	HitKnockBack(dt, player);
}

/**********************************************************
* 설명 : 몬스터의 이동을 처리해줄 함수
***********************************************************/
void swordman::Move(float dt)
{
	sprite.setOrigin(27, 47);

	if (leftMapCollision)
	{
		animation.Play("Walk(Right)");
		moveDir = MoveDir::Right;
	}
	else if (rightMapCollision)
	{
		animation.Play("Walk(Left)");
		moveDir = MoveDir::Left;
	}
	if (moveDir == MoveDir::Left)
	{
		animation.ClearPlayQueue();
		animation.PlayQueue("Walk(Left)");
		rightMapCollision = false;
		dir.x = -1.f;
		dir.y = 0.f;
		float length = sqrt(dir.x * dir.x + dir.y * dir.y);
		if (length > 0)
		{
			dir /= length;
		}
		moveDir = MoveDir::None;
	}
	if (moveDir == MoveDir::Right)
	{
		animation.ClearPlayQueue();
		animation.PlayQueue("Walk(Right)");
		leftMapCollision = false;
		dir.x = 1.f;
		dir.y = 0.f;
		float length = sqrt(dir.x * dir.x + dir.y * dir.y);
		if (length > 0)
		{
			dir /= length;
		}
		moveDir = MoveDir::None;
	}
	position += dir * dt * speed;
	sprite.setPosition(position);
}

/**********************************************************
* 설명 : 몬스터가 죽었을 때의 처리 함수
***********************************************************/
void swordman::Death(float dt)
{
	animation.Stop();
}

/**********************************************************
* 설명 : 소드맨 그림 반환
***********************************************************/
Sprite swordman::GetSprite()
{
	return sprite;
}

/**********************************************************
* 설명 : 소드맨 그림 4좌표의 틀 반환
***********************************************************/
FloatRect swordman::GetGlobalBound()
{
	return sprite.getGlobalBounds();
}

/**********************************************************
* 설명 : 소드맨의 바디 히트박스
***********************************************************/
FloatRect swordman::MonsterGetGlobalBound()
{
	return shapeMonster.getGlobalBounds();
}

/**********************************************************
* 설명 : 좌측 더미맵의 글로벌 바운즈
***********************************************************/
FloatRect swordman::LeftMapGetGlobalBound()
{
	return shapeLeftMap.getGlobalBounds();
}

/**********************************************************
* 설명 :우측 더미맵의 글러벌 바운즈
***********************************************************/
FloatRect swordman::RightMapGetGlobalBound()
{
	return shapeRightMap.getGlobalBounds();
}

/**********************************************************
* 설명 : 몬스터의 우측 공격 범위 지정 함수
***********************************************************/
void swordman::swordManAttackRectDirRight()
{
	shapeSwordManAttackRect.setSize(Vector2f(100.f, 100.f));
	shapeSwordManAttackRect.setPosition(position.x + 85, position.y - 100);
	shapeSwordManAttackRect.setFillColor(Color::Transparent);
	shapeSwordManAttackRect.setOutlineColor(Color::Red);
	shapeSwordManAttackRect.setOutlineThickness(2);
	shapeSwordManAttackRect.setScale(-1.f, 1.f);
}

/**********************************************************
* 설명 : 몬스터의 좌측 공격 범위 지정 함수
***********************************************************/
void swordman::swordManAttackRectDirLeft()
{
	shapeSwordManAttackRect.setSize(Vector2f(100.f, 100.f));
	shapeSwordManAttackRect.setPosition(position.x - 85, position.y - 100);
	shapeSwordManAttackRect.setFillColor(Color::Transparent);
	shapeSwordManAttackRect.setOutlineColor(Color::Red);
	shapeSwordManAttackRect.setOutlineThickness(2);
	shapeSwordManAttackRect.setScale(1.f, 1.f);
}

/**********************************************************
* 설명 : 몬스터가 플레이어를 공격 가능한 범위 그림 반환 함수
***********************************************************/
FloatRect swordman::MonsterAttackGetGlobalBound()
{
	return shapeSwordManAttackRect.getGlobalBounds();
}

/**********************************************************
* 설명 : 플레이 되는 애니메이션의 프레임 끝에 도달하면 액션 상태를 변경해줄 함수
***********************************************************/
void swordman::GetActionIdle()
{
	action = swordmanAction::Idle;
}

/**********************************************************
* 설명 : 몬스터가 공격을 받았을 때의 넉백 거리 지정 함수
***********************************************************/
void swordman::HitKnockBack(float dt, Player& player)
{
	if (player.GetPlayerPosition().x < position.x)
	{
		position.x -= dir.x * knockBackSpeed * dt;
	}
	else
	{
		position.x += dir.x * knockBackSpeed * dt;
	}
	sprite.setPosition(position);
}

/**********************************************************
* 설명 : 몬스터의 데미지 반환
***********************************************************/
int swordman::SwordManDamage()
{
	return damage;
}

/**********************************************************
* 설명 : 몬스터의 공격 가능 판단
***********************************************************/
bool swordman::IsAttackAble(float dt)
{
	if (!attackReady)
	{
		attackDelay -= dt;
	}
	if (attackDelay < 0)
	{
		attackDelay = 3.f;
		attackReady = true;
	}

	if (attackReady)
	{
		return attackReady;
	}
}

/**********************************************************
* 설명 :그림 그려주는 함수
***********************************************************/
void swordman::Draw(RenderWindow& window)
{
	window.draw(shapeLeftMap);
	window.draw(shapeRightMap);
	if (action != swordmanAction::Death)
	{
		if (action == swordmanAction::Attack)
		{
			window.draw(shapeSwordManAttackRect);
		}
		window.draw(shapeMonster);
		window.draw(sprite);
	}
}