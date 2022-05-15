/******************************************************************************
* 작 성 자 : 김 재 휘
* 작 성 일 : 2022-05-11
* 내    용 : bossfire의 동작을 구현한다.
* 수 정 일 :
*******************************************************************************/
#include "BossFire.h"

/**********************************************************
* 설명 : BossFire을 초기화한다.
***********************************************************/
BossFire::BossFire() : speed(DEFAULT_SPEED), distance(DEFAULT_DISTANCE)
{
	isSuper = false;

	// 충돌 확인
	fireRect.setSize(Vector2f(80, 40));
	fireRect.setFillColor(Color(140, 72, 19, 70));
	fireRect.setPosition(position);

	spriteFireBall.setScale(0.8f, 0.8f);
	Utils::SetOrigin(spriteFireBall, Pivots::CC);

	animation.SetTarget(&spriteFireBall);

	spriteSuperEffect.setScale(2.0f, 2.0f);
	spriteSuperEffect.setPosition(Vector2f(100, 100));
	animationSuperEffect.SetTarget(&spriteSuperEffect);

	spriteBomb.setScale(3.0f, 3.0f);
	spriteBomb.setPosition(Vector2f(100, 100));
	animationsBomb.SetTarget(&spriteBomb);

	rapidcsv::Document clipsFire("data_tables/animations/BossFireball/bossfireball_animation_clips.csv");
	std::vector<std::string> colId = clipsFire.GetColumn<std::string>("ID");
	std::vector<int> colFps = clipsFire.GetColumn<int>("FPS");
	std::vector<int> colLoop = clipsFire.GetColumn<int>("LOOP TYPE(0:Single, 1:Loop)");
	std::vector<std::string> colPath = clipsFire.GetColumn<std::string>("CLIP PATH");

	int totalclips = colId.size();

	for (int i = 0; i < totalclips; ++i)
	{
		AnimationClip clip;
		clip.id = colId[i];
		clip.fps = colFps[i];
		clip.loopType = (AnimationLoopTypes)colLoop[i];

		rapidcsv::Document frames(colPath[i]);
		std::vector<std::string> colTexure = frames.GetColumn<std::string>("TEXTURE PATH");
		std::vector<int> colL = frames.GetColumn<int>("L");
		std::vector<int> colT = frames.GetColumn<int>("T");
		std::vector<int> colW = frames.GetColumn<int>("W");
		std::vector<int> colH = frames.GetColumn<int>("H");

		int totalFrames = colTexure.size();
		for (int j = 0; j < totalFrames; ++j)
		{
			if (texMap.find(colTexure[j]) == texMap.end())
			{
				auto &ref = texMap[colTexure[j]];
				ref.loadFromFile(colTexure[j]);
			}
			clip.frames.push_back(AnimationFrame(texMap[colTexure[j]], IntRect(colL[j], colT[j], colW[j], colH[j])));
		}
		animation.AddClip(clip);
		animationSuperEffect.AddClip(clip);
		animationsBomb.AddClip(clip);
	}
}

BossFire::~BossFire()
{
}

/**********************************************************
* 설명 : BossFire의 작동여부를 설정한다.
***********************************************************/
void BossFire::SetActive(bool active)
{
	isActive = active;
}

/**********************************************************
* 설명 : BossFire의 작동여부를 받아온다.
***********************************************************/
bool BossFire::IsActive()
{
	return isActive;
}

/**********************************************************
* 설명 : BossFire의 기본공격을 관리한다.
***********************************************************/
void BossFire::Shoot(Vector2f pos, Vector2f dir)
{
	isSuper = false;
	speed = 500;

	animation.Play("fireball");

	SetActive(true);

	fireRect.setSize(Vector2f(80, 40));
	fireRect.setFillColor(Color(140, 72, 19, 70));

	fireRect.setPosition(position);

	Utils::SetOrigin(spriteFireBall, Pivots::LT);
	spriteFireBall.setScale(0.8f, 0.8f);


	distance = 0.f;
	position = pos;
	spriteFireBall.setPosition(pos);
	direction = Utils::Normalize(dir);
	float dgree = Utils::GetAngel(position, position + dir);
	spriteFireBall.setRotation(dgree);

	fireRect.setPosition(pos);
	fireRect.setRotation(dgree);

	spriteSuperEffect.setPosition(6000, 6000);
}

