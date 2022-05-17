#include "BossSuper.h"

BossSuper::BossSuper()
{
	position.x = 150;
	position.y = 150;


	spriteSuper.setScale(2.5f, 2.5f);
	spriteSuper.setPosition(Vector2f(position));
	animationSuper.SetTarget(&spriteSuper);

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
		animationSuper.AddClip(clip);
		animationSuperEffect.AddClip(clip);
	}
	animationSuper.Play("fireball");
	animationSuperEffect.Play("supereffect");
}

BossSuper::~BossSuper()
{
}


void BossSuper::Shoot(Vector2f pos, Vector2f dir)
{
	distance = 0.f;
	position = pos;
	spriteSuper.setPosition(pos);
	direction = Utils::Normalize(dir);
	float dgree = Utils::GetAngel(position, position + dir);
	spriteSuper.setRotation(dgree);

}

void BossSuper::Update(float dt)
{
	animationSuper.Update(dt);
	animationSuperEffect.Update(dt);

	position += direction * speed * dt;
	spriteSuper.setPosition(position);

	distance += speed * dt;
	/*if (distance > DEFAULT_DISTANCE)
	{
		animationSuper.Stop();
	}*/



}

Sprite BossSuper::GetSprite()
{
	return spriteSuper;
}

Sprite BossSuper::GetEffectSprite()
{
	return spriteSuperEffect;
}
