/******************************************************************************
* 작 성 자 : 진 현 섭
* 작 성 일 : 2022-05-06
* 내    용 : swordman의 동작을 구현한다.
* 수 정 일 :
*******************************************************************************/
/*include될 헤더*/
#include "../swordman/swordman.h"
#include "../Animation/rapidcsv.h"
#include <iostream>
#include <ctime>
#include <random>


/**********************************************************
* 설명 : 소드맨를 초기화한다.
***********************************************************/
void swordman::Init()
{
	//position.x = 1400; // 960
	//position.y = 920; // 540
	sprite.setScale(2.f, 2.f);
	sprite.setOrigin(60, 65);
	sprite.setPosition(position);
	animation.SetTarget(&sprite);

	rapidcsv::Document clipsswordman("data_tables/animations/swordman/swordman_animation_clips.csv");
	std::vector<std::string> colId = clipsswordman.GetColumn<std::string>("ID"); // 일반화인자를 받음
	std::vector<int> colFps = clipsswordman.GetColumn<int>("FPS");
	std::vector<int> colLoop = clipsswordman.GetColumn<int>("LOOP TYPE(0:Single, 1:Loop)");
	std::vector<std::string> colPath = clipsswordman.GetColumn<std::string>("CLIP PATH");

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

	mHp = START_swordman_HEALTH;
	damage = START_swordman_DAMAGE;
	speed = START_swordman_SPEED;
	hitReady = true;
	attackReady = false;

	attackDelay = 0;
	walkDelay = 2;
	afterAttack = 3;
	hitDelay = 1.f;

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

	shapeScope.setFillColor(Color::Transparent);
	shapeScope.setOutlineColor(Color::Black);
	shapeScope.setOutlineThickness(2);

	dir.x = -1.f;
	dir.y = 0.f;
	float length = sqrt(dir.x * dir.x + dir.y * dir.y);
	if (length > 0)
	{
		dir /= length;
	}

	action = swordmanAction::Idle;
}

swordman::swordman(int x, int y)
{
	position = Vector2f(x, y);
}

swordman::~swordman()
{
}

/**********************************************************
* 설명 : 아직 구현은 안 했지만 소드맨이 공격을 받았을 때의 처리 함수
***********************************************************/
bool swordman::OnHitted()
{
	return false;
}

/**********************************************************
* 설명 : 소드맨 동작 처리 함수
***********************************************************/
void swordman::Update(float dt, FloatRect playerBound, FloatRect playerAttackBound, FloatRect playerSkiilBound, Vector2f playerPosition, int playerDamage, std::vector<ColliderRect*> rects)
{
	animation.Update(dt);

	swordmanBound = shapeMonster.getGlobalBounds();

	rangeBound = shapeMonster.getGlobalBounds();
	attackAble = rangeBound.intersects(playerBound);

	swordmanScope = shapeScope.getGlobalBounds();

	leftMapCollision = swordmanBound.intersects(shapeLeftMap.getGlobalBounds());
	rightMapCollision = swordmanBound.intersects(shapeRightMap.getGlobalBounds());
	swordmanScopeCollision = swordmanScope.intersects(playerBound);	// 만들어만 놓고 아직 안 썼음
	swordmanHitCollision = swordmanBound.intersects(playerAttackBound);
	swordmanSkillHitCollision = swordmanBound.intersects(playerSkiilBound);

	prevMapCollision = false;
	prevRightMapCollision = false;

	shapeScope.setSize(Vector2f(150.f, 100.f));
	shapeScope.setPosition(position.x - 140, position.y - 120);

	if (!attackReady)
	{
		attackDelay -= dt;
	}
	if (attackAble && attackDelay < 0)
	{
		attackDelay = 3;
		attackReady = true;
	}

	if (action != swordmanAction::Death)
	{
		if (swordmanHitCollision && hitReady || swordmanSkillHitCollision && hitReady)
		{
			hitReady = false;
			action = swordmanAction::Hit;
		}
		if (action == swordmanAction::Hit)
		{
			hitDelay -= dt;
			if (mHp <= 0)
			{
				action = swordmanAction::Death;
			}
			if (playerPosition.x < position.x)
			{
				animation.Play("Hit(Left)");
			}
			else
			{
				animation.Play("Hit(Right)");
			}
			if (hitDelay < 0)
			{
				mHp -= playerDamage;
				hitReady = true;
				hitDelay = 1.f;
				swordmanHitCollision = false;
				swordmanSkillHitCollision = false;
				action = swordmanAction::Idle;
			}
		}
		if (action == swordmanAction::Idle)
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
				action = swordmanAction::Attack;
			}
			else if (!attackAble && walkDelay < 0 && dir.x == 1.f)
			{
				walkDelay = 2;
				animation.Play("Walk(Right)");
				action = swordmanAction::Walk;
			}
			else if (!attackAble && walkDelay < 0 && dir.x == -1.f)
			{
				walkDelay = 2;
				animation.Play("Walk(Left)");
				action = swordmanAction::Walk;
			}
		}
	}
	if (action == swordmanAction::Walk)
	{
		shapeMonster.setOrigin(60, 60);
		shapeMonster.setSize(Vector2f(60.f, 80.f));
		shapeMonster.setPosition(position.x - 40, position.y - 40);

		sprite.setPosition(position);
		sprite.setOrigin(60, 60);

		if (attackReady && attackAble)
		{
			action = swordmanAction::Attack;
		}
		// 플레이어가 인식 범위에 들어오면 행해줄 조건
	/*	if (swordmanScopeCollision)
		{
		}*/

		if (!prevMapCollision && leftMapCollision)
		{
			animation.ClearPlayQueue();
			animation.Play("Walk(Right)");
			action = swordmanAction::RightWalk;
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
			action = swordmanAction::LeftWalk;
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
	if (action == swordmanAction::LeftWalk)
	{
		animation.PlayQueue("Walk(Left)");
		action = swordmanAction::Walk;
	}
	if (action == swordmanAction::RightWalk)
	{
		animation.PlayQueue("Walk(Right)");
		action = swordmanAction::Walk;
	}
	if (action == swordmanAction::Attack)
	{
		afterAttack -= dt;
		if (playerPosition.x < position.x)
		{
			animation.Play("Attack(Left)");
		}
		else
		{
			animation.Play("Attack(Right)");
		}
		attackReady = false;

		shapeMonster.setOrigin(60, 80);
		shapeMonster.setSize(Vector2f(70.f, 100.f));
		shapeMonster.setPosition(position.x - 30, position.y - 40);

		sprite.setPosition(position);
		sprite.setOrigin(60, 75);

		if (!attackReady)
		{
			action = swordmanAction::Idle;
		}
		else if (!attackAble && !attackReady)
		{
			action = swordmanAction::Walk;
		}
	}
	else if (action == swordmanAction::Death)
	{
		animation.ClearPlayQueue();
		animation.Stop();
	}
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
* 설명 : 플레이어와의 충돌 더미 반환해줄 함수
***********************************************************/
FloatRect swordman::RangeGetGlobalBound()
{
	return shape.getGlobalBounds();
}

/**********************************************************
* 설명 : 플레이어와의 충돌 더미를 반환해주는 함수
***********************************************************/
const RectangleShape swordman::GetShape()
{
	return shape;
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
* 설명 : 아직 쓰지는 않지만 소드맨의 적 인식 범위 글로벌 바운즈
***********************************************************/
FloatRect swordman::ScopeGetGlobalBound()
{
	return shapeScope.getGlobalBounds();
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
		window.draw(shapeMonster);
		window.draw(sprite);
	}
}