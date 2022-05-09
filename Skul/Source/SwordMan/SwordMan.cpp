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
	sprite.setOrigin(60, 65);
	sprite.setPosition(position);
	animation.SetTarget(&sprite);

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
	}
	animation.Play("Walk(Left)");

	mHp = START_SwordMan_HEALTH;
	damage = START_SwordMan_DAMAGE;
	speed = START_SwordMan_SPEED;
	hitReady = true;
	attackReady = false;

	attackDelay = 0;
	walkDelay = 2;
	afterAttack = 3;
	IdleDelay = 2;

	//shape.setPosition(1165, 800);
	//shape.setSize(Vector2f(430.f, 100.f));
	//shape.setFillColor(Color::Red);

	shapeMonster.setFillColor(Color::Transparent);
	shapeMonster.setOutlineColor(Color::Yellow);
	shapeMonster.setOutlineThickness(2);

	shapeLeftMap.setPosition(1050, 800);
	shapeLeftMap.setSize(Vector2f(100.f, 100.f));
	shapeLeftMap.setFillColor(Color::Blue);

	shapeRightMap.setPosition(1580, 800);
	shapeRightMap.setSize(Vector2f(100.f, 100.f));
	shapeRightMap.setFillColor(Color::Magenta);

	dir.x = -1.f;
	dir.y = 0.f;
	float length = sqrt(dir.x * dir.x + dir.y * dir.y);
	if (length > 0)
	{
		dir /= length;
	}

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
* 설명 : 보스 동작 처리 함수
***********************************************************/
void SwordMan::Update(float dt, FloatRect playerBound, std::vector<TestRectangle*> rects)
{
	animation.Update(dt);

	swordManBound = shapeMonster.getGlobalBounds();
	// 플레이어의 히트박스 가져와서 충돌처리 할 변수
	//playerCollision = swordManBound.intersects();

	rangeBound = shapeMonster.getGlobalBounds();
	attackAble = rangeBound.intersects(playerBound);

	leftMapCollision = swordManBound.intersects(shapeLeftMap.getGlobalBounds());
	rightMapCollision = swordManBound.intersects(shapeRightMap.getGlobalBounds());

	prevMapCollision = false;
	prevRightMapCollision = false;

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
		if (action == SwordManAction::Idle)
		{
			animation.ClearPlayQueue();
			walkDelay -= dt;
			animation.PlayQueue("Idle");
			shapeMonster.setOrigin(60, 60);
			shapeMonster.setSize(Vector2f(60.f, 100.f));
			shapeMonster.setPosition(position.x - 60, position.y - 60);

			sprite.setOrigin(60, 65);
			sprite.setPosition(position);

			if (attackReady && attackAble)
			{
				action = SwordManAction::Attack;
			}
			else if(!attackAble && walkDelay < 0)
			{
				walkDelay = 2;
				animation.Play("Walk(Left)");
				action = SwordManAction::Walk;
			}
			//else if (!attackAble && walkDelay < 0)
			//{
			//	walkDelay = 2;
			//	action = SwordManAction::Walk;
			//}
		}
	}
	if (action == SwordManAction::Walk)
	{
		shapeMonster.setOrigin(60, 60);
		shapeMonster.setSize(Vector2f(60.f, 80.f));
		shapeMonster.setPosition(position.x - 40, position.y - 40);

		sprite.setPosition(position);
		sprite.setOrigin(60, 60);
		
		if (attackReady && attackAble)
		{
			action = SwordManAction::Attack;
		}

		if (!prevMapCollision && leftMapCollision)
		{
			animation.ClearPlayQueue();
			animation.Play("Walk(Right)");
			action = SwordManAction::RightWalk;
			prevMapCollision = true;
			leftMapCollision = false;
			dir.x = 1.f;
			dir.y = 0.f;
			float length = sqrt(dir.x * dir.x + dir.y * dir.y);
			if (length > 0)
			{
				dir /= length;
			}
		}
		if (!prevRightMapCollision && rightMapCollision)
		{
			animation.ClearPlayQueue();
			animation.Play("Walk(Left)");
			action = SwordManAction::LeftWalk;
			prevRightMapCollision = true;
			rightMapCollision = false;
			dir.x = -1.f;
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
	if (action == SwordManAction::LeftWalk)
	{
		animation.PlayQueue("Walk(Left)");
		action = SwordManAction::Walk;
	}
	if (action == SwordManAction::RightWalk)
	{
		animation.PlayQueue("Walk(Right)");
		action = SwordManAction::Walk;
	}
	if (action == SwordManAction::Attack)
	{
		afterAttack -= dt;

		std::cout << "공격";
		//animation.ClearPlayQueue();
		animation.Play("Attack");
		attackReady = false;

		shapeMonster.setOrigin(60, 80);
		shapeMonster.setSize(Vector2f(70.f, 100.f));
		shapeMonster.setPosition(position.x - 30, position.y - 40);

		sprite.setPosition(position);
		sprite.setOrigin(60, 75);

		if (!attackReady)
		{
			action = SwordManAction::Idle;
		}
		else if (!attackAble && !attackReady)
		{
			action = SwordManAction::Walk;
		}
	}
	if (action == SwordManAction::Hit)
	{
		if (playerCollision)	// 플레이어한테 공격을 받았을 때
		{
			mHp -= 20;	// 5대 맞으면 사망
		}
	}
	else if (action == SwordManAction::Death)
	{
		animation.Stop();
	}
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

FloatRect SwordMan::MonsterGetGlobalBound()
{
	return shapeMonster.getGlobalBounds();
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

FloatRect SwordMan::LeftMapGetGlobalBound()
{
	return shapeLeftMap.getGlobalBounds();
}

FloatRect SwordMan::RightMapGetGlobalBound()
{
	return shapeRightMap.getGlobalBounds();
}

void SwordMan::InitialLeftDir()
{
	dir.x *= -1.f;
}

void SwordMan::InitialRightDir()
{
	dir.x = 2.f;
	dir.y = 2.f;
}

/**********************************************************
* 설명 :그림 그려주는 함수
***********************************************************/
void SwordMan::Draw(RenderWindow& window)
{
	window.draw(shapeMonster);
	window.draw(shapeLeftMap);
	window.draw(shapeRightMap);
	window.draw(sprite);
}

/*Pivots pivot = Utils::CollisionDir(v->GetRect(), swordManBound);
				switch (pivot)
				{
				case Pivots::LC:
					position.x += (v->GetRect().left + v->GetRect().width) - (swordManBound.left);
					break;
				case Pivots::RC:
					position.x -= (swordManBound.left + swordManBound.width) - (v->GetRect().left);
					break;
				}*/

				//else if (prevMapCollision && !leftMapCollision)
				//{
				//	dir *= -1.f;
				//}

				//else
				//{
				//	action = SwordManAction::Idle;
				//	leftMapCollision = false;
				//	if (walkDelay < 0)
				//	{
				//		walkDelay = 2;
				//		animation.Play("Walk(Right)");
				//		dir *= -1.f;
				//	}
				//}

				/*for (auto v : rects)
				{
					swordManCollision = swordManBound.intersects(v->GetRect());
					if (!swordManCollision)
					{
						std::cout << "좌보";
						animation.Play("Walk(Left)");
					}*/
					/*	else
						{
							action = SwordManAction::Idle;
							std::cout << "우보";
							swordManCollision = false;
							animation.Play("Walk(Right)");
							dir *= -1.f;
						}*/
						/*}*/