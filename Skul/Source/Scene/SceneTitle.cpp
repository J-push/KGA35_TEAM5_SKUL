#include "SceneTitle.h"
#include "../Manager/ResourceMgr.h"
#include "../../rapidcsv.h"


void SceneTitle::Init()
{
	/*test.setFont(*ResourceMgr::instance()->GetFont("MAINFONT"));
	test.setString("MAIN");
	test.setFillColor(Color::White);
	test.setCharacterSize(100);
	test.setPosition(0, 0);*/
	spriteTitle.setTexture(*ResourceMgr::instance()->GetTexture("TITLETEX"));
	spriteStart1.setTexture(*ResourceMgr::instance()->GetTexture("STARTTEX1"));
	spriteStart2.setTexture(*ResourceMgr::instance()->GetTexture("STARTTEX2"));
	//spriteStart1.setPosition(900, 700);
	//spriteStart2.setPosition(900, 700);

	//spriteStart.setTexture(*ResourceMgr::instance()->GetTexture("STARTTEX"));	

	spriteStart.setPosition(880, 700);
	//spriteStart.setOrigin(60, 60);
	spriteStart.setScale(-1.f, 1.f);
	animation.SetTarget(&spriteStart);

	rapidcsv::Document clips("data_tables/animations/title/title_animation_clips.csv");
	std::vector<std::string> colId = clips.GetColumn<std::string>("ID"); // 일반화인자를 받음
	std::vector<int> colFps = clips.GetColumn<int>("FPS");
	std::vector<int> colLoop = clips.GetColumn<int>("LOOP TYPE(0:Single, 1:Loop)");
	std::vector<std::string> colPath = clips.GetColumn<std::string>("CLIP PATH");

	int totalClips = colId.size();
	for (int i = 0; i < totalClips; ++i)
	{
		AnimationClip clip;
		clip.id = colId[i];
		clip.fps = colFps[i];
		clip.loopType = (AnimationLoopTypes)colLoop[i];

		std::string path = colPath[i]; // ??
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
	animation.Play("MAPTEX");
}

void SceneTitle::Release()
{

}

void SceneTitle::Start()
{

}

void SceneTitle::End()
{

}

void SceneTitle::Update(float dt)
{
	if (Keyboard::isKeyPressed(Keyboard::Return))
	{
		mgr.ChangeScene(Scenes::MENU);
	}
	if (Keyboard::isKeyPressed(Keyboard::Num0))
	{
		animation.Play("MAPTEX");
	}
}

void SceneTitle::Draw(sf::RenderWindow* window)
{
	//window->draw(spriteTitle);
	//window->draw(spriteStart);


	/*window->draw(spriteStart1);*/
}
