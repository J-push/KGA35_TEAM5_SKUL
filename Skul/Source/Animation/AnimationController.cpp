/******************************************************************************
* 작 성 자 : 김 재 휘
* 작 성 일 : 2022-05-03
* 내    용 : AnimationControllere 부분의 동작을 구현한다.
* 수 정 일 : 주석 다 안담
*******************************************************************************/

/*include 될 헤더파일*/
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
* 설명 : AnimationClip에 아이디를 추가?
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
		// 안됐다고 표현하기?
	}
}

/**********************************************************
* 설명 : Animation을 업데이트 한다.
***********************************************************/
void AnimationController::Update(float dt)
{
	if (!isPlaying) // 플레이중이 아닐 때
	{
		return;
	}
	accumTime += dt;
	if (accumTime < frameDuration) // 현재시간이 frameDuration보다 작을 때는 넘어감
	{
		return;
	}
	accumTime = 0.f;
	++currentFrame; // 다음 프레임으로
	if (currentFrame >= totalFrame) 
	{
		if (playQueue.empty()) // 큐스텍이 비었는지 찬건지 ??
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
			std::string nextClipId = playQueue.front(); // 첫번째 원소에 접근
			playQueue.pop();                            // 가장 뒤 제거
			Play(nextClipId, false);
		}
	}
	// 타겟sprite의 조절
	sprite->setTexture(currentClip->frames[currentFrame].texture);
	sprite->setTextureRect(currentClip->frames[currentFrame].texCoord);
}


/**********************************************************
* 설명 : Play를 위한 설정을 한다??
***********************************************************/
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


/**********************************************************
* 설명 : 원소를 삽입하고 play상태로 변경한다.
***********************************************************/
void AnimationController::PlayQueue(std::string clipId)
{
	isPlaying = true;
	playQueue.push(clipId); // 해당자료구조에 집어넣기
}

/**********************************************************
* 설명 : 큐스택을 비우고 play상태를 false로 변경한다.
***********************************************************/
void AnimationController::Stop()
{
	isPlaying = false; 
	ClearPlayQueue();
}

/**********************************************************
* 설명 : isplaying의 상태를 받아온다.
***********************************************************/
bool AnimationController::IsPlaying()
{
	return isPlaying;
}

/**********************************************************
* 설명 : 큐를 비운다.
***********************************************************/
void AnimationController::ClearPlayQueue()
{
	while (!playQueue.empty())
	{
		playQueue.pop();
	}
}