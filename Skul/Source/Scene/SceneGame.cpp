#include "SceneGame.h"
#include "../Manager/ResourceMgr.h"
#include "../Manager/RandomMgr.h"
#include "../Framework/Framework.h"


void SceneGame::Init()
{
	player.Init();
	/*spriteBackground.setTexture(*ResourceMgr::instance()->GetTexture("MAINBGTEX"));
	spritePlayer.setTexture(*ResourceMgr::instance()->GetTexture("MAINPLAYERTEX"));
	spriteCloud.setTexture(*ResourceMgr::instance()->GetTexture("MAINCLOUDTEX"));
	spriteBee.setTexture(*ResourceMgr::instance()->GetTexture("MAINBEETEX"));
	spriteBee.setPosition(500, 500);
	spriteCloud.setPosition(300, 300);*/
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

	//	// 화면 밖으로 나갔는지 테스트
	//	if (currPos.x < -100)
	//	{
	//		beeActive = false;
	//	}
	//}
	//
}

void SceneGame::Draw(sf::RenderWindow* window)
{
	//window->draw(player.Draw(window));
	player.Draw(*window);
	/*window->draw(spriteBackground);*/
	/*window->draw(spriteBee);*/
}
