/******************************************************************************
* 작 성 자 : 김 재 휘
* 작 성 일 : 2022-05-10
* 내    용 : boss의 동작을 구현한다.
* 수 정 일 :
*******************************************************************************/
#include "Boss.h"

// intro1 intro2 intro2re attackready attack idle walkback walkfront landingready landingbomb landingdown bomb
// superdoing superready supergo landingeffect landingoutro

Boss::~Boss()
{
	for (auto fire : unuseFires)
	{
		delete fire;
	}
	unuseFires.clear();
	for (auto fire : useFires)
	{
		delete fire;
	}
	useFires.clear();
}

/**********************************************************
* 설명 : Boss를 초기화한다.
***********************************************************/
void Boss::Init()
{
	isHit = false;
	isFireAttacking = true;
	isLandingAttacking = false;
	alive = true;

	int superCount = 0;
	int launcher2 = 0;
	int launcher3 = 0;
	bossPosition.x = 1700;
	bossPosition.y = 750;


	spriteAttackEffect.setScale(0.7f, 0.7f);
	Utils::SetOrigin(spriteEffect, Pivots::CC);
	spriteAttackEffect.setPosition(bossPosition);
	animationAttackEffect.SetTarget(&spriteAttackEffect);


	// 피격판정
	bossRect.setSize(Vector2f(38, 110));
	bossRect.setFillColor(Color(255, 0, 0, 70));
	Utils::SetOrigin(bossRect, Pivots::CC);
	bossRect.setPosition(bossPosition);

	bossLandingRect.setSize(Vector2f(200, 110));
	bossLandingRect.setFillColor(Color(128, 128, 0, 100));
	Utils::SetOrigin(bossLandingRect, Pivots::CC);
	bossLandingRect.setPosition(bossPosition);


	spriteBoss.setScale(1.7f, 1.7f);
	spriteBoss.setPosition(bossPosition);
	animation.SetTarget(&spriteBoss);

	spriteEffect.setScale(2.0f, 2.0f);
	Utils::SetOrigin(spriteEffect, Pivots::CC);
	spriteEffect.setPosition(bossPosition);
	animationEffect.SetTarget(&spriteEffect);


	rapidcsv::Document clipsBoss("data_tables/animations/Boss/boss_animation_clips.csv");
	std::vector<std::string> colId = clipsBoss.GetColumn<std::string>("ID");
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
		animationEffect.AddClip(clip);
		animationAttackEffect.AddClip(clip);
	}

	for (int i = 0; i < FIRE_SIZE; ++i)
	{
		unuseFires.push_back(new BossFire());
	}
	action = BossStatus::INTRO;
}

/**********************************************************
* 설명 : Boss의 인트로.
***********************************************************/
void Boss::Intro(float dt)
{
	if (introCount == 0 && timer < 99.9)
	{
		animation.Play("intro1");
		introCount++;
	}
	if (introCount == 1 && timer < 97.7)
	{
		bossPosition.y -= 200;
		animation.Play("intro2");
		introCount++;
	}
	if (introCount == 2 && timer < 96.4)
	{
		//bossPosition.y += 7;
		introCount = 0;
		timer = 100;
		moveWhere = RandomMgr::GetRandom(1, 2);
		animation.Play("walkfront");
		action = BossStatus::MOVE;
	}
}

/**********************************************************
* 설명 : Boss가 사용할 일반공격.
***********************************************************/
void Boss::Fire(Vector2f dir)
{
	Vector2f realdir = dir - bossPosition;
	realdir = Utils::Normalize(realdir);

	Vector2f spawnPos = bossPosition + realdir;

	if (unuseFires.empty()) //	비어있을때 true
	{
		for (int i = 0; i < FIRE_SIZE; ++i)
		{
			unuseFires.push_back(new BossFire());
		}
	}

	BossFire *bossFire = unuseFires.front();
	unuseFires.pop_front();
	useFires.push_back(bossFire);
	bossFire->Shoot(spawnPos, realdir);
}

