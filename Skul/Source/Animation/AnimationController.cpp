#include "AnimationController.h"

/**********************************************************
* 설명 : AnimationController의 객체 초기화
***********************************************************/
AnimationController::AnimationController()
	: clips(), currentClip(nullptr), isPlaying(false), currentFrame(-1),
	totalFrame(0), frameDuration(0.f), accumTime(0.f), sprite(nullptr)
{
}

/**********************************************************
* 설명 : 타겟을 잡음??
***********************************************************/
void AnimationController::SetTarget(Sprite *sprite)
{
	this->sprite = sprite;
}

/**********************************************************
* 설명 : 클립을 추가??
***********************************************************/
void AnimationController::AddClip(const AnimationClip &newClip)
{
	// 맵에 넣을때는 습관적으로 있나없나 검사하고 넣기
	if (clips.find(newClip.id) == clips.end()) // 없는경우
	{
		clips[newClip.id] = newClip;
	}
	else
	{
		// 오류, 중복된거 가지고있을때
	}
}


void AnimationController::Update(float dt)
{
	if (!isPlaying)
	{
		return;
	}
	accumTime += dt;
	if (accumTime < frameDuration) // 더 작아서 아직교체 안함
	{
		return;
	}
	accumTime = 0.f;
	++currentFrame;
	if (currentFrame >= totalFrame)
	{
		if (playQueue.empty())
		{
			switch (currentClip->loopType)
			{
			case AnimationLoopTypes::Single:
				currentFrame = totalFrame - 1;
				break;
			case AnimationLoopTypes::Loop:
				currentFrame = 0;
				break;
			default:
				break;
			}
		}
		else
		{
			std::string nextClipId = playQueue.front();
			playQueue.pop();
			Play(nextClipId, false);
		}

	}

	// 타겟sprite의 조절
	sprite->setTexture(currentClip->frames[currentFrame].texture);
	sprite->setTextureRect(currentClip->frames[currentFrame].texCoord);
}

void AnimationController::Play(std::string clipId, bool clear)
{
	if (clear)
	{
		ClearPlayQueue();
	}
	isPlaying = true;
	currentClip = &clips[clipId];
	currentFrame = 0;
	totalFrame = currentClip->frames.size();
	frameDuration = 1.f / currentClip->fps; // 한 프레임당 몇 초 쓰는지
	//frameDurtion = currentClip->fps;
}

void AnimationController::PlayQueue(std::string clipId)
{
	isPlaying = true;
	playQueue.push(clipId); // 해당자료구조에 집어넣기
}

void AnimationController::Stop()
{
	isPlaying = false; 
	ClearPlayQueue();
}

bool AnimationController::IsPlaying()
{
	return isPlaying;
}

void AnimationController::ClearPlayQueue()
{
	while (!playQueue.empty())
	{
		playQueue.pop();
	}
}