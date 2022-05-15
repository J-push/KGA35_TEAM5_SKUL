#include "SceneMenu.h"
#include "../Manager/ResourceMgr.h"

void SceneMenu::Init()
{
	map.Init();
}

void SceneMenu::Release()
{
	map.Release();
}

void SceneMenu::Start()
{
}

void SceneMenu::End()
{
}

void SceneMenu::Update(float dt, RenderWindow *window, View *mainView)
{
	map.Update(dt, window, mainView);
}

void SceneMenu::Draw(sf::RenderWindow *window, View *mainView, View *uiView)
{
	//window->setMouseCursorVisible(false);
	map.Draw(window, mainView, uiView);
}
