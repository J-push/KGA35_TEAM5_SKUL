/******************************************************************************
* 작 성 자 : 김 재 휘
* 작 성 일 : 2022-05-03
* 내    용 : 게임이 진행중인 Scene의 정보를 담당한다.
* 수 정 일 : 2022-05-04(임병록)
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
  
	player.Init();
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
	//if (!beeActive)
	//{
	//	beeSpeed = RandomMgr::GetRandom(200, 200);
	//	beeSpeed *= -1.f;
	//	float y = RandomMgr::GetRandom(500, 500);
	//	spriteBee.setPosition(2000, y);
	//	beeActive = true;
	//}
	//else
	//{
	//	float deltaX = beeSpeed * dt;
	//	Vector2f currPos = spriteBee.getPosition();
	//	currPos.x += deltaX;
	//	spriteBee.setPosition(currPos);

	//	// ȭ�� ����� �������� �׽�Ʈ
	//	if (currPos.x < -100)
	//	{
	//		beeActive = false;
	//	}
	//}
	//

	tilemap.CreateBackGround();

}

void SceneGame::Draw(sf::RenderWindow *window)
{

	//window->draw(player.Draw(window));
	
	/*window->draw(spriteBackground);*/
	/*window->draw(spriteBee);*/

	window->draw(spriteBackground);
	tilemap.Draw(window);
	player.Draw(*window);
}
