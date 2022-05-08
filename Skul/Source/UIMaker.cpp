#include "UIMaker.h"
#include "Scene/SceneGame.h"

#include <iostream>


UIMaker::UIMaker() : hp(2.5f)
{
}


UIMaker::UIMaker(SceneGame *hp) : hpinfo(hp)
{
}

void UIMaker::Init()
{

	clickGameStart = false;
	mouseCursor.Init();

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
	spriteHpBar.setPosition(HP_BAR_X, HP_BAR_Y);
	spriteHpBar.setScale(hp, 2.5);
	spriteAbutton.setTexture(*ResourceMgr::instance()->GetTexture("ABUTTONTEX"));
	spriteAbutton.setPosition(A_X, A_Y);
	spriteAbutton.setScale(0.8, 0.8);
	
	spriteGrimReaperIcon1.setTexture(*ResourceMgr::instance()->GetTexture("REAPERICONTEX1"));
	spriteGrimReaperIcon1.setPosition(MINI_HEAD_X, MINI_HEAD_Y);
	spriteGrimReaperIcon1.setScale(1.0, 1.0);
	spriteGrimReaperIcon3.setTexture(*ResourceMgr::instance()->GetTexture("REAPERICONTEX3"));
	spriteGrimReaperIcon3.setPosition(PORTRAIT_X, PORTRAIT_Y);
	spriteGrimReaperIcon3.setScale(2.0, 2.0);
	spriteGrimReaperSkill.setTexture(*ResourceMgr::instance()->GetTexture("REAPERSKILLTEX"));
	spriteGrimReaperSkill.setPosition(SKIIL1_X, SKIIL1_Y);
	spriteGrimReaperSkill.setScale(2.8, 2.8);	

	spriteLittleBoneIcon1.setTexture(*ResourceMgr::instance()->GetTexture("BONEICONTEX1"));
	spriteLittleBoneIcon1.setPosition(MINI_HEAD_X, MINI_HEAD_Y);
	spriteLittleBoneIcon1.setScale(1.0, 1.0);
	spriteLittleBoneIcon3.setTexture(*ResourceMgr::instance()->GetTexture("BONEICONTEX3"));
	spriteLittleBoneIcon3.setPosition(PORTRAIT_X + 35, PORTRAIT_Y + 18);
	spriteLittleBoneIcon3.setScale(2.5, 2.5);

	textHp.setFont(*ResourceMgr::instance()->GetFont("MAINFONT"));
	textHp.setString("100 / 100");
	textHp.setCharacterSize(20);
	textHp.setPosition(246, 911);

	// Damage
	underAttackText.setFont(*ResourceMgr::instance()->GetFont("MAINFONT"));
	underAttackText.setString("-10");
	underAttackText.setCharacterSize(20);
	underAttackText.setPosition(6000,400);
	underAttackText.setFillColor(Color::Red);
	textSpeed = 5.0f;
	deleteDistance = 100.f;
	isActive = false;
}


void UIMaker::Update(float dt)
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
			clickGameStart = true;
		}
		else
		{
			clickGameStart = false;
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
	


	// Game UI

	/*stringstream HP;
	HP << hpinfo->GetMaxPlayerHealthReal() << " / ";
	textHp.setString(HP.str());*/



	/*if (InputManager::GetMouseButtonDown(Mouse::Left) && hp > 0.f)
	{
		hp *= 0.9f;
		spriteHpBar.setScale(hp, 2.5);
	}*/
	/*if (Keyboard::isKeyPressed(Keyboard::Num6) && hp < 2.5f)
	{
		hp += 0.01f;
		spriteHpBar.setScale(hp, 2.5);
	}*/

	if (Keyboard::isKeyPressed(Keyboard::Num1)) // ¸®Æ²º» ¸ÔÀ½
	{
		subHead = (int)Heads::LITTLEBORN;
	}

	if (InputManager::GetKeyDown(Keyboard::Space) && subHead != 0)
	{
		int change = 0;
		change = subHead;
		subHead = nowHead;
		nowHead = change;
	
	}
}




void UIMaker::DrawSceneTitle(sf::RenderWindow *window)
{

	window->draw(spriteStart);
	window->draw(spriteMapEdit);
	mouseCursor.Draw(window);
}

bool UIMaker::GetClickGameStart()
{
	return clickGameStart;
}

FloatRect UIMaker::GetMouseBound()
{
	return mouseCursor.GetGlobalBounds();
}

void UIMaker::SetHpbarText(int CurHp, int MaxHp)
{
	stringstream HP;
	HP << CurHp << " / " << MaxHp;
	textHp.setString(HP.str());
}

void UIMaker::SetHpbarSize(int CurHp, int MaxHp)
{
	hp = 2.5f * ((float)CurHp / MaxHp);
	spriteHpBar.setScale(hp, 2.5);
}



void UIMaker::DrawSceneGame(sf::RenderWindow *window)
{

	window->draw(spriteMainFrame);
	window->draw(spriteHpBar);
	

	switch (nowHead)
	{
	case 1:
		window->draw(spriteLittleBoneIcon3);
		break;
	case 2:
		window->draw(spriteGrimReaperIcon3);
		window->draw(spriteGrimReaperSkill);
		break;
	
	}
	switch (subHead)
	{
	case 1:
		window->draw(spriteLittleBoneIcon1);
		break;
	case 2:
		window->draw(spriteGrimReaperIcon1);
		break;	
	}

	window->draw(spriteAbutton);
	window->draw(textHp);
	window->draw(underAttackText);

	mouseCursor.Draw(window);
}

void UIMaker::UnderAttack(Vector2f position, float dt)
{
	position.y -= 100;
	underAttackText.setPosition(position);
	position.y -= textSpeed * dt;
}