/**********************************************************
* 설명 : Boss가 사용할 일반공격 루틴.
***********************************************************/
void Boss::FireRutine(Vector2f dir, float dt)
{
	if (bossPosition.x - dir.x > 0) // 플레이어가 보스의 왼쪽
	{
		spriteBoss.setScale(1.7f, 1.7f);
	}
	if (bossPosition.x - dir.x < 0) // 플레이어가 보스의 오른쪽
	{
		spriteBoss.setScale(-1.7f, 1.7f);
	}

	if (count == 0 && timer < 99.9f)
	{
		spriteText.setTexture(*ResourceMgr::instance()->GetTexture("BOSSTEX1"));
		spriteText.setPosition(bossPosition.x - 100, bossPosition.y - 120);
		isFireAttacking = true;
		animation.Play("attack");
		Fire(dir);
		count++;
	}
	if (count == 1 && timer < 99.4f)
	{
		Fire(dir);
		count++;
	}
	if (count == 2 && timer < 98.9f)
	{
		Fire(dir);
		count++;
	}
	if (count == 3 && timer < 98.4f)
	{
		Fire(dir);
		count++;
	}
	if (count == 4 && timer < 97.9f)
	{
		spriteText.setPosition(Vector2f(6000, 6000));

		Fire(dir);
		count = 0;
		timer = 100;
		moveWhere = RandomMgr::GetRandom(1, 2);
		FirstMove(dir, moveWhere);
		action = BossStatus::MOVE;
	}
}

/**********************************************************
* 설명 : Boss가 사용할 필살기.
***********************************************************/
void Boss::SuperFire(Vector2f dir, Vector2f pos)
{
	pos.x -= 230;
	pos.y -= 180;
	dir.x -= 170;

	Vector2f realdir = dir - pos;
	realdir = Utils::Normalize(realdir);

	Vector2f spawnPos = pos;

	if (unuseFires.empty()) //	비어있을때 true
	{
		for (int i = 0; i < FIRE_SIZE; ++i)
		{
			unuseFires.push_back(new BossFire());
		}
	}

	BossFire *bossFire = unuseFires.front();
	unuseFires.pop_front();
	useFires.push_back(bossFire);
	bossFire->SuperShoot(spawnPos, realdir);
}

/**********************************************************
* 설명 : Boss가 사용할 필살기 루틴.
***********************************************************/
void Boss::SuperFireRutine(Vector2f dir, float dt)
{
	if (count == 0 && timer < 99.9)
	{
		if (bossPosition.x - dir.x > 0) // 플레이어가 보스의 왼쪽
		{
			spriteBoss.setScale(1.7f, 1.7f);
		}
		if (bossPosition.x - dir.x < 0) // 플레이어가 보스의 오른쪽
		{
			spriteBoss.setScale(-1.7f, 1.7f);
		}
		animation.Play("superready");
		count++;
	}
	if (count == 1 && timer < 99.1)
	{
		spriteText.setTexture(*ResourceMgr::instance()->GetTexture("BOSSTEX2"));
		spriteText.setPosition(bossPosition.x - 120, bossPosition.y - 120);
		isFireAttacking = false;
		animation.Play("supergo");
		count++;
	}
	if (count == 2 && timer < 97.9)
	{
		animation.Play("superdoing");
		SuperFire(dir, Vector2f(380, 230));
		count++;
	}
	if (count == 3 && timer < 95.9)
	{
		SuperFire(dir, Vector2f(380, 230));
		SuperFire(dir, Vector2f(1030, 180));
		count++;
	}

	if (count == 4 && timer < 93.9)
	{
		SuperFire(dir, Vector2f(1030, 180));
		SuperFire(dir, Vector2f(1730, 230));
		count++;
	}

	if (count == 5 && timer < 91.9)
	{
		SuperFire(dir, Vector2f(1730, 230));
		count++;
	}

	if (count == 6 && timer < 89.9)
	{
		SuperFire(dir, Vector2f(380, 230));
		SuperFire(dir, Vector2f(1030, 180));
		SuperFire(dir, Vector2f(1730, 230));
		count++;
	}
	if (count == 7 && timer < 87.9)
	{
		count = 0;
		timer = 100;
		spriteText.setPosition(Vector2f(6000, 6000));
		moveWhere = RandomMgr::GetRandom(1, 2);
		isFireAttacking = true;
		FirstMove(dir, moveWhere);
		action = BossStatus::MOVE;
	}
}

