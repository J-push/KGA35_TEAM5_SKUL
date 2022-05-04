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
* ���� : Framework�� �ʱ�ȭ�Ѵ�.
***********************************************************/
bool Framework::Init()
{	
	VideoMode vm(1920, 1080);                               // �ػ�	
	window = new RenderWindow(vm, "Skull", Style::Fullscreen); // â�׷��ֱ�
	                                                        //Default â���, fullscreen Ǯ���

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
* ���� : Ű �Է� ó���� �Ѵ�.
***********************************************************/
void Framework::ProcessEvent(Event event)
{
}

/**********************************************************
* ���� : ������Ʈ�� ó���Ѵ�.
***********************************************************/
void Framework::Update(float delaTime)
{
	sceneMgr.Update(delaTime);
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
