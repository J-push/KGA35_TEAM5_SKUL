#include <iostream>
#include "Framework.h"

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

	return 0;
}
