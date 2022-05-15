/******************************************************************************
* 작 성 자 : 진 현 섭
* 작 성 일 : 2022-05-13
* 내    용 : PinkEnt의 동작을 구현한다.
* 수 정 일 :
*******************************************************************************/
/*include될 헤더*/
#include "PinkEnt.h"
#include "../../Animation/rapidcsv.h"
#include <iostream>

/**********************************************************
* 설명 : PinkEnt를 초기화한다.
***********************************************************/
void PinkEnt::Init()
{
	sprite.setScale(2.f, 2.f);
	sprite.setPosition(position);
	sprite.setOrigin(36, 61);
	animation.SetTarget(&sprite);

	spriteGas.setScale(2.f, 2.f);
	spriteGas.setPosition(position);
	spriteGas.setOrigin(36, 61);
	animationGas.SetTarget(&spriteGas);

	rapidcsv::Document clipsPinkEnt("data_tables/animations/Monster/PinkEnt/PinkEnt_animation_clips.csv");
	std::vector<std::string> colId = clipsPinkEnt.GetColumn<std::string>("ID"); // 일반화인자를 받음
	std::vector<int> colFps = clipsPinkEnt.GetColumn<int>("FPS");
	std::vector<int> colLoop = clipsPinkEnt.GetColumn<int>("LOOP TYPE(0:Single, 1:Loop)");
	std::vector<std::string> colPath = clipsPinkEnt.GetColumn<std::string>("CLIP PATH");

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
		animationGas.AddClip(clip);
	}

	mHp = START_PINKENT_HEALTH;
	damage = START_PINKENT_DAMAGE;
	speed = START_PINKENT_SPEED;
	knockBackSpeed = START_PINKENT_KNOCKBACKSPEED;
	hitReady = true;
	attackReady = false;

	attackDelay = 0.f;
	walkDelay = 2;
	hitDelay = 0.5f;
	moveDir = PinkEntMoveDir::Left;

	shapeMonster.setFillColor(Color::Transparent);
	shapeMonster.setOutlineColor(Color::Yellow);
	shapeMonster.setOutlineThickness(2);

	shapeMonsterSkiil.setFillColor(Color::Transparent);
	shapeMonsterSkiil.setOutlineColor(Color::Blue);
	shapeMonsterSkiil.setOutlineThickness(2);

	attackBuffer.loadFromFile("sound/pinkent/attack.wav");
	attack.setBuffer(attackBuffer);

	dir.x = -1.f;
	dir.y = 0.f;
	float length = sqrt(dir.x * dir.x + dir.y * dir.y);
	if (length > 0)
	{
		dir /= length;
	}
	action = PinkEntAction::Idle;
}

/**********************************************************
* 설명 : 몬스터의 위치를 설정해준다.
***********************************************************/
PinkEnt::PinkEnt(int x, int y)
{
	position = Vector2f(x, y);
}

PinkEnt::~PinkEnt()
{
}

/**********************************************************
* 설명 : 몬스터의 상태 및 애니메이션을 업데이트 해준다.
***********************************************************/
void PinkEnt::Update(float dt, Player& player)
{
	animation.Update(dt);
	animationGas.Update(dt);

	AnimationUpdate(dt, player);

	pinkEntBound = shapeMonster.getGlobalBounds();
	pinkEntSkillBound = shapeMonsterSkiil.getGlobalBounds();
	attackAble = pinkEntSkillBound.intersects(player.GetPlayerRect());

	pinkEntHitCollision = pinkEntBound.intersects(player.GetPlayerAttackRect());
	pinkEntSkillHitCollision = pinkEntBound.intersects(player.GetPlayerSkiilRect());

	shapeMonster.setSize(Vector2f(80.f, 90.f));
	shapeMonster.setPosition(position.x, position.y - 25);
	shapeMonster.setOrigin(36, 61);

	shapeMonsterSkiil.setSize(Vector2f(370.f, 250.f));
	shapeMonsterSkiil.setPosition(position.x - 170, position.y - 120);
	shapeMonsterSkiil.setOrigin(36, 61);
}

