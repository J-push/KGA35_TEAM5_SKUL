/******************************************************************************
* 작 성 자 : 김 재 휘
* 작 성 일 : 2022-05-03
* 내    용 : 게임의 Tilte정보를 담당한다.
* 수 정 일 : 
*******************************************************************************/
/*include될 헤더*/
#include "SceneTitle.h"
#include "../Manager/ResourceMgr.h"
//#include "../Animation/rapidcsv.h" // 애니컨트롤러에 추가함 지워도댐
#include <iostream>
/**********************************************************
* 설명 : SceneTitle을 초기화한다.
***********************************************************/
void SceneTitle::Init()
{
	spriteTitle.setTexture(*ResourceMgr::instance()->GetTexture("TITLETEX"));

	shapeGameStart.setPosition(880, 700);
	shapeGameStart.setSize(Vector2f(158, 39));
	spriteStart.setPosition(880, 700);
	animationGameStart.SetTarget(&spriteStart);

	shapeMapEdit.setPosition(880, 750);
	shapeMapEdit.setSize(Vector2f(153, 39));
	spriteMapEdit.setPosition(880, 750);
	animationMapEdit.SetTarget(&spriteMapEdit);


	rapidcsv::Document clips("data_tables/animations/title/title_animation_clips.csv");
	std::vector<std::string> colId = clips.GetColumn<std::string>("ID");
	std::vector<int> colFps = clips.GetColumn<int>("FPS");
	std::vector<int> colLoop = clips.GetColumn<int>("LOOP TYPE(0:Single, 1:Loop)");
	std::vector<std::string> colPath = clips.GetColumn<std::string>("CLIP PATH");

	int totalclips = colId.size();
	for (int i = 0; i < totalclips; ++i)
	{
		AnimationClip clip;
		clip.id = colId[i];
		clip.fps = colFps[i];
		clip.loopType = (AnimationLoopTypes)colLoop[i];

		std::string path = colPath[i]; // ??
		rapidcsv::Document frames(colPath[i]);
		std::vector<std::string> 
			colTexure = frames.GetColumn<std::string>("TEXTURE PATH");
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

		animationGameStart.AddClip(clip);
		animationMapEdit.AddClip(clip);

	}
	animationGameStart.Play("STARTTEX");
	animationMapEdit.Play("MAPTEX");

	mouseCursor.Init();
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
/**********************************************************
* 설명 : SceneTitle을 업데이트한다.
***********************************************************/
void SceneTitle::Update(float dt)
{
	mouseCursor.Update(dt);
	animationGameStart.Update(dt);
	animationMapEdit.Update(dt);

	

	FloatRect mouseBound = mouseCursor.GetGlobalBounds();
	bool checkGameStart = mouseBound.intersects(shapeGameStart.getGlobalBounds());
	bool checkMapEdit = mouseBound.intersects(shapeMapEdit.getGlobalBounds());

	if (checkGameStart)
	{
		animationGameStart.Play("STARTMOUSETEX");
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			mgr.ChangeScene(Scenes::GAME);
		}
	}
	else
	{
		animationGameStart.Play("STARTTEX");
	}
	if (checkMapEdit)
	{
		animationMapEdit.Play("MAPMOUSETEX");
	}
	else
	{
		animationMapEdit.Play("MAPTEX");
	}
	

	
	if (Keyboard::isKeyPressed(Keyboard::Return))
	{
		mgr.ChangeScene(Scenes::GAME);
	}

}

/**********************************************************
* 설명 : SceneTitle을 그린다.
***********************************************************/
void SceneTitle::Draw(sf::RenderWindow* window)
{
	window->draw(spriteTitle);

	window->draw(spriteStart);
	window->draw(spriteMapEdit);
	
	mouseCursor.Draw(window);

}

