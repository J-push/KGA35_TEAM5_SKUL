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
	int launcher1 = 0;
	int launcher2 = 0;
	int launcher3 = 0;
	bossPosition.x = 1700;
	bossPosition.y = 700;

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

void Boss::Fire(Vector2f dir)
{
	launcher1 = 0;
	launcher2 = 0;
	launcher3 = 0;

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

void Boss::FireRutine(Vector2f dir)
{
	if (bossPosition.x - dir.x > 0) // 플레이어가 보스의 왼쪽
	{
		spriteBoss.setScale(-1.7f, 1.7f);
		animation.Play("attack");
	}
	if (bossPosition.x - dir.x < 0) // 플레이어가 보스의 왼쪽
	{
		spriteBoss.setScale(-1.7f, 1.7f);
		animation.Play("attack");
	}

	Fire(dir);
}



void Boss::SuperFire(Vector2f dir, Vector2f pos)
{
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

void Boss::SuperFireRutine(Vector2f dir)
{
	if (launcher1 == 0)
	{
		SuperFire(dir, Vector2f(150, 50));
		launcher1++;
	}
	if (launcher1 == 1)
	{
		SuperFire(dir, Vector2f(150, 50));
		SuperFire(dir, Vector2f(800, 0));
		launcher1++;
		launcher2++;
	}
	if (launcher1 == 2)
	{
		SuperFire(dir, Vector2f(800, 0));
		SuperFire(dir, Vector2f(1500, 50));
		launcher1++;
		launcher2++;
		launcher3++;
	}
	if (launcher2 == 2)
	{
		SuperFire(dir, Vector2f(1500, 50));
		launcher2++;
		launcher3++;
	}
}




void Boss::Move(float dt, Vector2f dir)
{
	int move = RandomMgr::GetRandom(1, 2);
	if (move == 1)
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
		bossPosition.x += speed * dt;
	}
	if (move == 2)
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
		bossPosition.x -= speed * dt;
	}
}

//intro1 intro2 attackready attack idle walkback walkfront


void Boss::Update(float dt, Vector2f dir)
{
	switch (action)
	{
	case BossStatus::INTRO:
		animation.Play("intro1");		
		if (animation.GetisEnding())
		{
			animation.Play("intro2");
			action = BossStatus::IDLE;
		}
		break;

	case BossStatus::IDLE:
		animation.Play("idle");
		break;

	case BossStatus::MOVE:
		Move(dt, dir);
		break;
	case BossStatus::FIREBALL:
		break;
	case BossStatus::LANDING:
		break;
	case BossStatus::METEO:
		SuperFireRutine(dir);
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
		bossPosition.y -= 200;
		animation.Play("intro1");
	}
	if (InputManager::GetKeyDown(Keyboard::W))
	{
		animation.Play("attackready");
	}
	if (InputManager::GetKeyDown(Keyboard::E))
	{
		animation.Play("attack");
		Fire(dir);
	}
	if (InputManager::GetKeyDown(Keyboard::R))
	{
		Fire(dir);
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
	//window.draw(superSkill.GetSprite());
	//window.draw(superSkill.GetEffectSprite());
}
