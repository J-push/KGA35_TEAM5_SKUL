/******************************************************************************
* 작 성 자 : 김 재 휘
* 작 성 일 : 2022-05-04
* 내    용 : Scene들을 관리하는 매니저 파일
* 수 정 일 :
*******************************************************************************/
/*include될 헤더*/
#include "SceneMgr.h"
#include "../Scene/SceneTitle.h"
#include "../Scene/SceneGame.h"
#include "../Scene/SceneCharacter.h"
#include "../Scene/SceneMenu.h"
/**********************************************************
* 설명 : Scene들을 초기화한다.
***********************************************************/
void SceneMgr::Init()
{
	scenes[(int)Scenes::TITLE] = new SceneTitle(*this);
	scenes[(int)Scenes::MENU] = new SceneMenu(*this);
	scenes[(int)Scenes::CHARACTER] = new SceneCharacter(*this);
	scenes[(int)Scenes::GAME] = new SceneGame(*this);

	scenes[(int)Scenes::TITLE]->Init();	
	scenes[(int)Scenes::MENU]->Init();
	scenes[(int)Scenes::CHARACTER]->Init();
	scenes[(int)Scenes::GAME]->Init();
}
/*******************************************************************
* 설명 : Scene하나하나가 끝날때마다 새로운 Scene을 받아와 시작한다.
********************************************************************/
void SceneMgr::ChangeScene(Scenes newScene)
{
	scenes[(int)currentScene]->End();
	currentScene = newScene;
	scenes[(int)currentScene]->Start();
}
/*******************************************************************
* 설명 : 장면을 업데이트 한다.
********************************************************************/
void SceneMgr::Update(float dt)
{
	scenes[(int)currentScene]->Update(dt);
}

/*******************************************************************
* 설명 : 현재 장면들을 그린다.
********************************************************************/
void SceneMgr::Draw(sf::RenderWindow* window)
{
	scenes[(int)currentScene]->Draw(window);
}
