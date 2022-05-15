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
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;
	playerView = new View(FloatRect(0, 0, resolution.x, resolution.y));
	playerView->setSize(1920.f, 1080.f);

	spriteBackground.setTexture(*ResourceMgr::instance()->GetTexture("BACKGROUNDTEX"));
	spriteBackground.setScale(Vector2f(backGroundX, backGroundY));
	spriteTile.setTexture(*ResourceMgr::instance()->GetTexture("TILETEX"));
	rect.Init();
	rect.LoadRect();
	rect.LoadImage();
	CreateSwordMan(mSwordMans, 1);
	CreatePinkEnt(mPinkEnt, 1);
	player.Init();
	player.SkillInit();
	player.ChangeEffectInit();
	ui.Init();

	boss.Init();
	check = forCheckTime.restart();
}

void SceneGame::Release()
{
}

void SceneGame::Start()
{

}

void SceneGame::End()
{
}

void SceneGame::Update(float dt, RenderWindow *window, View *mainView)
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
	
	player.Update(dt, tileMap.Getrects());
	boss.Update(dt, player.GetPlayerPosition());
	ui.Update(dt);


	// 보스가 플레이어 기본공격에 맞음
	bool isPlayerAttack = boss.GetGlobalBound().intersects(player.GetPlayerAttackRect());
	if (isPlayerAttack)
	{
		if (player.GetIsAttack() && boss.underAttack(dt))
		{
			boss.SetBossHp(10);		
		}
	}
	// 보스가 플레이어 스킬에 맞음
	bool isPlayerSkill = boss.GetGlobalBound().intersects(player.GetPlayerSkiilRect());
	if (isPlayerSkill)
	{
		if (player.GetIsSkill() && boss.underAttack(dt))
		{
			boss.SetBossHp(5);
		}
	}


	// 플레이어가 보스 한테 맞음
	boss.UpdateCollision(player);
	player.PlayerConllision(rect.Getrects());


	// 마우스 충돌시 피 까임 확인용
	bool checkPlayerHit = ui.GetMouseBound().intersects(player.GetGlobalBound());
	if (checkPlayerHit)
	{
		if (InputManager::GetMouseButtonDown(Mouse::Left))
		{
			player.Hit(10);
		}
	}
	bool checkBossHIt = ui.GetMouseBound().intersects(boss.GetGlobalBound());
	if (checkBossHIt)
	{
		if (InputManager::GetMouseButtonDown(Mouse::Left))
		{
			boss.SetBossHp(220);
		}
	}

	if (InputManager::GetKey(Keyboard::Right))
	{
		playerView->move(200 * dt, 0.f);
	}
	if (InputManager::GetKeyDown(Keyboard::Z))
	{
		playerView->move(1000 * dt, 0.f);
	}

	if (InputManager::GetKey(Keyboard::Left))
	{
		playerView->move(-200 * dt, 0.f);
		
	}

	ui.SetHpbarSize(player.GetCurrentPlayerHealth(), player.GetMaxPlayerHealth());
	ui.SetHpbarText(player.GetCurrentPlayerHealth(), player.GetMaxPlayerHealth());
	ui.SetBossHpbarSize(boss.GetCurrentHp(), boss.GetMaxHp());
	if (!boss.isAlive())
	{
		mgr.ChangeScene(Scenes::END);
	}
}

void SceneGame::Draw(sf::RenderWindow *window, View *mainView, View *uiView)
{
	window->setView(*playerView);
	window->draw(spriteBackground);
	for (auto blockshape : rect.Getrects())
	{
		window->draw(blockshape->GetRectShape());
	}
	
	rect.DrawMap(window,mainView,uiView);

	for (auto SwordMan : mSwordMans)
	{
		SwordMan->Draw(*window);
	}
	player.Draw(*window);
	for (auto pinkEnt : mPinkEnt)
	{
		pinkEnt->Draw(*window);
	}
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
		int x = RandomMgr::GetRandom(576,928);
		int y = 576;
		pinkEnt = new PinkEnt(x, y);
		pinkEnt->Init();
		mpinkEnt.push_back(pinkEnt);
	}
}


