#include "BossFire.h"

BossFire::BossFire() : speed(DEFAULT_SPEED), distance(DEFAULT_DISTANCE)
{
	// �浹 Ȯ��
	fireRect.setSize(Vector2f(80, 40));
	fireRect.setFillColor(Color(140, 72, 19, 70));
	fireRect.setPosition(position);

	spriteFireBall.setScale(0.8f, 0.8f);
	Utils::SetOrigin(spriteFireBall, Pivots::CB);

	animation.SetTarget(&spriteFireBall);

	spriteSuperEffect.setScale(2.0f, 2.0f);
	spriteSuperEffect.setPosition(Vector2f(100, 100));
	animationSuperEffect.SetTarget(&spriteSuperEffect);

	rapidcsv::Document clipsFire("data_tables/animations/BossFireball/bossfireball_animation_clips.csv");
	std::vector<std::string> colId = clipsFire.GetColumn<std::string>("ID");
	std::vector<int> colFps = clipsFire.GetColumn<int>("FPS");
	std::vector<int> colLoop = clipsFire.GetColumn<int>("LOOP TYPE(0:Single, 1:Loop)");
	std::vector<std::string> colPath = clipsFire.GetColumn<std::string>("CLIP PATH");

	int totalclips = colId.size();

	for (int i = 0; i < totalclips; ++i)
	{
		AnimationClip clip;
		clip.id = colId[i];
		clip.fps = colFps[i];
		clip.loopType = (AnimationLoopTypes)colLoop[i];

		rapidcsv::Document frames(colPath[i]);
		std::vector<std::string> colTexure = frames.GetColumn<std::string>("TEXTURE PATH");
		std::vector<int> colL = frames.GetColumn<int>("L");
		std::vector<int> colT = frames.GetColumn<int>("T");
		std::vector<int> colW = frames.GetColumn<int>("W");
		std::vector<int> colH = frames.GetColumn<int>("H");

		int totalFrames = colTexure.size();
		for (int j = 0; j < totalFrames; ++j)
		{
			if (texMap.find(colTexure[j]) == texMap.end())
			{
				auto &ref = texMap[colTexure[j]];
				ref.loadFromFile(colTexure[j]);
			}
			clip.frames.push_back(AnimationFrame(texMap[colTexure[j]], IntRect(colL[j], colT[j], colW[j], colH[j])));
		}
		animation.AddClip(clip);
		animationSuperEffect.AddClip(clip);
	}
}

BossFire::~BossFire()
{
}

void BossFire::SetActive(bool active)
{
	isActive = active;
}

bool BossFire::IsActive()
{
	return isActive;
}

void BossFire::Shoot(Vector2f pos, Vector2f dir)
{
	animation.Play("fireball");

	SetActive(true);
	
	fireRect.setSize(Vector2f(80, 40));
	fireRect.setFillColor(Color(140, 72, 19, 70));

	fireRect.setPosition(position);

	Utils::SetOrigin(spriteFireBall, Pivots::LT);
	spriteFireBall.setScale(0.8f, 0.8f);


	distance = 0.f;
	position = pos;
	spriteFireBall.setPosition(pos);
	direction = Utils::Normalize(dir);
	float dgree = Utils::GetAngel(position, position + dir);
	spriteFireBall.setRotation(dgree);
	
	fireRect.setPosition(pos);
	fireRect.setRotation(dgree);
}

void BossFire::SuperShoot(Vector2f pos, Vector2f dir)
{
	animation.Play("fireball");
	animationSuperEffect.Play("supereffect");

	position = pos;

	SetActive(true);
	spriteSuperEffect.setPosition(position);

	position.x += 230;
	position.y += 180;

	fireRect.setSize(Vector2f(200, 100));
	fireRect.setFillColor(Color(140, 72, 19, 70));
	fireRect.setPosition(position);

	spriteFireBall.setScale(2.0f, 2.0f);

	distance = 0.f;

	spriteFireBall.setPosition(position);
	direction = Utils::Normalize(dir);
	float dgree = Utils::GetAngel(position, position + dir);
	spriteFireBall.setRotation(dgree);

	fireRect.setPosition(pos);
	fireRect.setRotation(dgree);
}

void BossFire::Stop()
{
	SetActive(false);

}

void BossFire::Update(float dt)
{
	animation.Update(dt);
	animationSuperEffect.Update(dt);

	position += direction * speed * dt;
	fireRect.setPosition(position);
	spriteFireBall.setPosition(position);

	distance += speed * dt;
	if (distance > DEFAULT_DISTANCE)
	{
		Stop();
	}

	fireRect.setPosition(position);
}

Sprite BossFire::GetSprite()
{
	return spriteFireBall;
}

Sprite BossFire::GetSuperEffectSprite()
{
	return spriteSuperEffect;
}

RectangleShape BossFire::GetRect()
{
	return fireRect;
}