/******************************************************************************
* 작 성 자 : 김 재 휘
* 작 성 일 : 2022-05-04
* 내    용 : Scene의 틀을 담당한다.
* 수 정 일 :
*******************************************************************************/
/*include될 헤더*/
#include "Scene.h"

Scene::Scene(SceneMgr& mgr) : mgr(mgr)
{
}

void Scene::Init()
{
}

void Scene::Release()
{
}

void Scene::Start()
{
}

void Scene::End()
{
}

void Scene::Update(float dt, RenderWindow *window, View *mainView)
{
}

void Scene::Draw(sf::RenderWindow *window,View *mainView, View *uiView)
{
}
