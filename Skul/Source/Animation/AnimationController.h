#pragma once

#include "AnimationClip.h"

#include <map>
#include <queue> // stl �ڷᱸ��
#include <iostream> // cpp�� ����

using namespace sf;

class AnimationController
{
private:
	std::map<std::string, AnimationClip> clips; // map <key type, value type>
	std::queue<std::string> playQueue;          // FIFO �ڷᱸ��

	AnimationClip *currentClip;
	bool isPlaying;      
	int currentFrame;    
	int totalFrame;     
	float frameDuration; 

	float accumTime;

	Sprite *sprite; // ������ ����??

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

