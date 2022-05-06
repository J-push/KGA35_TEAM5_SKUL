/******************************************************************************
* �� �� �� : �� �� ��
* �� �� �� : 2022-05-04
* ��    �� : skul������ ��ü���� �����ӿ�ũ�� ���.
* �� �� �� :
*******************************************************************************/
/*include�� ���*/
#include <iostream>
#include "Framework.h"
#include "../Manager/ResourceMgr.h"
#include "../Manager/RandomMgr.h"
#include "../Utils/Singleton.h"
#include "../Manager/InputManager.h"

using namespace std;
/**********************************************************
* ���� : Framework�� �ʱ�ȭ�Ѵ�.
***********************************************************/
bool Framework::Init()
{	
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;
	VideoMode vm(1920, 1080);                               // �ػ�	
	window = new RenderWindow(vm, "Skull", Style::Default); // â�׷��ֱ�
	                                                        //Default â���, fullscreen Ǯ���
	mainView = new View(FloatRect(0, 0, resolution.x, resolution.y));
	ResourceMgr::instance()->Init(); // singleton������ �̿��Ͽ� ResourceMgr Ŭ������ Init()�Լ� ����
	sceneMgr.Init();		         // ���� �ʱ�ȭ�Ѵ�.
	return true;
}

/**********************************************************
* ���� : ���ӷ����� �����Ѵ�.
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
			ProcessEvent(event);
		}

		Update(dt.asSeconds());
		Draw(window);
	}
}
/**********************************************************
* ���� : Ű �Է� ó���� �Ѵ�.
***********************************************************/
void Framework::ProcessEvent(Event event)
{
	InputManager::ProcessInput(event);
}

/**********************************************************
* ���� : ������Ʈ�� ó���Ѵ�.
***********************************************************/
void Framework::Update(float delaTime)
{
	sceneMgr.Update(delaTime);
	InputManager::Update(delaTime, *window, *mainView);
}

/**********************************************************
* ���� : ȭ�鿡 scene�� �׷��ش�.
***********************************************************/
void Framework::Draw(RenderWindow* window)
{
	window->clear();

	sceneMgr.Draw(window);

	window->display();
}
