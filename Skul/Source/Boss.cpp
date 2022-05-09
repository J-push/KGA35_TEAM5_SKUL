#include "Boss.h"

Boss::Boss()
{
}

void Boss::Init()
{
	bossPosition.x = 500;
	bossPosition.y = 500;

	// 피격판정 초기화
	bossRect.setSize(Vector2f(28, 60));
	bossRect.setScale(1.5f, 1.5f);
	bossRect.setOrigin(Vector2f(14, 0));
	bossRect.setFillColor(Color::Transparent);
	bossRect.setOutlineColor(Color::Red);
	bossRect.setOutlineThickness(2);


	spriteBoss.setScale(5.f, 5.f);
	spriteBoss.setOrigin(150, 100);
	spriteBoss.setPosition(bossPosition);
	animation.SetTarget(&spriteBoss);

	rapidcsv::Document clipsBoss("data_tables/animations/Boss/boss_animation_clips.csv");
	std::vector<std::string> colId = clipsBoss.GetColumn<std::string>("ID");
	std::vector<int> colFps = clipsBoss.GetColumn<int>("FPS");
	std::vector<int> colLoop = clipsBoss.GetColumn<int>("LOOP TYPE(0:Single, 1:Loop)");
	std::vector<std::string> colPath = clipsBoss.GetColumn<std::string>("CLIP PATH");

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
	}
	animation.Play("intro1");
}



void Boss::Update(float dt)
{
	animation.PlayQueue("intro2");
	animation.Update(dt);
	bossRect.setPosition(bossPosition);
}



void Boss::Draw(RenderWindow &window)
{
	window.draw(bossRect);
	window.draw(spriteBoss);

}
