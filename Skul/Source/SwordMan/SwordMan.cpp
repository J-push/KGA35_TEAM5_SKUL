/******************************************************************************
* 작 성 자 : 진 현 섭
* 작 성 일 : 2022-05-06
* 내    용 : SwordMan의 동작을 구현한다.
* 수 정 일 :
*******************************************************************************/
/*include될 헤더*/
#include "../SwordMan/SwordMan.h"
#include "../Animation/rapidcsv.h"
#include <iostream>
#include <ctime>
#include <random>


/**********************************************************
* 설명 : 보스를 초기화한다.
***********************************************************/
void SwordMan::Init()
{
	srand((int)time(NULL));

	position.x = 1400; // 960
	position.y = 920; // 540
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

	rapidcsv::Document clipsSwordMan("data_tables/animations/SwordMan/swordman_animation_clips.csv");
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
		/*	aniAttackDrop.AddClip(clip);
			aniIntro.AddClip(clip);*/
	}
	animation.Play("Walk");

	mHp = START_SwordMan_HEALTH;
	damage = START_SwordMan_DAMAGE;
	speed = START_SwordMan_SPEED;
	hitReady = true;
	attackReady = false;

	attackDelay = 0;
	walkDelay = 3;

	shape.setPosition(1165, 800);
	shape.setSize(Vector2f(430.f, 100.f));
	shape.setFillColor(Color::Red);

	shapeLeftMap.setPosition(1050, 800);
	shapeLeftMap.setSize(Vector2f(100.f, 100.f));
	shapeLeftMap.setFillColor(Color::Blue);

	shapeRightMap.setPosition(1600, 800);
	shapeRightMap.setSize(Vector2f(100.f, 100.f));
	shapeRightMap.setFillColor(Color::Green);

	action = SwordManAction::Idle;
}

SwordMan::~SwordMan()
{
}

/**********************************************************
* 설명 : 아직 구현은 안 했지만 보스가 공격을 받았을 때의 처리 함수
***********************************************************/
bool SwordMan::OnHitted()
{
	return false;
}

/**********************************************************
* 설명 : 보류
***********************************************************/
void SwordMan::UpdateInput(Event event)
{
	switch (event.type)
	{
	case Event::KeyPressed:
		switch (event.key.code)
		{
		case Keyboard::A:
			animation.Play("Idle");
			break;
		case Keyboard::B:
			animation.Play("Hit");
			break;
		case Keyboard::C:
			animation.Play("Attack");
			break;
		case Keyboard::D:
			animation.Play("Walk");
			break;
		}
	}
}

/**********************************************************
* 설명 : 보스 동작 처리 함수
***********************************************************/
void SwordMan::Update(float dt, FloatRect playerBound)
{
	// 플레이어 포인터로 받아오든 레퍼런스로 받아오던
	animation.Update(dt);

	rangeBound = shape.getGlobalBounds();
	attackAble = rangeBound.intersects(playerBound);

	leftMapBound = shapeLeftMap.getGlobalBounds();
	leftMapCrash = leftMapBound.intersects(leftMapBound);

	if (mHp <= 0)
	{
		action = SwordManAction::Death;
	}

	if (!attackReady)
	{
		attackDelay -= dt;
	}
	if (attackAble && attackDelay < 0)
	{
		attackDelay = 3;
		attackReady = true;
	}
	if (action != SwordManAction::Death)
	{
		if (action == SwordManAction::Attack)
		{
			std::cout << "공격";
			animation.ClearPlayQueue();
			animation.PlayQueue("Attack");
			attackReady = false;
			if (!attackReady)
			{
				action = SwordManAction::Walk;
			}
		}
		if (action == SwordManAction::Idle)
		{
			animation.PlayQueue("Idle");
			if (attackReady && attackAble)
			{
				action = SwordManAction::Attack;
			}
		}
		if (action == SwordManAction::Walk)
		{
			animation.PlayQueue("Walk");
			if (attackReady && attackAble)
			{
				action = SwordManAction::Attack;
			}

		}
	}
	else if (action == SwordManAction::Death)
	{
		animation.Stop();
	}
}

/**********************************************************
* 설명 : 아마 추후에 보스 패턴 다시 구현하게 된다면 수정할 함수
***********************************************************/
void SwordMan::Attack(float dt)
{


}

void SwordMan::Idle()
{
}

void SwordMan::Hit()
{
}

void SwordMan::Damage(int Damage)
{
}

void SwordMan::AttackDamage()
{
}

void SwordMan::MoveReset()
{
}

bool SwordMan::AttackCheck(int area)
{
	return false;
}

void SwordMan::Animation()
{
}

bool SwordMan::UpdateCollision()
{
	return false;
}

/**********************************************************
* 설명 : 소드맨 그림 반환
***********************************************************/
Sprite SwordMan::GetSprite()
{
	return sprite;
}

/**********************************************************
* 설명 : 소드맨 그림 4좌표의 틀 반환
***********************************************************/
FloatRect SwordMan::GetGlobalBound()
{
	return sprite.getGlobalBounds();
}

/**********************************************************
* 설명 : 플레이어와의 충돌 더미 반환해줄 함수
***********************************************************/
FloatRect SwordMan::RangeGetGlobalBound()
{
	return shape.getGlobalBounds();
}

/**********************************************************
* 설명 : 플레이어와의 충돌 더미를 반환해주는 함수
***********************************************************/
const RectangleShape SwordMan::GetShape()
{
	return shape;
}

/**********************************************************
* 설명 :좌측 맵과의 충돌 더미 반환 함수
***********************************************************/
FloatRect SwordMan::LeftMapGetGlobalBound()
{
	return shapeLeftMap.getGlobalBounds();
}

/**********************************************************
* 설명 : 좌측 맵과의 충돌 더미를 반환해주는 함수
***********************************************************/
const RectangleShape SwordMan::GetLeftMapShape()
{
	return shapeLeftMap;
}

/**********************************************************
* 설명 :우측 맵과의 충돌 더미 반환 함수
***********************************************************/
FloatRect SwordMan::RightMapGetGlobalBound()
{
	return shapeRightMap.getGlobalBounds();
}

/**********************************************************
* 설명 :우측 맵과의 충돌 더미를 반환해주는 함수
***********************************************************/
const RectangleShape SwordMan::GetRightMapShape()
{
	return shapeRightMap;
}

/**********************************************************
* 설명 :그림 그려주는 함수
***********************************************************/
void SwordMan::Draw(RenderWindow& window)
{
	window.draw(shape);
	window.draw(shapeLeftMap);
	window.draw(shapeRightMap);
	window.draw(sprite);
}
