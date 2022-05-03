#include "RandomMgr.h"
using namespace std;

random_device RandomMgr::rd;
mt19937 RandomMgr::gen = mt19937(RandomMgr::rd());

RandomMgr::RandomMgr()
{

}

RandomMgr::~RandomMgr()
{
}

void RandomMgr::Init()
{

}

/**********************************************************
* 설명 : 랜덤 숫자를 가지고 온다.
* 변수 1 : 제일 작은 값, 변수 2 : 제일 큰값
***********************************************************/
int RandomMgr::GetRandom(int min, int max)
{
	uniform_int_distribution<> dist(min, max); 
	return dist(gen);
}
