#include "Framework.h"
#include "../Manager/ResourceMgr.h"
#include "../Manager/RandomMgr.h"
#include "../Utils/Singleton.h"
#include <iostream>

using namespace std;

Framework::Framework()
{
}
Framework::~Framework()
{
}

/**********************************************************
* 설명 : Framework를 초기화한다.
***********************************************************/
bool Framework::Init()
{	
	VideoMode vm(1920, 1080);                               // 해상도	
	window = new RenderWindow(vm, "Skull", Style::Fullscreen); // 창그려주기
	                                                        //Default 창모드, fullscreen 풀모드

	ResourceMgr::instance()->Init(); // singleton패턴을 이용하여 ResourceMgr 클래스의 Init()함수 실행
	sceneMgr.Init();		         // 장면들 초기화한다.
	return true;
}

/**********************************************************
* 설명 : 게임루프를 시작한다.
***********************************************************/
void Framework::Run()
{
	while (window->isOpen())
	{
		Time dt = clock.restart();
		Event event;
		while (window->pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				window->close();
				break;
			}
			ProcessEvent(event);
		}

		Update(dt.asSeconds());
		Draw(window);
	}
}
/**********************************************************
* 설명 : 키 입력 처리를 한다.
***********************************************************/
void Framework::ProcessEvent(Event event)
{
}

/**********************************************************
* 설명 : 업데이트를 처리한다.
***********************************************************/
void Framework::Update(float delaTime)
{
	sceneMgr.Update(delaTime);
}

/**********************************************************
* 설명 : 화면에 scene을 그려준다.
***********************************************************/
void Framework::Draw(RenderWindow* window)
{
	window->clear();

	sceneMgr.Draw(window);

	window->display();
}
