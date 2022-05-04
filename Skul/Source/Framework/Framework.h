#pragma once
#include <SFML/Graphics.hpp>
#include "../Manager/SceneMgr.h"

using namespace sf;

class Framework
{
private:
	RenderWindow* window;	// SFML기본 윈도우
	Clock clock;			// 시계
	SceneMgr sceneMgr;		// scene 매니저

	Framework(const Framework& ref) {} 
	Framework& operator=(const Framework& ref) {}
public:
	Framework() {} // 멤버변수 초기화
	~Framework() {}

	bool Init();
	void Run();

	void ProcessEvent(Event event);	    //키입력
	void Update(float delaTime);		//업데이트
	void Draw(RenderWindow* window);	//그리기

	// 윈도우 생성
	// 메인 루프
	// 부가 // 난수, 시간
};

