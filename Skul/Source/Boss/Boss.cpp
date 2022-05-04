//#include "Boss.h"
//#include "CVS.h"
//
//#include <iostream>
//#include <ctime>
//#include <random>
//
////#define DELTA_TIME Timer::GetDeltaTime()
//
//void Boss::Init()
//{
//	srand((int)time(NULL));
//
//	position.x = 1920 * 0.5f; // 960
//	position.y = 1080 * 0.5f; // 540
//	sprite.setPosition(position);
//	sprite.setOrigin(60, 60);
//	//sprite.setScale(-1.f, 1.f);
//	animation.SetTarget(&sprite);
//
//	/*spriteAttackDrop.setPosition(1920 * 0.5f, 510);
//	spriteAttackDrop.setOrigin(60, 60);
//	aniAttackDrop.SetTarget(&spriteAttackDrop);
//
//	spriteIntro.setPosition(1920 * 0.5f, 520);
//	spriteIntro.setOrigin(60, 60);
//	aniIntro.SetTarget(&spriteIntro);*/
//
//	rapidcsv::Document clips("data_tables/animatioins/boss/boss_animation_clips.csv");
//	std::vector<std::string> colId = clips.GetColumn<std::string>("ID"); // 일반화인자를 받음
//	std::vector<int> colFps = clips.GetColumn<int>("FPS");
//	std::vector<int> colLoop = clips.GetColumn<int>("LOOP TYPE(0:Single, 1:Loop)");
//	std::vector<std::string> colPath = clips.GetColumn<std::string>("CLIP PATH");
//
//	int totalClips = colId.size();
//
//	for (int i = 0; i < totalClips; ++i)
//	{
//		AnimationClip clip;
//		clip.id = colId[i];
//		clip.fps = colFps[i];
//		clip.loopTypes = (AnimationLoopTypes)colLoop[i];
//
//		//std::string path = colPath[i];
//		rapidcsv::Document frames(colPath[i]);
//		std::vector<std::string> colTexture = frames.GetColumn<std::string>("TEXTURE PATH");
//		std::vector<int> colL = frames.GetColumn<int>("L");
//		std::vector<int> colT = frames.GetColumn<int>("T");
//		std::vector<int> colW = frames.GetColumn<int>("W");
//		std::vector<int> colH = frames.GetColumn<int>("H");
//
//		int totalFrames = colTexture.size();
//		for (int j = 0; j < totalFrames; ++j)
//		{
//			if (texMap.find(colTexture[j]) == texMap.end())
//			{
//				auto& ref = texMap[colTexture[j]];
//				ref.loadFromFile(colTexture[j]);
//			}
//			clip.frames.push_back(AnimationFrame(texMap[colTexture[j]], IntRect(colL[j], colT[j], colW[j], colH[j])));
//		}
//		animation.AddClip(clip);
//		/*	aniAttackDrop.AddClip(clip);
//			aniIntro.AddClip(clip);*/
//	}
//	animation.Play("Intro1(Left)");
//
//
//	status = BossStatus::Intro1;
//	mHp = START_BOSS_HEALTH;
//	damage = START_BOSS_DAMAGE;
//	speed = START_BOSS_SPEED;
//	hitReady = true;
//	attackReady = true;
//
//	Idlestart = true;
//	Intro1start = true;
//	Intro2start = true;
//
//	attackDelay = 3;
//	mIntroTime = 5;
//	mIntro2Time = 1.f;
//	mActionTime = 1.5f;
//	mAttack2Time = 5.f;
//	mOutroTime = 5;
//
//	testNum = 2;
//
//	currentPosition = position;
//
//	randomNum = rand() % 5 + 1;
//}
//
//Boss::~Boss()
//{
//}
//
//bool Boss::OnHitted()
//{
//	return false;
//}
//
//void Boss::UpdateInput(Event event)
//{
//	switch (event.type)
//	{
//	case Event::KeyPressed:
//		switch (event.key.code)
//		{
//		case Keyboard::A:
//			animation.Play("Idle");
//			break;
//			/*	case Keyboard::Num4:
//					animation.PlayQueue("Idle");
//					break;
//				case Keyboard::Num5:
//					animation.PlayQueue("Move");
//					break;
//				case Keyboard::Num6:
//					animation.PlayQueue("Jump");
//					break;
//			*/
//		}
//	}
//}
//
//void Boss::Update(float dt)
//{
//	animation.Update(dt);
//	//aniAttackDrop.Update(dt);
//	//aniIntro.Update(dt);
//
//	if (status != BossStatus::Death)
//	{
//		if (!attackReady)
//		{
//			mNextAttackTime += dt;
//		}
//		if (mNextAttackTime > attackDelay)
//		{
//			mNextAttackTime = 0;
//			attackReady = true;
//		}
//		switch (status)
//		{
//		case BossStatus::Intro1:
//		{
//			// 특정한 조건을 가질 때 스테이터스를 넘기게 해야 한다.
//			/*
//			조건을 정해줘서(시간의 조건을 주든,
//			키 입력을 받든, 애니메이션 로딩이 끝나면 넘기게 하든)
//			지금 현재 상태는 조건이 없기 때문에 계속 첫 프레임의 화면만 나온다.
//
//			각각의 상태(케이스)에서 각각의 시간을 받아서 그 딜레이 시간이 지난 후에 동작되게
//			해야 한다.
//			*/
//			sprite.setPosition(1920 * 0.5f, 1080 * 0.5f);
//			animation.PlayQueue("Intro1(Left)");
//			status = BossStatus::Intro2;
//			break;
//		}
//		case BossStatus::Intro2:
//			mIntro2Time -= dt;
//			if (mIntro2Time < 0)
//			{
//				sprite.setPosition(960, 400);
//				animation.Play("Intro2");
//				mIntro2Time = 1.f;
//				std::cout << "gd";
//				animation.ClearPlayQueue();
//				if (animation.ClearPlayQueueCheck())
//				{
//					status = BossStatus::Idle;
//				}
//				break;
//			}
//		case BossStatus::Idle:
//			mActionTime -= dt;
//			if (mActionTime < 0)
//			{
//				std::cout << "Idle";
//				animation.PlayQueue("Idle");
//				mActionTime = 1.5f;
//				status = BossStatus::Attack;
//
//				if (position.y != currentPosition.y)
//				{
//					std::cout << "원상태";
//					currentPosition.y -= 30;
//					sprite.setPosition(position);
//				}
//			}
//			break;
//		case BossStatus::Attack:
//			switch (testNum)
//			{
//			case 1:
//				BossAction::Attack1FireBall;
//				break;
//			case 2:
//				// 추후 x 좌표는 플레이어 좌표를 받아와서 그 위치로 이동 후 낙하스킬 발동.
//				BossAction::Attack2DropSkill;
//				mAttack2Time -= dt;
//				if (mAttack2Time < 0)
//				{
//					mAttack2Time = 5.f;
//					animation.PlayQueue("Attack2(LeftReady)");
//					animation.PlayQueue("Attack2(LeftReady2)");
//					sprite.setPosition(960, 600);
//					animation.PlayQueue("Attack2(LeftEnd)");
//					std::cout << "drop";
//					break;
//				}
//			case 3:
//				BossAction::Attack4Meteo;
//				break;
//			case 4:
//				BossAction::Walk;
//				std::cout << "Walk";
//				break;
//			case 5:
//				BossAction::Potion;
//				break;
//			}
//			break;
//		case BossStatus::Groggy:
//			break;
//		case BossStatus::Hit:
//			break;
//		case BossStatus::Death:
//			mOutroTime -= dt;
//			animation.PlayQueue("Die(Left)");
//			if (mOutroTime < 0)
//			{
//
//			}
//			break;
//		}
//	}
//}
//
//void Boss::Attack(float dt)
//{
//	switch (testNum)
//	{
//	case 1:
//		BossAction::Attack1FireBall;
//		break;
//	case 2:
//		BossAction::Attack2DropSkill;
//		mAttack2Time -= dt;
//		animation.PlayQueue("Attack2(LeftReady)");
//		animation.PlayQueue("Attack2(LeftReady2)");
//		animation.PlayQueue("Attack2(LeftEnd)");
//		status = BossStatus::Idle;
//		if (mAttack2Time < 0)
//		{
//			testNum = 4;
//			std::cout << "drop";
//			Update(dt);
//			break;
//		}
//	case 3:
//		BossAction::Attack4Meteo;
//		break;
//	case 4:
//		BossAction::Walk;
//		std::cout << "Walk";
//		break;
//	case 5:
//		BossAction::Potion;
//		break;
//	default:
//		break;
//	}
//
//}
//
//void Boss::Idle()
//{
//}
//
//void Boss::Hit()
//{
//}
//
//void Boss::Damage(int Damage)
//{
//}
//
//void Boss::AttackDamage()
//{
//}
//
//void Boss::CurrentSet(std::string clipId, BossStatus status, Direction direction)
//{
//}
//
//void Boss::MoveReset()
//{
//}
//
//bool Boss::AttackCheck(int area)
//{
//	return false;
//}
//
//void Boss::Animation()
//{
//}
//
//bool Boss::UpdateCollision()
//{
//	return false;
//}
//
//FloatRect Boss::GetGlobalBound()
//{
//	return sprite.getGlobalBounds();
//}
//
//void Boss::Draw(RenderWindow& window)
//{
//	window.draw(sprite);
//	window.draw(spriteAttackDrop);
//	window.draw(spriteIntro);
//}