void Boss::SuperFireHp()
{
	if (bossPosition.y < 600 && isFireAttacking)
	{
		if (currentHp < 350 && superCount == 0)
		{
			timer = 100;
			count = 0;
			superCount++;
			action = BossStatus::METEO;
		}
		if (currentHp < 300 && superCount == 1)
		{
			timer = 100;
			count = 0;
			superCount++;
			action = BossStatus::METEO;
		}
		if (currentHp < 250 && superCount == 2)
		{
			timer = 100;
			count = 0;
			superCount++;
			action = BossStatus::METEO;
		}
		if (currentHp < 200 && superCount == 3)
		{
			timer = 100;
			count = 0;
			superCount++;
			action = BossStatus::METEO;
		}
		if (currentHp < 150 && superCount == 4)
		{
			timer = 100;
			count = 0;
			superCount++;
			action = BossStatus::METEO;
		}
		if (currentHp < 100 && superCount == 5)
		{
			timer = 100;
			count = 0;
			superCount++;
			action = BossStatus::METEO;
		}
		if (currentHp < 50 && superCount == 6)
		{
			timer = 100;
			count = 0;
			superCount++;
			action = BossStatus::METEO;
		}
	}
}

/**********************************************************
* 설명 : Boss가 사용할 착지공격.
***********************************************************/
void Boss::Landing(Vector2f dir)
{
	if (count == 0 && timer < 99.9)
	{
		spriteEffect.setScale(2.0f, 2.0f);
		animation.Play("intro2re"); // 1.0
		count++;
	}
	if (count == 1 && timer < 99.4)
	{
		bossPosition.x = dir.x;
		animation.Play("intro2"); // 1.3
		count++;
	}
	if (count == 2 && timer < 98.8)
	{
		spriteText.setTexture(*ResourceMgr::instance()->GetTexture("BOSSTEX3"));
		spriteText.setPosition(bossPosition.x - 70, bossPosition.y - 130);
		animation.Play("landingready"); // 0.4
		count++;
	}
	if (count == 3 && timer < 98.4)
	{
		isLandingAttacking = true;
		bossPosition.y = 750;
		spriteText.setPosition(bossPosition.x - 70, bossPosition.y - 70);
		spriteEffect.setPosition(bossPosition.x - 293, bossPosition.y - 275);
		animationEffect.Play("landingeffect"); // 2.0
		animation.Play("landingdown");
		count++;
	}
	if (count == 4 && timer < 98.2)
	{
		isLandingAttacking = false;
		count++;
	}
	if (count == 5 && timer < 96.4)
	{
		animation.Play("landingdown"); // 2.0
		count++;
	}
	if (count == 6 && timer < 94.1)
	{
		spriteText.setPosition(Vector2f(6000, 6000));
		animation.Play("landingoutro"); // 1.0
		count++;
	}
	if (count == 7 && timer < 93.6)
	{
		bossPosition.y -= 200;
		animation.Play("intro2"); // 1.3
		count++;
	}
	if (count == 8 && timer < 92.7)
	{
		animation.Play("Move");
		bossPosition.y = 550;
		count = 0;
		timer = 100;

		moveWhere = RandomMgr::GetRandom(1, 2);
		FirstMove(dir, moveWhere);
		action = BossStatus::MOVE;
	}
}

/**********************************************************
* 설명 : Boss의 시작 움직임 설정.
***********************************************************/
void Boss::FirstMove(Vector2f dir, int moving)
{

	if (moving == 1)
	{
		if (bossPosition.x - dir.x > 0) // 왼쪽보면서 오른쪽으로 이동
		{
			spriteBoss.setScale(-1.7f, 1.7f);
			animation.Play("walkback");
		}
		else
		{
			spriteBoss.setScale(-1.7f, 1.7f);
			animation.Play("walkfront");
		}
	}
	if (moving == 2)
	{
		if (bossPosition.x - dir.x < 0) // 오른쪽보면서 왼쪽으로 이동
		{
			spriteBoss.setScale(1.7f, 1.7f);
			animation.Play("walkback");
		}
		else
		{
			spriteBoss.setScale(1.7f, 1.7f);
			animation.Play("walkfront");
		}
	}
}

