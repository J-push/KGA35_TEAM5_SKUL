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


void SceneGame::Init()
{
	spriteBackground.setTexture(*ResourceMgr::instance()->GetTexture("BACKGROUNDTEX"));
	spriteBackground.setScale(Vector2f(backGroundX, backGroundY));
	tilemap.Init();
	SwordMan.Init();
	player.Init();
	ui.Init();
	mouseCursor.Init();

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

void SceneGame::Update(float dt)
{

	player.Update(dt);

	SwordMan.Update(dt, player.GetGlobalBound());

	tilemap.CreateBackGround();

	mouseCursor.Update(dt);
	ui.Update(dt);

}

void SceneGame::Draw(sf::RenderWindow *window)
{

	window->draw(spriteBackground);
	tilemap.Draw(window);
	player.Draw(*window);
	//boss.Draw(*window);
	ui.DrawSceneGame(window);

	SwordMan.Draw(*window);

}
