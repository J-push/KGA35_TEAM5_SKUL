/******************************************************************************
* �� �� �� : �� �� ��
* �� �� �� : 2022-05-04
* ��    �� : Boss�� ������ �����Ѵ�.
* �� �� �� :
*******************************************************************************/
/*include�� ���*/
#include "Boss.h"
#include "../Animation/rapidcsv.h"

#include <iostream>
#include <ctime>
#include <random>


/**********************************************************
* ���� : ������ �ʱ�ȭ�Ѵ�.
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
	std::vector<std::string> colId = clipsBoss.GetColumn<std::string>("ID"); // �Ϲ�ȭ���ڸ� ����
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
* ���� : ���� ������ �� ������ ������ ������ �޾��� ���� ó�� �Լ�
***********************************************************/
bool Boss::OnHitted()
{
	return false;
}

/**********************************************************
* ���� : ���� �ִϸ��̼��� ����� ������ ����� Ȯ���ϱ� ���� �Լ�.
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
* ���� : ���� ���� ó�� �Լ�
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
			// Ư���� ������ ���� �� �������ͽ��� �ѱ�� �ؾ� �Ѵ�.
			/*
			������ �����༭(�ð��� ������ �ֵ�,
			Ű �Է��� �޵�, �ִϸ��̼� �ε��� ������ �ѱ�� �ϵ�)
			���� ���� ���´� ������ ���� ������ ��� ù �������� ȭ�鸸 ���´�.

			������ ����(���̽�)���� ������ �ð��� �޾Ƽ� �� ������ �ð��� ���� �Ŀ� ���۵ǰ�
			�ؾ� �Ѵ�.
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
					std::cout << "���� ����";
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
				// ���� x,y ��ǥ�� �÷��̾� ��ǥ�� �޾ƿͼ� �� ��ġ�� �̵� �� ���Ͻ�ų �ߵ�.
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
* ���� : �Ƹ� ���Ŀ� ���� ���� �ٽ� �����ϰ� �ȴٸ� ������ �Լ�
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
