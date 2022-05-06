/******************************************************************************
* 작 성 자 : 진 현 섭
* 작 성 일 : 2022-05-04
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
	animation.Play("Idle");

	mHp = START_SwordMan_HEALTH;
	damage = START_SwordMan_DAMAGE;
	speed = START_SwordMan_SPEED;
	hitReady = true;
	attackReady = false;
	afterIdle = false;

	attackDelay = 3;

	mActionTime = 1.5f;
	mAttack2Time = 5.f;

	shape.setPosition(1160, 800);
	shape.setSize(Vector2f(430.f, 100.f));
	shape.setFillColor(Color::Red);
	rangeBound = shape.getGlobalBounds();
	attackAble = rangeBound.intersects(player.GetGlobalBound());
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
void SwordMan::Update(float dt)
{
	Player player;
	animation.Update(dt);

	if (!attackReady)
	{
		attackDelay -= dt;
	}
	if (attackDelay < 0)
	{
		attackDelay = 3;
		attackReady = true;
	}
	if (action != SwordManAction::Death)
	{
		if (attackReady && action != SwordManAction::Hit && attackAble)
		{
			action = SwordManAction::Attack;
			animation.Play("Attack");
		}
		else if (action != SwordManAction::Attack && action != SwordManAction::Hit)
		{
			action = SwordManAction::Idle;
			sprite.setPosition(1400, 920);
			animation.Play("Idle");
		}
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

FloatRect SwordMan::GetGlobalBound()
{
	return sprite.getGlobalBounds();
}

FloatRect SwordMan::RangeGetGlobalBound()
{
	return shape.getGlobalBounds();
}

const RectangleShape SwordMan::GetShape()
{
	return shape;
}

void SwordMan::Draw(RenderWindow& window)
{
	window.draw(sprite);
	window.draw(shape);
}
