#pragma once

#include "AnimationClip.h"

#include <map>
#include <queue> // stl 자료구조
#include <iostream> // cpp에 쓰임

using namespace sf;

class AnimationController
{
private:
	std::map<std::string, AnimationClip> clips; // map <key type, value type>
	std::queue<std::string> playQueue; // FIFO

	AnimationClip *currentClip;
	bool isPlaying;      // 재생중인지
	int currentFrame;    // 몇번째꺼 재생중인지
	int totalFrame;      // 총 갯수
	float frameDuration; // 지속시간????

	float accumTime;

	Sprite *sprite;

public:
	AnimationController();

	void SetTarget(Sprite *sprite);
	void AddClip(const AnimationClip &newClip);

	void Update(float dt);

	void Play(std::string clipId, bool clear = true);
	void PlayQueue(std::string clipId);

	void Stop();

	bool IsPlaying();
	void ClearPlayQueue();
};

