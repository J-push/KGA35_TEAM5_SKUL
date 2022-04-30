#include "SceneMenu.h"
#include "ResourceMgr.h"

void SceneMenu::Init()
{
	test.setFont(*ResourceMgr::instance()->GetFont("MAINFONT"));
	test.setString("MENU");
}

void SceneMenu::Release()
{
}

void SceneMenu::Start()
{
}

void SceneMenu::End()
{
}

void SceneMenu::Update(float dt)
{
	if (Keyboard::isKeyPressed(Keyboard::Space))
	{
		mgr.ChangeScene(Scenes::GAME);
	}
}

void SceneMenu::Draw(sf::RenderWindow* window)
{
	window->draw(test);
}