/**********************************************************
* 설명 : Boss의 이동 설정.
***********************************************************/
void Boss::Move(float dt, Vector2f dir, int moving)
{
	if (50 > bossPosition.x || bossPosition.x > 1800)
	{
		timer = 100;
		count = 0;
		action = BossStatus::LANDING;
	}
	if (timer > 96)
	{
		if (moving == 1)
		{
			if (bossPosition.x - dir.x > 0) // 왼쪽보면서 오른쪽으로 이동
			{
				spriteBoss.setScale(-1.7f, 1.7f);
				if (bossLook)
				{
					animation.Play("walkback");
					bossLook = false;
				}
			}
			else
			{
				spriteBoss.setScale(-1.7f, 1.7f);
				if (!bossLook)
				{
					animation.Play("walkfront");
					bossLook = true;
				}
			}
			bossPosition.x += speed * dt;
		}
		if (moving == 2)
		{
			if (bossPosition.x - dir.x < 0) // 오른쪽보면서 왼쪽으로 이동
			{
				spriteBoss.setScale(1.7f, 1.7f);
				if (!bossLook)
				{
					animation.Play("walkback");
					bossLook = true;
				}
			}
			else
			{
				spriteBoss.setScale(1.7f, 1.7f);
				if (bossLook)
				{
					animation.Play("walkfront");
					bossLook = false;
				}
			}
			bossPosition.x -= speed * dt;
		}
	}
	else
	{
		timer = 100;
		count = 0;

		whatAction = RandomMgr::GetRandom(1, 5);
		if (1 <= whatAction && whatAction <= 4)
		{
			action = BossStatus::FIREBALL;
		}
		/*if (whatAction == 2)
		{
			action = BossStatus::METEO;
		}*/
		if (whatAction == 5)
		{
			action = BossStatus::LANDING;
		}
	}
}

/**********************************************************
* 설명 : Boss가 죽었을 때 설정.
***********************************************************/
void Boss::Die(float dt)
{
	if (dieCount == 0 && dietimer < 99.7)
	{
		animation.Play("dieintro");
		dieCount++;
	}

	if (dieCount == 1 && dietimer < 99.0)
	{
		bossPosition.x = 1700;
		bossPosition.y = 750;
		animation.Play("landingoutrore");
		dieCount++;
	}

	if (dieCount == 2 && dietimer < 98.0)
	{
		bossPosition.y += 20;
		animation.Play("die");
		dieCount++;
	}
	if (dieCount == 3 && dietimer < 93.5)
	{
		alive = false;
		dieCount++;
	}
}

/**********************************************************
* 설명 : Boss의 기본상태 설정.
***********************************************************/
void Boss::Idle()
{
	animation.PlayQueue("idle");
	moveWhere = RandomMgr::GetRandom(1, 2);
}

/**********************************************************
* 설명 : Boss의 피격범위.
***********************************************************/
FloatRect Boss::GetGlobalBound()
{
	return spriteBoss.getGlobalBounds();
}

/**********************************************************
* 설명 : Boss의 착지공격 범위.
***********************************************************/
FloatRect Boss::GetBossLanding()
{
	return bossLandingRect.getGlobalBounds();
}

