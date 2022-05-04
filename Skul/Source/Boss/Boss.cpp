/******************************************************************************
* 작 성 자 : 진 현 섭
* 작 성 일 : 2022-05-04
* 내    용 : Boss의 동작을 구현한다.
* 수 정 일 :
*******************************************************************************/
/*include될 헤더*/
#include "Boss.h"
#include "../Animation/rapidcsv.h"

#include <iostream>
#include <ctime>
#include <random>


/**********************************************************
* 설명 : 보스를 초기화한다.
***********************************************************/
void Boss::Init()
{
	srand((int)time(NULL));

	position.x = 1920 * 0.5f; // 960
	position.y = 1080 * 0.5f; // 540
	sprite.setScale(2.f, 2.f);
	sprite.setPosition(position);
	sprite.setOrigin(60, 60);
	//sprite.setScale(-1.f, 1.f);
	animation.SetTarget(&sprite);

	/*spriteAttackDrop.setPosition(1920 * 0.5f, 510);
	spriteAttackDrop.setOrigin(60, 60);
	aniAttackDrop.SetTarget(&spriteAttackDrop);

	spriteIntro.setPosition(1920 * 0.5f, 520);
	spriteIntro.setOrigin(60, 60);
	aniIntro.SetTarget(&spriteIntro);*/

	rapidcsv::Document clipsBoss("data_tables/animations/boss/boss_animation_clips.csv");
	std::vector<std::string> colId = clipsBoss.GetColumn<std::string>("ID"); // 일반화인자를 받음
	std::vector<int> colFps = clipsBoss.GetColumn<int>("FPS");
	std::vector<int> colLoop = clipsBoss.GetColumn<int>("LOOP TYPE(0:Single, 1:Loop)");
	std::vector<std::string> colPath = clipsBoss.GetColumn<std::string>("CLIP PATH");

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
		/*	aniAttackDrop.AddClip(clip);
			aniIntro.AddClip(clip);*/
	}
	animation.Play("Intro1(Left)");


	status = BossStatus::Intro1;
	mHp = START_BOSS_HEALTH;
	damage = START_BOSS_DAMAGE;
	speed = START_BOSS_SPEED;
	hitReady = true;
	attackReady = true;
	afterIdle = false;

	attackDelay = 3;

	mIntro2Time = 1.f;
	mActionTime = 1.5f;
	mAttack2Time = 5.f;
	mOutroTime = 5;

	testNum = 2;
}

Boss::~Boss()
{
}

/**********************************************************
* 설명 : 아직 구현은 안 했지만 보스가 공격을 받았을 때의 처리 함수
***********************************************************/
bool Boss::OnHitted()
{
	return false;
}

/**********************************************************
* 설명 : 보스 애니메이션이 제대로 구현이 榮쩝 확인하기 위한 함수.
***********************************************************/
void Boss::UpdateInput(Event event)
{
	switch (event.type)
	{
	case Event::KeyPressed:
		switch (event.key.code)
		{
		case Keyboard::A:
			animation.Play("Idle");
			break;
			/*	case Keyboard::Num4:
					animation.PlayQueue("Idle");
					break;
				case Keyboard::Num5:
					animation.PlayQueue("Move");
					break;
				case Keyboard::Num6:
					animation.PlayQueue("Jump");
					break;
			*/
		}
	}
}

