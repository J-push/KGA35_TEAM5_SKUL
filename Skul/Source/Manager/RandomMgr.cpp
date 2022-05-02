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

int RandomMgr::GetRandom(int min, int max)
{
	uniform_int_distribution<> dist(min, max); 
	return dist(gen);
}
