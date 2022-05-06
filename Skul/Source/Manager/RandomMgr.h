#pragma once
#include <random>

class RandomMgr
{
private:
	static std::random_device rd;
	static std::mt19937 gen;
	RandomMgr() {}
	~RandomMgr() {}
	RandomMgr operator=(const RandomMgr& random) {}

public:
	static void Init() {}
	static int GetRandom(int min, int max);
};
