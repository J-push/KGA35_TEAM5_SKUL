#include "SceneEnd.h"



void SceneEnd::Init()
{
	

	//test.setFont(*ResourceMgr::instance()->GetFont("MAINFONT"));
	//test.setString("MENU");
	// 엔드용
	spriteScoreFrame.setTexture(*ResourceMgr::instance()->GetTexture("SCORETEX"));
	spriteScoreFrame.setPosition(130, 50);

	spriteScoreFrame.setScale(1.3, 1.3);
}

void SceneEnd::Release()
{
}

void SceneEnd::Start()
{
}

void SceneEnd::End()
{
}

void SceneEnd::Update(float dt)
{
	

}

void SceneEnd::Draw(sf::RenderWindow *window)
{
	
	//엔드용
	window->draw(spriteScoreFrame);
	//window->draw(test);
}