/**********************************************************
* 설명 : Boss의 업데이트를 관리한다.
***********************************************************/
void Boss::Update(float dt, Vector2f dir)
{
	if (currentHp <= 0)
	{
		action = BossStatus::DIE;
	}

	SuperFireHp();

	switch (action)
	{
	case BossStatus::INTRO:
		timer -= dt;
		Intro(dt);
		break;

	case BossStatus::IDLE:
		Idle();
		break;

	case BossStatus::MOVE:
		timer -= dt;
		Move(dt, dir, moveWhere);
		break;

	case BossStatus::LANDING:
		timer -= dt;
		Landing(dir);
		break;

	case BossStatus::FIREBALL:
		timer -= dt;
		FireRutine(dir, dt);
		break;

	case BossStatus::METEO:
		timer -= dt;
		SuperFireRutine(dir, dt);
		break;

	case BossStatus::DIE:
		dietimer -= dt;
		Die(dt);
		break;

	default:
		break;
	}

	// 불 부분
	auto it = useFires.begin();
	while (it != useFires.end())
	{
		BossFire *fire = *it;
		fire->Update(dt);

		if (!fire->IsActive())
		{
			it = useFires.erase(it);
			unuseFires.push_back(fire);
		}
		else
		{
			++it;
		}
	}

	Utils::SetOrigin(spriteBoss, Pivots::CC);
	animation.Update(dt);
	animationEffect.Update(dt);
	animationAttackEffect.Update(dt);
	bossRect.setPosition(bossPosition);
	bossLandingRect.setPosition(bossPosition);
	spriteBoss.setPosition(bossPosition);

	// 체크용
	if (InputManager::GetKeyDown(Keyboard::Q))
	{
		action = BossStatus::INTRO;
	}
	if (InputManager::GetKeyDown(Keyboard::W))
	{
		animation.Play("intro1");
	}
	if (InputManager::GetKeyDown(Keyboard::E))
	{
		Move(dt, dir, moveWhere);
	}
	if (InputManager::GetKeyDown(Keyboard::R))
	{
		action = BossStatus::FIREBALL;
	}
	if (InputManager::GetKeyDown(Keyboard::T))
	{
		action = BossStatus::METEO;
	}
	if (InputManager::GetKeyDown(Keyboard::Y))
	{
		action = BossStatus::MOVE;
	}
}

/**********************************************************
* 설명 : Boss의 Draw를 관리한다.
***********************************************************/
void Boss::Draw(RenderWindow &window)
{
	window.draw(spriteEffect);
	window.draw(spriteBoss);
	window.draw(spriteAttackEffect);
	window.draw(bossRect);
	window.draw(bossLandingRect);
	window.draw(spriteText);

	for (auto fire : useFires)
	{
		window.draw(fire->GetSprite());
		window.draw(fire->GetRect());
		window.draw(fire->GetSuperEffectSprite());
		window.draw(fire->GetBombSprite());
	}
}

/**********************************************************
* 설명 : Boss의 최대체력을 받아온다.
***********************************************************/
int Boss::GetMaxHp()
{
	return maxHp;
}

/**********************************************************
* 설명 : Boss의 현재체력을 받아온다.
***********************************************************/
int Boss::GetCurrentHp()
{
	return currentHp;
}

/**********************************************************
* 설명 : Boss의 피격 딜레이를 설정한다.
***********************************************************/
bool Boss::underAttack(float dt)
{
	hitTimer -= dt;
	if (hitTimer < 99.5 && !isHit)
	{
		hitTimer = 100;
		isHit = true;
		return true;
	}
	else
	{
		isHit = false;
		return false;
	}
}

/**********************************************************
* 설명 : Boss가 공격받았을 때 체력을 조절한다.
***********************************************************/
void Boss::SetBossHp(int damage)
{
	if (currentHp > 0)
	{
		currentHp -= damage;
	}
	if (currentHp <= 0)
	{
		currentHp = 0;
	}
}

/**********************************************************
* 설명 : Boss가 살아있는지 확인한다.
***********************************************************/
bool Boss::isAlive()
{
	return alive;
}

/**********************************************************
* 설명 : Boss공격의 충돌처리를 담당한다.
***********************************************************/
bool Boss::UpdateCollision(Player &player)
{
	bool isCollied = false;

	for (auto fire : useFires)
	{
		if (fire->UpdateCollision(player))
		{
			if (isFireAttacking)
			{
				spriteAttackEffect.setScale(0.6f, 0.6f);
				spriteAttackEffect.setPosition(player.GetPlayerPosition().x - 55, player.GetPlayerPosition().y - 70);
				animationAttackEffect.Play("attackeffect");
				player.Hit(5);
			}
			if (!isFireAttacking)
			{
				spriteAttackEffect.setScale(1.3f, 1.3f);
				spriteAttackEffect.setPosition(player.GetPlayerPosition().x - 100, player.GetPlayerPosition().y - 150);
				animationAttackEffect.Play("attackeffect");
				player.Hit(20);
			}
			isCollied = true;
		}
	}

	bool isCheck = player.GetPlayerRect().intersects(GetBossLanding());
	if (isCheck && isLandingAttacking)
	{
		player.Hit(30);
		isLandingAttacking = false;
		isCollied = true;
	}
	return isCollied;
}