#include "PinkEnt.h"
#include "../../Animation/rapidcsv.h"
#include <iostream>

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
	speed = 25;
	hitReady = true;
	attackReady = false;
	pinkEntMoveDir = true;

	attackDelay = 0;
	walkDelay = 2;
	afterAttack = 2;
	hitDelay = 1.f;
	changeAction = 4.f;

	shapeMonster.setFillColor(Color::Transparent);
	shapeMonster.setOutlineColor(Color::Yellow);
	shapeMonster.setOutlineThickness(2);

	shapeMonsterSkiil.setFillColor(Color::Transparent);
	shapeMonsterSkiil.setOutlineColor(Color::Blue);
	shapeMonsterSkiil.setOutlineThickness(2);

	dir.x = -1.f;
	dir.y = 0.f;
	float length = sqrt(dir.x * dir.x + dir.y * dir.y);
	if (length > 0)
	{
		dir /= length;
	}

	action = PinkEntAction::Idle;
}

PinkEnt::PinkEnt(int x, int y)
{
	position = Vector2f(x, y);
}

PinkEnt::~PinkEnt()
{
}

void PinkEnt::Update(float dt, Player& player)
{
	animation.Update(dt);
	animationGas.Update(dt);

	pinkEntBound = shapeMonster.getGlobalBounds();
	pinkEntSkillBound = shapeMonsterSkiil.getGlobalBounds();
	attackAble = pinkEntSkillBound.intersects(player.GetPlayerRect());

	pinkEntHitCollision = pinkEntBound.intersects(player.GetPlayerAttackRect());
	pinkEntSkillHitCollision = pinkEntBound.intersects(player.GetPlayerSkiilRect());

	shapeMonster.setSize(Vector2f(80.f, 90.f));
	shapeMonster.setPosition(position.x, position.y - 25);
	shapeMonster.setOrigin(36, 61);

	shapeMonsterSkiil.setSize(Vector2f(250.f, 250.f));
	shapeMonsterSkiil.setPosition(position.x - 90, position.y - 120);
	shapeMonsterSkiil.setOrigin(36, 61);

	Vector2f limitMinMove(800,600);
	Vector2f limitMaxMove(1150,600);

	if (!attackReady)
	{
		attackDelay -= dt;
	}
	if (attackAble && attackDelay < 0)
	{
		attackDelay = 3;
		attackReady = true;
	}
	if (action != PinkEntAction::Death)
	{
		if (pinkEntHitCollision && hitReady || pinkEntSkillHitCollision && hitReady)
		{
			hitReady = false;
			action = PinkEntAction::Hit;
		}
		if (action == PinkEntAction::Hit)
		{
			shapeMonster.setSize(Vector2f(80.f, 90.f));
			shapeMonster.setPosition(position.x - 10, position.y - 25);
			shapeMonster.setOrigin(36, 61);

			sprite.setOrigin(36, 61);
			hitDelay -= dt;
			if (mHp <= 0)
			{
				action = PinkEntAction::Death;
			}
			if (player.GetPlayerPosition().x < position.x)
			{
				animation.Play("Hit(Left)");
			}
			else
			{
				animation.Play("Hit(Right)");
			}
			if (hitDelay < 0)
			{
				mHp -= player.GetPlayerDamage();
				hitReady = true;
				hitDelay = 1.f;
				pinkEntHitCollision = false;
				pinkEntSkillHitCollision = false;
				action = PinkEntAction::Idle;
			}
		}
		if (action == PinkEntAction::Idle)
		{
			animation.ClearPlayQueue();
			walkDelay -= dt;
			animation.PlayQueue("Idle");
			sprite.setOrigin(37,66);

			if (attackReady && attackAble)
			{
				action = PinkEntAction::Attack;
			}
			else if (!attackAble && walkDelay < 0 && dir.x == 1.f)
			{
				walkDelay = 2;
				animation.Play("Walk(Right)");
				action = PinkEntAction::Walk;
			}
			else if (!attackAble && walkDelay < 0 && dir.x == -1.f)
			{
				walkDelay = 2;
				animation.Play("Walk(Left)");
				action = PinkEntAction::Walk;
			}
		}
		if (action == PinkEntAction::Walk)
		{
			sprite.setOrigin(36, 61);

			if (position.x < limitMinMove.x)
			{
				position.x = limitMinMove.x;
				animation.Play("Walk(Right)");
				pinkEntMoveDir = false;
			}
			else if (position.x > limitMaxMove.x)
			{
				position.x = limitMaxMove.x;
				animation.Play("Walk(Left)");
				pinkEntMoveDir = true;
			}

			if (attackReady && attackAble)
			{
				action = PinkEntAction::Attack;
			}
			if (pinkEntMoveDir)
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
			if (!pinkEntMoveDir)
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
		if (action == PinkEntAction::Attack)
		{
			afterAttack -= dt;
			changeAction -= dt;
			sprite.setOrigin(35, 56);
			if (player.GetPlayerPosition().x < position.x)
			{
				animation.PlayQueue("AttackReady(Left)");
				sprite.setOrigin(35, 56);
			}
			else
			{
				animation.PlayQueue("AttackReady(Right)");
				sprite.setOrigin(35, 56);
			}
			if (afterAttack < 0)
			{
				afterAttack = 2.f;
				std::cout << "공격 중";
				spriteGas.setPosition(position.x - 140, position.y - 50);
				animationGas.Play("EntGas");
				attackReady = false;

				if (!attackReady)
				{
					action = PinkEntAction::Idle;	
				}
				else if (!attackAble && !attackReady)
				{
					action = PinkEntAction::Walk;
				}
			}
		}
	}
	else if (action == PinkEntAction::Death)
	{
	animation.ClearPlayQueue();
	animation.Stop();
	}
}

Sprite PinkEnt::GetSprite()
{
	return sprite;
}

FloatRect PinkEnt::GetGlobalBound()
{
	return sprite.getGlobalBounds();
}

FloatRect PinkEnt::MonsterGetGlobalBound()
{
	return shapeMonster.getGlobalBounds();
}

FloatRect PinkEnt::MonsterSkillGetGlobalBound()
{
	return shapeMonsterSkiil.getGlobalBounds();
}

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