/**********************************************************
* 설명 : 몬스터의 상태에 따른 애니메이션을 업데이트 해준다.
***********************************************************/
void PinkEnt::AnimationUpdate(float dt, Player& player)
{
	switch (action)
	{
	case PinkEntAction::Idle:
		if (player.GetPlayerPosition().x < position.x)
		{
			animation.PlayQueue("Idle(Left)");
		}
		else
		{
			animation.PlayQueue("Idle(Right)");
		}
		sprite.setOrigin(37, 66);

		walkDelay -= dt;
		if (!attackAble && walkDelay < 0)
		{
			walkDelay = 2;
			SetAction(PinkEntAction::Walk, player);
		}
		if (pinkEntHitCollision || pinkEntSkillHitCollision)
		{
			SetAction(PinkEntAction::Hit, player);
		}

		if (attackAble)
		{
			IsAttackAble(dt);

			if (attackReady)
			{
				attackReady = false;
				SetAction(PinkEntAction::Attack, player);
			}
		}
		break;
	case PinkEntAction::Attack:
		Attack(dt, player);
		if (pinkEntHitCollision || pinkEntSkillHitCollision)
		{
			SetAction(PinkEntAction::Hit, player);
		}
		break;
	case PinkEntAction::Hit:
		Hit(dt, player);
		if (!pinkEntHitCollision && !pinkEntSkillHitCollision)
		{
			SetAction(PinkEntAction::Idle, player);
		}
		if (mHp <= 0)
		{
			SetAction(PinkEntAction::Death, player);
		}
		break;
	case PinkEntAction::Walk:
		Move(dt);
		if (attackAble)
		{
			attackReady = false;
			SetAction(PinkEntAction::Attack, player);
		}
		if (pinkEntHitCollision || pinkEntSkillHitCollision)
		{
			SetAction(PinkEntAction::Hit, player);
		}
		break;
	case PinkEntAction::Death:
		Death();
		break;
	default:
		break;
	}
}

/**********************************************************
* 설명 : 몬스터의 상태를 설정해준다.
***********************************************************/
void PinkEnt::SetAction(PinkEntAction entAction, Player& player)
{
	action = entAction;

	switch (entAction)
	{
	case PinkEntAction::Idle:
		break;
	case PinkEntAction::Attack:
		attack.play();
		player.Hit(4);

		if (player.GetPlayerPosition().x < position.x)
		{
			moveDir = PinkEntMoveDir::Left;
			animation.Play("AttackReady(Left)");
			sprite.setOrigin(35, 56);
		}
		else
		{
			moveDir = PinkEntMoveDir::Right;
			animation.Play("AttackReady(Right)");
			sprite.setOrigin(35, 56);
		}

		spriteGas.setPosition(position.x - 140, position.y - 50);
		animationGas.Play("EntGas");
		animationGas.OnComplete = std::bind(&PinkEnt::GetActionIdle, this);
		break;
	case PinkEntAction::Hit:
		if (player.GetPlayerPosition().x < position.x)
		{
			moveDir = PinkEntMoveDir::Left;
			animation.Play("Hit(Left)");
		}
		else
		{
			moveDir = PinkEntMoveDir::Right;
			animation.Play("Hit(Right)");
		}
		break;
	case PinkEntAction::Walk:
		if (moveDir == PinkEntMoveDir::Left)
		{
			animation.Play("Walk(Left)");
		}
		else if (moveDir == PinkEntMoveDir::Right)
		{
			animation.Play("Walk(Right)");
		}
		break;
	case PinkEntAction::Death:
		break;
	default:
		break;
	}
}

/**********************************************************
* 설명 : 몬스터의 공격 함수
***********************************************************/
void PinkEnt::Attack(float dt, Player& player)
{
	sprite.setOrigin(35, 56);
}

