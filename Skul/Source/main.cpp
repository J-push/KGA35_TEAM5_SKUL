﻿/******************************************************************************
* 작 성 자 : 김 재 휘
* 작 성 일 : 2022-05-04
* 내    용 : main 함수를 실행한다.
* 수 정 일 : 
*******************************************************************************/
/*include될 헤더*/
#include <iostream>
#include "Framework/Framework.h"

using namespace std;
/**********************************************************
* 설명 : main() 함수를 실행한다.
***********************************************************/
int main()
{
	Framework framework;		//framework클래스 객체

	if (!framework.Init())		//초기화 실패시
	{
		cout << "초기화 할 수 없습니다." << endl;
		return 1;
	}

	framework.Run();			//초기화 성공시 run()
	cout << "종료" << endl;
	return 0;
}
