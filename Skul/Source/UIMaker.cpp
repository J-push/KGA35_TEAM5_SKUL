#include "UIMaker.h"

#include <iostream>

void UIMaker::Init()
{
	//mouseCursor.Init();

	// Title UI
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

	// Game UI
	spriteMainFrame.setTexture(*ResourceMgr::instance()->GetTexture("MAINFRAMETEX"));
	spriteMainFrame.setPosition(MAIN_FRAME_X, MAIN_FRAME_Y);
	spriteMainFrame.setScale(2.5, 2.5);

	spriteHpBar.setTexture(*ResourceMgr::instance()->GetTexture("HPBARTEX"));
	spriteHpBar.setPosition(HP_BAR_X, HP_BAR_Y); // +58, +110
	spriteHpBar.setScale(hp, 2.5);

	SpriteGrimReaperIcon.setTexture(*ResourceMgr::instance()->GetTexture("REAPERICONTEX"));
	SpriteGrimReaperIcon.setPosition(PORTRAIT_X, PORTRAIT_Y); // =20, 0
	SpriteGrimReaperIcon.setScale(2.0, 2.0);

	SpriteGrimReaperSkill.setTexture(*ResourceMgr::instance()->GetTexture("REAPERSKILLTEX"));
	SpriteGrimReaperSkill.setPosition(SKIIL1_X, SKIIL1_Y); // +142, +33
	SpriteGrimReaperSkill.setScale(2.8, 2.8);	
}


void UIMaker::Update(float dt)
{
	currentScene = mgr.GetCurrentScene();

	/*if (currentScene == 0)
	{
		animationGameStart.Update(dt);
		animationMapEdit.Update(dt);

		mouseCursor.Update(dt);

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
	}*/


	if (currentScene == Scenes::GAME)
	{
		animationGameStart.Stop();
		animationMapEdit.Stop();
		if (Keyboard::isKeyPressed(Keyboard::Num5) && hp > 0.f)
		{
			hp -= 0.01f;
			spriteHpBar.setScale(hp, 2.5);
		}
		if (Keyboard::isKeyPressed(Keyboard::Num6) && hp < 2.5f)
		{
			hp += 0.01f;
			spriteHpBar.setScale(hp, 2.5);
		}
	}
}


void UIMaker::Draw(sf::RenderWindow *window)
{
	/*if (currentScene == 0)
	{
		window->draw(spriteStart);
		window->draw(spriteMapEdit);

		
	}*/


	if (currentScene == Scenes::GAME)
	{
		window->draw(spriteMainFrame);
		window->draw(spriteHpBar);
		window->draw(SpriteGrimReaperIcon);
		window->draw(SpriteGrimReaperSkill);
	}

}