/**********************************************************
* 설명 : 보스 동작 처리 함수
***********************************************************/
void Boss::Update(float dt)
{
	Player player;
	animation.Update(dt);
	//aniAttackDrop.Update(dt);
	//aniIntro.Update(dt);

	if (status != BossStatus::Death)
	{
		if (!attackReady)
		{
			mNextAttackTime += dt;
		}
		if (mNextAttackTime > attackDelay)
		{
			mNextAttackTime = 0;
			attackReady = true;
		}
		switch (status)
		{
		case BossStatus::Intro1:
		{
			// 특정한 조건을 가질 때 스테이터스를 넘기게 해야 한다.
			/*
			조건을 정해줘서(시간의 조건을 주든,
			키 입력을 받든, 애니메이션 로딩이 끝나면 넘기게 하든)
			지금 현재 상태는 조건이 없기 때문에 계속 첫 프레임의 화면만 나온다.

			각각의 상태(케이스)에서 각각의 시간을 받아서 그 딜레이 시간이 지난 후에 동작되게
			해야 한다.
			*/
			sprite.setPosition(1800, 770);
			animation.PlayQueue("Intro1(Left)");
			status = BossStatus::Intro2;
			break;
		}
		case BossStatus::Intro2:
			mIntro2Time -= dt;
			if (mIntro2Time < 0)
			{
				sprite.setPosition(1800, 370);
				sprite.setOrigin(20.5, 31.5);
				animation.Play("Intro2");
				mIntro2Time = 1.f;
				std::cout << "gd";
				animation.ClearPlayQueue();
				if (animation.ClearPlayQueueCheck())
				{
					status = BossStatus::Idle;
				}
				break;
			}
		case BossStatus::Idle:
			mActionTime -= dt;
			if (mActionTime < 0 && status == BossStatus::Idle)
			{
				sprite.setPosition(1800, 400);
				sprite.setOrigin(21, 31);
				if (afterIdle)
				{
					std::cout << "전투 시작";
					position.x = position.x;
					position.y = 600 - 200;
					sprite.setPosition(position);
				}
				std::cout << "Idle";
				animation.PlayQueue("Idle");
				mActionTime = 3.3f;
				status = BossStatus::Attack;
			}
			break;
		case BossStatus::Attack:
			switch (testNum)
			{
			case 1:
				BossAction::Attack1FireBall;
				break;
			case 2:
				// 추후 x,y 좌표는 플레이어 좌표를 받아와서 그 위치로 이동 후 낙하스킬 발동.
				BossAction::Attack2DropSkill;
				mAttack2Time -= dt;
				if (mAttack2Time < 0)
				{
					afterIdle = true;
					mAttack2Time = 5.f;
					sprite.setPosition(960, 600);
					animation.PlayQueue("Attack2(LeftReady)");
					animation.PlayQueue("Attack2(LeftReady2)");
					// ------------------------------------------
					animation.PlayQueue("Attack2(LeftEnd)");
					std::cout << "drop";
					status = BossStatus::Idle;
					break;
				}
			case 3:
				BossAction::Attack4Meteo;
				break;
			case 4:
				BossAction::Walk;
				std::cout << "Walk";
				break;
			case 5:
				BossAction::Potion;
				break;
			}
			break;
		case BossStatus::Groggy:
			break;
		case BossStatus::Hit:
			break;
		case BossStatus::Death:
			mOutroTime -= dt;
			animation.PlayQueue("Die(Left)");
			if (mOutroTime < 0)
			{

			}
			break;
		}
	}
}

/**********************************************************
* 설명 : 아마 추후에 보스 패턴 다시 구현하게 된다면 수정할 함수
***********************************************************/
void Boss::Attack(float dt)
{
	switch (testNum)
	{
	case 1:
		BossAction::Attack1FireBall;
		break;
	case 2:
		BossAction::Attack2DropSkill;
		mAttack2Time -= dt;
		animation.PlayQueue("Attack2(LeftReady)");
		animation.PlayQueue("Attack2(LeftReady2)");
		animation.PlayQueue("Attack2(LeftEnd)");
		status = BossStatus::Idle;
		if (mAttack2Time < 0)
		{
			testNum = 4;
			std::cout << "drop";
			Update(dt);
			break;
		}
	case 3:
		BossAction::Attack4Meteo;
		break;
	case 4:
		BossAction::Walk;
		std::cout << "Walk";
		break;
	case 5:
		BossAction::Potion;
		break;
	default:
		break;
	}

}

void Boss::Idle()
{
}

void Boss::Hit()
{
}

void Boss::Damage(int Damage)
{
}

void Boss::AttackDamage()
{
}

void Boss::MoveReset()
{
}

bool Boss::AttackCheck(int area)
{
	return false;
}

void Boss::Animation()
{
}

bool Boss::UpdateCollision()
{
	return false;
}

FloatRect Boss::GetGlobalBound()
{
	return sprite.getGlobalBounds();
}

void Boss::Draw(RenderWindow& window)
{
	window.draw(sprite);
}
