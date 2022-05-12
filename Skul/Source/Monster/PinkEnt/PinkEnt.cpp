/******************************************************************************
* �� �� �� : �� �� ��
* �� �� �� : 2022-05-12
* ��    �� : PinkEnt�� ������ �����Ѵ�.
* �� �� �� :
*******************************************************************************/
/*include�� ���*/
#include "PinkEnt.h"
#include "../../Animation/rapidcsv.h"
#include <iostream>

/**********************************************************
* ���� : PinkEnt�� �ʱ�ȭ�Ѵ�.
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
	std::vector<std::string> colId = clipsPinkEnt.GetColumn<std::string>("ID"); // �Ϲ�ȭ���ڸ� ����
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
	attackReady = true;
	pinkEntMoveDir = true;

	attackDelay = 0;
	walkDelay = 2;
	hitDelay = 0.5f;

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
	animation.Play("Idle");
	action = PinkEntAction::Idle;
}

/**********************************************************
* ���� : ������ ��ġ�� �������ش�.
***********************************************************/
PinkEnt::PinkEnt(int x, int y)
{
	position = Vector2f(x, y);
}

PinkEnt::~PinkEnt()
{
}

/**********************************************************
* ���� : ������ ���� �� �ִϸ��̼��� ������Ʈ ���ش�.
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

	shapeMonsterSkiil.setSize(Vector2f(250.f, 250.f));
	shapeMonsterSkiil.setPosition(position.x - 90, position.y - 120);
	shapeMonsterSkiil.setOrigin(36, 61);
}

/**********************************************************
* ���� : ������ ���¿� ���� �ִϸ��̼��� ������Ʈ ���ش�.
***********************************************************/
void PinkEnt::AnimationUpdate(float dt, Player& player)
{
	switch (action)
	{
	case PinkEntAction::Idle:
		animation.PlayQueue("Idle");
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
			SetAction(PinkEntAction::Attack, player);
		}
		if (pinkEntHitCollision|| pinkEntSkillHitCollision)
		{
			SetAction(PinkEntAction::Hit, player);
		}
		break;
	case PinkEntAction::Death:
		Death(dt);
		break;
	default:
		break;
	}
}

/**********************************************************
* ���� : ������ ���¸� �������ش�.
***********************************************************/
void PinkEnt::SetAction(PinkEntAction entAction, Player& player)
{
	action = entAction;

	switch (entAction)
	{
	case PinkEntAction::Idle:
		break;
	case PinkEntAction::Attack:
		if (player.GetPlayerPosition().x < position.x)
		{
			animation.Play("AttackReady(Left)");
			sprite.setOrigin(35, 56);
		}
		else
		{
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
			animation.Play("Hit(Left)");
		}
		else
		{
			animation.Play("Hit(Right)");
		}
		break;
	case PinkEntAction::Walk:
		break;
	case PinkEntAction::Death:
		std::cout << "����";
		break;
	default:
		break;
	}
}

/**********************************************************
* ���� : ������ ���� �Լ�
***********************************************************/
void PinkEnt::Attack(float dt, Player& player)
{
	sprite.setOrigin(35, 56);
}

/**********************************************************
* ���� : ���Ͱ� ������ �޾��� ���� ó�� �Լ�
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
		std::cout << mHp << std::endl;
	}
}

/**********************************************************
* ���� : ������ �̵��� ó������ �Լ�
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
		pinkEntMoveDir = false;
	}
	else if (position.x > limitMaxMove.x)
	{
		position.x = limitMaxMove.x;
		animation.Play("Walk(Left)");
		pinkEntMoveDir = true;
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

/**********************************************************
* ���� : ���Ͱ� �׾��� ���� ó�� �Լ�
***********************************************************/
void PinkEnt::Death(float dt)
{
	animation.ClearPlayQueue();
	animation.Stop();
}

/**********************************************************
* ���� : ���� �׸� ��ȯ
***********************************************************/
Sprite PinkEnt::GetSprite()
{
	return sprite;
}

/**********************************************************
* ���� : ���� �׸� Ʋ ��ȯ
***********************************************************/
FloatRect PinkEnt::GetGlobalBound()
{
	return sprite.getGlobalBounds();
}

/**********************************************************
* ���� :���� ��Ʈ�ڽ��� Ʋ ��ȯ
***********************************************************/
FloatRect PinkEnt::MonsterGetGlobalBound()
{
	return shapeMonster.getGlobalBounds();
}

/**********************************************************
* ���� : ���� ��ų �ڽ��� Ʋ ��ȯ
***********************************************************/
FloatRect PinkEnt::MonsterSkillGetGlobalBound()
{
	return shapeMonsterSkiil.getGlobalBounds();
}

/**********************************************************
* ���� : �÷��� �Ǵ� �ִϸ��̼��� ������ ���� �����ϸ� �׼� ���¸� �������� �Լ�
***********************************************************/
void PinkEnt::GetActionIdle()
{
	action = PinkEntAction::Idle;
}

/**********************************************************
* ���� : ���͸� ȭ�鿡 �׷��� �Լ�
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