/**********************************************************
* 설명 : 몬스터가 공격을 받았을 때의 처리 함수
***********************************************************/
void PinkEnt::Hit(float dt, Player& player)
{
	sprite.setOrigin(36, 61);
	hitReady = false;
	hitDelay -= dt;
	if (hitDelay < 0)
	{
		hitReady = true;
		hitDelay = 0.5f;
		pinkEntHitCollision = false;
		pinkEntSkillHitCollision = false;
		mHp -= player.GetPlayerDamage();
		HitKnockBack(dt, player);
	}
}

/**********************************************************
* 설명 : 몬스터의 이동을 처리해줄 함수
***********************************************************/
void PinkEnt::Move(float dt)
{
	Vector2f limitMinMove(800, 600);
	Vector2f limitMaxMove(1150, 600);

	sprite.setOrigin(36, 61);

	if (position.x < limitMinMove.x)
	{
		position.x = limitMinMove.x;
		animation.Play("Walk(Right)");
		moveDir = PinkEntMoveDir::Right;
	}
	else if (position.x > limitMaxMove.x)
	{
		position.x = limitMaxMove.x;
		animation.Play("Walk(Left)");
		moveDir = PinkEntMoveDir::Left;
	}

	if (moveDir == PinkEntMoveDir::Left)
	{
		animation.ClearPlayQueue();
		animation.PlayQueue("Walk(Left)");
		dir.x = -1.f;
		dir.y = 0.f;
		float length = sqrt(dir.x * dir.x + dir.y * dir.y);
		if (length > 0)
		{
			dir /= length;
		}
	}
	if (moveDir == PinkEntMoveDir::Right)
	{
		animation.ClearPlayQueue();
		animation.PlayQueue("Walk(Right)");
		dir.x = 1.f;
		dir.y = 0.f;
		float length = sqrt(dir.x * dir.x + dir.y * dir.y);
		if (length > 0)
		{
			dir /= length;
		}
	}
	position += dir * dt * speed;
	sprite.setPosition(position);
}

/**********************************************************
* 설명 : 몬스터가 죽었을 때의 처리 함수
***********************************************************/
void PinkEnt::Death()
{
	animation.Stop();
}

/**********************************************************
* 설명 : 몬스터 그림 반환
***********************************************************/
Sprite PinkEnt::GetSprite()
{
	return sprite;
}

/**********************************************************
* 설명 : 몬스터 그림 틀 반환
***********************************************************/
FloatRect PinkEnt::GetGlobalBound()
{
	return sprite.getGlobalBounds();
}

/**********************************************************
* 설명 :몬스터 히트박스의 틀 반환
***********************************************************/
FloatRect PinkEnt::MonsterGetGlobalBound()
{
	return shapeMonster.getGlobalBounds();
}

/**********************************************************
* 설명 : 몬스터 스킬 박스의 틀 반환
***********************************************************/
FloatRect PinkEnt::MonsterSkillGetGlobalBound()
{
	return shapeMonsterSkiil.getGlobalBounds();
}

/**********************************************************
* 설명 : 플레이 되는 애니메이션의 프레임 끝에 도달하면 액션 상태를 변경해줄 함수
***********************************************************/
void PinkEnt::GetActionIdle()
{
	action = PinkEntAction::Idle;
}

/**********************************************************
* 설명 : 몬스터가 공격을 받았을 때의 넉백 거리 지정 함수
***********************************************************/
void PinkEnt::HitKnockBack(float dt, Player& player)
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
int PinkEnt::PinkEntDamage()
{
	return damage;
}

bool PinkEnt::IsAttackAble(float dt)
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

bool PinkEnt::IsAttackCollision(float dt, Player& player)
{
	if (pinkEntSkillBound.intersects(player.GetPlayerRect()))
	{
		return true;
	}
	return false;
}

/**********************************************************
* 설명 : 몬스터를 화면에 그려줄 함수
***********************************************************/
void PinkEnt::Draw(RenderWindow& window)
{
	if (action != PinkEntAction::Death)
	{
		window.draw(shapeMonsterSkiil);
		window.draw(shapeMonster);
		window.draw(sprite);
		if (action == PinkEntAction::Attack)
		{
			window.draw(spriteGas);
		}
	}
}