/**********************************************************
* 설명 : BossFire의 필살기를 관리한다.
***********************************************************/
void BossFire::SuperShoot(Vector2f pos, Vector2f dir)
{
	isSuper = true;
	speed = 500;

	animation.Play("fireball");
	animationSuperEffect.Play("supereffect");

	position = pos;

	SetActive(true);
	spriteSuperEffect.setPosition(position);

	position.x += 230;
	position.y += 180;

	fireRect.setSize(Vector2f(200, 100));
	fireRect.setFillColor(Color(140, 72, 19, 70));
	fireRect.setPosition(position);

	spriteFireBall.setScale(2.0f, 2.0f);

	distance = 0.f;

	spriteFireBall.setPosition(position);
	direction = Utils::Normalize(dir);
	float dgree = Utils::GetAngel(position, position + dir);
	spriteFireBall.setRotation(dgree);

	fireRect.setPosition(pos);
	fireRect.setRotation(dgree);
}

/**********************************************************
* 설명 : BossFire의 실행을 멈춘다.
***********************************************************/
void BossFire::Stop()
{
	SetActive(false);
}

/**********************************************************
* 설명 : BossFire의 업데이트를 관리한다.
***********************************************************/
void BossFire::Update(float dt)
{
	animation.Update(dt);
	animationSuperEffect.Update(dt);
	animationsBomb.Update(dt);

	position += direction * speed * dt;
	fireRect.setPosition(position);
	spriteFireBall.setPosition(position);

	if (isSuper)
	{
		if (position.y > 605)
		{
			fireRect.setPosition(Vector2f(3000, 0));
			speed = 0;
			position.y = 480;
			position.x -= 230;
			spriteFireBall.setRotation(0);
			animation.Play("bomb");
			animation.OnComplete = std::bind(&BossFire::Stop, this);
		}
		if (position.y == 480)
		{
			fireRect.setPosition(Vector2f(3000, 0));
		}
	}
	if (!isSuper)
	{
		if (position.y > 710)
		{
			fireRect.setPosition(Vector2f(3000, 0));
			speed = 0;
			position.y = 630;
			spriteFireBall.setRotation(0);
			animation.Play("attackeffect");
			animation.OnComplete = std::bind(&BossFire::Stop, this);
		}
		if (position.y == 630)
		{
			fireRect.setPosition(Vector2f(3000, 0));
		}
	}
}

/**********************************************************
* 설명 : BossFire의 sprite를 받아온다.
***********************************************************/
Sprite BossFire::GetSprite()
{
	return spriteFireBall;
}

/**********************************************************
* 설명 : 이펙트의 sprite를 받아온다.
***********************************************************/
Sprite BossFire::GetSuperEffectSprite()
{
	return spriteSuperEffect;
}

/**********************************************************
* 설명 : 폭발의 sprite를 받아온다.
***********************************************************/
Sprite BossFire::GetBombSprite()
{
	return spriteBomb;
}

/**********************************************************
* 설명 : fire의 범위를 받아온다.
***********************************************************/
RectangleShape BossFire::GetRect()
{
	return fireRect;
}

/**********************************************************
* 설명 : fire의 충돌처리를 담당한다.
***********************************************************/
bool BossFire::UpdateCollision(Player &player)
{
	FloatRect bounds = fireRect.getGlobalBounds();
	if (bounds.intersects(player.GetPlayerRect()))
	{
		Stop();
		return true;
	}
	return false;
}

