#include "SceneTitle.h"
#include "ResourceMgr.h"

void SceneTitle::Init()
{
	/*test.setFont(*ResourceMgr::instance()->GetFont("MAINFONT"));
	test.setString("MAIN");
	test.setFillColor(Color::White);
	test.setCharacterSize(100);
	test.setPosition(0, 0);*/
	spriteTitle.setTexture(*ResourceMgr::instance()->GetTexture("TITLETEX"));
	spriteStart1.setTexture(*ResourceMgr::instance()->GetTexture("STARTTEX1"));
	spriteStart2.setTexture(*ResourceMgr::instance()->GetTexture("STARTTEX2"));
	//spriteStart1.setPosition(900, 700);
	//spriteStart2.setPosition(900, 700);
}

void SceneTitle::Release()
{

}

void SceneTitle::Start()
{

}

void SceneTitle::End()
{

}

void SceneTitle::Update(float dt)
{
	if (Keyboard::isKeyPressed(Keyboard::Return))
	{
		mgr.ChangeScene(Scenes::MENU);
	}
}

void SceneTitle::Draw(sf::RenderWindow* window)
{
	window->draw(spriteTitle);
	/*window->draw(spriteStart1);*/
}
