#include "AnimationController.h"

/**********************************************************
* ���� : AnimationController�� ��ü �ʱ�ȭ
***********************************************************/
AnimationController::AnimationController()
	: clips(), currentClip(nullptr), isPlaying(false), currentFrame(-1),
	totalFrame(0), frameDuration(0.f), accumTime(0.f), sprite(nullptr)
{
}

/**********************************************************
* ���� : Ÿ���� ����??
***********************************************************/
void AnimationController::SetTarget(Sprite *sprite)
{
	this->sprite = sprite;
}

/**********************************************************
* ���� : Ŭ���� �߰�??
***********************************************************/
void AnimationController::AddClip(const AnimationClip &newClip)
{
	// �ʿ� �������� ���������� �ֳ����� �˻��ϰ� �ֱ�
	if (clips.find(newClip.id) == clips.end()) // ���°��
	{
		clips[newClip.id] = newClip;
	}
	else
	{
		// ����, �ߺ��Ȱ� ������������
	}
}


void AnimationController::Update(float dt)
{
	if (!isPlaying)
	{
		return;
	}
	accumTime += dt;
	if (accumTime < frameDuration) // �� �۾Ƽ� ������ü ����
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

	// Ÿ��sprite�� ����
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
	frameDuration = 1.f / currentClip->fps; // �� �����Ӵ� �� �� ������
	//frameDurtion = currentClip->fps;
}

void AnimationController::PlayQueue(std::string clipId)
{
	isPlaying = true;
	playQueue.push(clipId); // �ش��ڷᱸ���� ����ֱ�
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