#include "SceneMenu.h"
#include "../Manager/ResourceMgr.h"

void SceneMenu::Init()
{
	//test.setFont(*ResourceMgr::instance()->GetFont("MAINFONT"));
	//test.setString("MENU");
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
	map.Update(dt,window, mainView);
}

void SceneMenu::Draw(sf::RenderWindow *window, View *mainView, View *uiView)
{
	map.Draw(window, mainView, uiView);
}
