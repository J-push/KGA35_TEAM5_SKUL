#include "SceneGame.h"
#include "../Manager/ResourceMgr.h"
#include "../Manager/RandomMgr.h"
#include "../Framework/Framework.h"

void SceneGame::Init()
{
	spriteBackground.setTexture(*ResourceMgr::instance()->GetTexture("BACKGROUNDTEX"));
	spriteBackground.setScale(Vector2f(backGroundX, backGroundY));
	tilemap.Init();
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
	tilemap.CreateBackGround();
}

void SceneGame::Draw(sf::RenderWindow *window)
{
	window->draw(spriteBackground);
	tilemap.Draw(window);
}
