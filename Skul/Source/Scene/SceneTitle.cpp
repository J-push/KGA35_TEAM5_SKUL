/******************************************************************************
* 작 성 자 : 김 재 휘
* 작 성 일 : 2022-05-03
* 내    용 : 게임의 Tilte정보를 담당한다.
* 수 정 일 : 
*******************************************************************************/
/*include될 헤더*/
#include "SceneTitle.h"
#include "../Manager/ResourceMgr.h"
//#include "../Animation/rapidcsv.h" // 애니컨트롤러에 추가함 지워도댐
#include <iostream>
/**********************************************************
* 설명 : SceneTitle을 초기화한다.
***********************************************************/
void SceneTitle::Init()
{
	spriteTitle.setTexture(*ResourceMgr::instance()->GetTexture("TITLETEX"));

	ui.Init();

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
/**********************************************************
* 설명 : SceneTitle을 업데이트한다.
***********************************************************/
void SceneTitle::Update(float dt, RenderWindow *window, View *mainView)
{
	
	if (ui.GetClickGameStart())
	{
		mgr.ChangeScene(Scenes::GAME);
	}
	


	if (InputManager::GetKeyDown(Keyboard::Return))
	{
		mgr.ChangeScene(Scenes::GAME);
	}
	if (Keyboard::isKeyPressed(Keyboard::Num0))
	{
		mgr.ChangeScene(Scenes::EDITOR);
	}
	ui.Update(dt);

}

/**********************************************************
* 설명 : SceneTitle을 그린다.
***********************************************************/
void SceneTitle::Draw(sf::RenderWindow *window, View *mainView, View *uiView)
{
	window->draw(spriteTitle);

	
	ui.DrawSceneTitle(window);



}

