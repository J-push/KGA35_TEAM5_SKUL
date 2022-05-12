/******************************************************************************
* 작 성 자 : 김 재 휘
* 작 성 일 : 2022-05-04
* 내    용 : skul게임의 전체적인 프레임워크를 담당.
* 수 정 일 :
*******************************************************************************/
/*include될 헤더*/
#include <iostream>
#include "Framework.h"
#include "../Manager/ResourceMgr.h"
#include "../Manager/RandomMgr.h"
#include "../Utils/Singleton.h"
#include "../Manager/InputManager.h"

using namespace std;
/**********************************************************
* 설명 : Framework를 초기화한다.
***********************************************************/
bool Framework::Init()
{	
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;
	VideoMode vm(1920, 1080);                               // 해상도	
	window = new RenderWindow(vm, "Skull", Style::Default); // 창그려주기
	                                                        //Default 창모드, fullscreen 풀모드
	mainView = new View(FloatRect(0, 0, resolution.x, resolution.y));
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
		InputManager::ClearInput();
		Event event;
		while (window->pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				window->close();
				break;
			case Event::KeyPressed:
				switch (event.key.code)
				{
				case Keyboard::Escape:
					window->close();
					break;
				}
			}
			if (event.key.code == Keyboard::Escape)
			{
				window->close();
			}
			InputManager::ProcessInput(event);
			//ProcessEvent(event);
		}

		Update(dt.asSeconds(), window, mainView);
		Draw(window, mainView, uiView);
	}
}
/**********************************************************
* 설명 : 키 입력 처리를 한다.
***********************************************************/
void Framework::ProcessEvent(Event event)
{
	InputManager::ProcessInput(event);
}

/**********************************************************
* 설명 : 업데이트를 처리한다.
***********************************************************/
void Framework::Update(float delaTime, RenderWindow *window, View *mainView)
{
	sceneMgr.Update(delaTime, window, mainView);
	InputManager::Update(delaTime, *window, *mainView);
}

/**********************************************************
* 설명 : 화면에 scene을 그려준다.
***********************************************************/
void Framework::Draw(sf::RenderWindow *window, View *mainView, View *uiView)
{
	window->clear();

	sceneMgr.Draw(window, mainView, uiView);

	window->display();
}
