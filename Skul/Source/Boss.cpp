#include "Boss.h"

Boss::~Boss()
{
	for (auto bullet : unuseFires)
	{
		delete bullet;
	}
	unuseFires.clear();
	for (auto bullet : useFires)
	{
		delete bullet;
	}
	useFires.clear();
}

void Boss::Init()
{
	int superCount = 0;
	int launcher2 = 0;
	int launcher3 = 0;
	bossPosition.x = 1700;
	bossPosition.y = 750;

	// 피격판정
	bossRect.setSize(Vector2f(38, 110));
	bossRect.setFillColor(Color(255,0,0,70));
	Utils::SetOrigin(bossRect, Pivots::CC);
	bossRect.setPosition(bossPosition);

	spriteBoss.setScale(1.7f, 1.7f);
	spriteBoss.setPosition(bossPosition);
	animation.SetTarget(&spriteBoss);


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
	}

	for (int i = 0; i < FIRE_SIZE; ++i)
	{
		unuseFires.push_back(new BossFire());
	}
	action = BossStatus::INTRO;
}

void Boss::Intro(float dt)
{
	if (introCount == 0 && timer < 99.9)
	{
		animation.Play("intro1");
		introCount++;
	}
	if (introCount == 1 && timer < 95.7)
	{
		bossPosition.y -= 200;
		animation.Play("intro2");
		introCount++;
	}
	if (introCount == 2 && timer < 94.4)
	{
		//bossPosition.y += 7;
		introCount = 0;
		timer = 100;
		moveWhere = RandomMgr::GetRandom(1,2);
		action = BossStatus::MOVE;
	}
}

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
		Fire(dir);
		count++;
		timer = 100;
		moveWhere = RandomMgr::GetRandom(1, 2);
		FirstMove(dir, moveWhere);
		action = BossStatus::MOVE;
	}
}

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

void Boss::SuperFireRutine(Vector2f dir, float dt)
{	
	if (superCount == 0 && timer < 99.9)
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
		superCount++;
	}
	if (superCount == 1 && timer < 99.1)
	{
		animation.Play("supergo");
		superCount++;
	}
	if (superCount == 2 && timer < 97.9)
	{
		animation.Play("superdoing");
		SuperFire(dir, Vector2f(380, 230));
		superCount++;
	}
	if (superCount == 3 && timer < 95.9)
	{
		SuperFire(dir, Vector2f(380, 230));
		SuperFire(dir, Vector2f(1030, 180));
		superCount++;
	}

	if (superCount == 4 && timer < 93.9)
	{
		SuperFire(dir, Vector2f(1030, 180));
		SuperFire(dir, Vector2f(1730, 230));
		superCount++;
	}

	if (superCount == 5 && timer < 91.9)
	{
		SuperFire(dir, Vector2f(1730, 230));
		superCount++;
	}

	if (superCount == 6 && timer < 89.9)
	{
		SuperFire(dir, Vector2f(380, 230));
		SuperFire(dir, Vector2f(1030, 180));
		SuperFire(dir, Vector2f(1730, 230));
		superCount++;
	}
	if (superCount == 7 && timer < 87.9)
	{
		superCount = 0;
		timer = 100;
		moveWhere = RandomMgr::GetRandom(1, 2);
		FirstMove(dir, moveWhere);
		action = BossStatus::MOVE;
	}
}

void Boss::Landing(Vector2f dir)
{
	if (superCount == 0 && timer < 99.9)
	{
		bossPosition.x = dir.x;
		animation.Play("landingready");
		superCount++;
	}
	if (superCount == 1 && timer < 98.9)
	{
		bossPosition.y = dir.y - 10;
		animation.Play("landingbomb");
		superCount++;
	}
	if (superCount == 2 && timer < 96.9)
	{
		animation.Play("landingdown");
		superCount++;
	}
	if (superCount == 3 && timer < 94.9)
	{
		animation.Play("Move");
		bossPosition.y = 550;
		superCount = 0;
		timer = 100;
		moveWhere = RandomMgr::GetRandom(1, 2);
		FirstMove(dir, moveWhere);
		action = BossStatus::MOVE;
	}	
}

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

void Boss::Move(float dt, Vector2f dir, int moving)
{
	if (200 > bossPosition.x || bossPosition.x > 1600)
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
	
		whatAction = RandomMgr::GetRandom(1, 3);
		if (whatAction == 1)
		{
			action = BossStatus::FIREBALL;
		}
		if (whatAction == 2)
		{
			action = BossStatus::METEO;
		}
		if (whatAction == 3)
		{
			action = BossStatus::LANDING;
		}	
	}
}

void Boss::Idle()
{
	animation.PlayQueue("idle");
	moveWhere = RandomMgr::GetRandom(1, 2);
}

// intro1 intro2 attackready attack idle walkback walkfront landingready landingbomb landingdown bomb
// superdoing superready supergo

void Boss::Update(float dt, Vector2f dir)
{
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
	bossRect.setPosition(bossPosition);
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

void Boss::Draw(RenderWindow &window)
{
	window.draw(spriteBoss);
	window.draw(bossRect);
	for (auto fire : useFires)
	{
		window.draw(fire->GetSprite());
		window.draw(fire->GetRect());
		window.draw(fire->GetSuperEffectSprite());
	}
}


void Boss::SetStateIdle()
{
	action = BossStatus::IDLE;
}
