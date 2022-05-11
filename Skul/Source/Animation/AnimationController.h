#pragma once
/*include 될 헤더파일*/
#include "AnimationClip.h"
#include <map>
#include <queue> // stl 자료구조
#include <iostream> // cpp에 쓰임
#include "../Animation/rapidcsv.h"

using namespace sf;

class AnimationController
{
private:
	std::map<std::string, AnimationClip> clips; // map <key type, value type>
	std::queue<std::string> playQueue;          // FIFO 자료구조

	AnimationClip *currentClip;
	bool isPlaying;							//플레이 유무
	int currentFrame;						//현재 프레임
	int totalFrame;							//전체 프레임
	float frameDuration; 

	float accumTime;

	Sprite *sprite;						// 포인터 이유??

public:
	std::function<void()> OnComplete;

	AnimationController();

	void SetTarget(Sprite *sprite);
	void AddClip(const AnimationClip &newClip);

	void Update(float dt);

	void Play(std::string clipId, bool clear = true);
	void PlayQueue(std::string clipId);

	void Stop();

	bool IsPlaying();
	void ClearPlayQueue();
	bool ClearPlayQueueCheck();

};

