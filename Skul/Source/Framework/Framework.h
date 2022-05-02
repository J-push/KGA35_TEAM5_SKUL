#pragma once
#include <SFML/Graphics.hpp>
#include "../Utils/Singleton.h"
#include "../Manager/ResourceMgr.h"
#include "../Manager/RandomMgr.h"
#include "../Manager/SceneMgr.h"

using namespace sf;
/**********************************************************
* ���� : Framework Ŭ������ �����Ѵ�.
***********************************************************/
class Framework
{
private:
	RenderWindow* window;	//SFML�⺻ ������
	Clock clock;			//�ð�
	SceneMgr sceneMgr;		//scene�Ŵ���

	Framework(const Framework& ref) {}
	Framework& operator=(const Framework& ref) {}
public:
	Framework();
	~Framework();

	bool Init();
	void Run();


	void ProcessEvent(Event event);				//Ű�Է�
	void Update(float delaTime);		//������Ʈ
	void Draw(RenderWindow* window);	//�׸���

	// ������ ����
	// ���� ����
	// �ΰ� // ����, �ð�
};

