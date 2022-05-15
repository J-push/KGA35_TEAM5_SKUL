/******************************************************************************
* 작 성 자 : 김 재 휘
* 작 성 일 : 2022-05-03
* 내    용 : 게임이 진행중인 Scene의 정보를 담당한다.
* 수 정 일 : 2022-05-04(진현섭)
*******************************************************************************/
/*include될 헤더*/
#include "SceneGame.h"
#include "../Manager/ResourceMgr.h"
#include "../Manager/RandomMgr.h"
#include "../Framework/Framework.h"
#include "../BossFire.h"

void SceneGame::Init()
{
	spriteBackground.setTexture(*ResourceMgr::instance()->GetTexture("BACKGROUNDTEX"));
	spriteBackground.setScale(Vector2f(backGroundX, backGroundY));
	tilemap.Init();
	CreateSwordMan(mSwordMans, 1);
	CreatePinkEnt(mPinkEnt, 1);
	player.Init();
	player.SkillInit();
	ui.Init();

	boss.Init();

	check = forCheckTime.restart();
}

void SceneGame::Release()
{
}

void SceneGame::Start()
{
	//Init();
}

void SceneGame::End()
{
}

void SceneGame::Update(float dt)
{
	playTime += check;

	for (auto pinkEnt : mPinkEnt)
	{
		pinkEnt->Update(dt, player);
	}

	for (auto SwordMan : mSwordMans)
	{
		SwordMan->Update(dt, player);
	}
	
	player.Update(dt, tilemap.GetRects());

	tilemap.CreateBackGround();

	ui.Update(dt);


	// 보스가 플레이어 기본공격에 맞음
	bool checkBossHIt = boss.GetGlobalBound().intersects(player.GetPlayerAttackRect());
	if (checkBossHIt)
	{
		if (player.GetIsAttack() && boss.underAttack(dt))
		{
			boss.SetBossHp(10);
			ui.SetBossHpbarSize(boss.GetCurrentHp(), boss.GetMaxHp());
		}
	}
	bool checkBossSkillHIt = boss.GetGlobalBound().intersects(player.GetPlayerSkiilRect());
	if (checkBossSkillHIt)
	{
		if (player.GetIsSkill() && boss.underAttack(dt))
		{
			boss.SetBossHp(50);
			ui.SetBossHpbarSize(boss.GetCurrentHp(), boss.GetMaxHp());
		}
	}


	ui.SetHpbarText(player.GetCurrentPlayerHealth(), player.GetMaxPlayerHealth());
	ui.SetHpbarSize(player.GetCurrentPlayerHealth(), player.GetMaxPlayerHealth());

	// 플레이어가 보스 기본공격에 맞음



	// 마우스 충돌시 피 까임 확인용
	bool checkHpHit = ui.GetMouseBound().intersects(player.GetGlobalBound());
	if (checkHpHit)
	{
		if (InputManager::GetMouseButtonDown(Mouse::Left))
		{
			player.Hit(damage);
			ui.SetHpbarText(player.GetCurrentPlayerHealth(), player.GetMaxPlayerHealth());
			ui.SetHpbarSize(player.GetCurrentPlayerHealth(), player.GetMaxPlayerHealth());
			ui.UnderAttack(player.GetPosition(), dt);
		}
	}
	/*bool checkBossHIt = ui.GetMouseBound().intersects(boss.GetGlobalBound());
	if (checkBossHIt)
	{
		if (InputManager::GetMouseButtonDown(Mouse::Left))
		{
			boss.underAttack(10);
			ui.SetBossHpbarSize(boss.GetCurrentHp(), boss.GetMaxHp());

		}
	}*/



	if (InputManager::GetKeyDown(Keyboard::Num7))
	{
		mgr.ChangeScene(Scenes::END);
	}

	boss.Update(dt, player.GetPlayerPosition());
}

void SceneGame::Draw(sf::RenderWindow* window)
{

	window->draw(spriteBackground);
	tilemap.Draw(window);
	
	for (auto SwordMan : mSwordMans)
	{
		SwordMan->Draw(*window);
	}
	for (auto pinkEnt : mPinkEnt)
	{
		pinkEnt->Draw(*window);
	}
	player.Draw(*window);
	ui.DrawSceneGame(window);
	
	boss.Draw(*window);
}

void SceneGame::CreateSwordMan(std::vector<swordman*>& mSwordMans, int count)
{
	for (auto swordman : mSwordMans)
	{
		delete swordman;
	}
	mSwordMans.clear();

	for (int i = 0; i < count; i++)
	{
		int x = RandomMgr::GetRandom(1240,1500);
		int y = 900;
		mSwordman = new swordman(x, y);
		mSwordman->Init();
		mSwordMans.push_back(mSwordman);
	}
	
}

void SceneGame::CreatePinkEnt(std::vector<PinkEnt*>& mpinkEnt, int count)
{
	for (auto pinkEnt : mpinkEnt)
	{
		delete pinkEnt;
	}
	mpinkEnt.clear();

	for (int i = 0; i < count; i++)
	{
		int x = RandomMgr::GetRandom(900,1100);
		int y = 575;
		pinkEnt = new PinkEnt(x, y);
		pinkEnt->Init();
		mpinkEnt.push_back(pinkEnt);
	}
}

//int SceneGame::GetMaxPlayerHealthReal()
//{
//	return  player.GetMaxPlayerHealth();
//}

