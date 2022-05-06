/******************************************************************************
* 작 성 자 : 임 병 록
* 작 성 일 : 2022-05-04
* 내    용 : Player의 동작을 구현한다.
* 수 정 일 :
*******************************************************************************/
/*include될 헤더*/
#include "Player.h"
#include "../Animation/rapidcsv.h"
#include "../Utils/Utils.h"

/**********************************************************
* 설명 : 플레이어를 초기화한다.
***********************************************************/
void Player::Init()
{
	Player player;


	// 재휘 현재,최대체력 초기화
	mMaxPlayerHealth = START_PLAYER_HEALTH;
	mCurrentPlayerHealth = START_PLAYER_HEALTH;
	mPlayerPosition.x = 900.f;
	mPlayerPosition.y = 750.f;

	mSpeed = START_PLAYER_SPEED;

	mPlayerAttacking = false;
	isDash = false;

	SpritePlayer.setPosition(mPlayerPosition);
	SpritePlayer.setOrigin(150, 100);
	SpritePlayer.setScale(Player_Size, Player_Size);
	animation.SetTarget(&SpritePlayer);
	rapidcsv::Document clips("data_tables/animations/Player/player_animation_clips.csv");
	std::vector<std::string> colId = clips.GetColumn<std::string>("ID");
	std::vector<int> colFps = clips.GetColumn<int>("FPS");
	std::vector<int> colLoop = clips.GetColumn<int>("LOOP TYPE(0:Single, 1:Loop)");
	std::vector<std::string> colPath = clips.GetColumn<std::string>("CLIP PATH");



	View mainView(FloatRect(0, 0, resolution.x, resolution.y));
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	mainView.setCenter(player.GetPosition());

	int totalClips = colId.size();
	for (int i = 0; i < totalClips; ++i)

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
				auto& ref = texMap[colTexure[j]];
				ref.loadFromFile(colTexure[j]);
			}
			clip.frames.push_back(AnimationFrame(texMap[colTexure[j]], IntRect(colL[j], colT[j], colW[j], colH[j])));
		}

		animation.AddClip(clip);
	}


	skillPosition.x = 200;
	skillPosition.y = 500;

	spriteSkill.setPosition(skillPosition);
	spriteSkill.setOrigin(50, 50);
	spriteSkill.setScale(2.f, 2.f);
	skillAni.SetTarget(&spriteSkill);
	rapidcsv::Document clips2("data_tables/animations/PlayerSkill/playerSkill_animation_clips.csv");
	std::vector<std::string> colId2 = clips2.GetColumn<std::string>("ID");
	std::vector<int> colFps2 = clips2.GetColumn<int>("FPS");
	std::vector<int> colLoop2 = clips2.GetColumn<int>("LOOP TYPE(0:Single, 1:Loop)");
	std::vector<std::string> colPath2 = clips2.GetColumn<std::string>("CLIP PATH");

	int totalClips2 = colId2.size();
	for (int i = 0; i < totalClips2; ++i)

	{
		AnimationClip skill;
		skill.id = colId2[i];
		skill.fps = colFps2[i];
		skill.loopType = (AnimationLoopTypes)colLoop2[i];

		rapidcsv::Document frames(colPath2[i]);
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
				auto& ref = texMap[colTexure[j]];
				ref.loadFromFile(colTexure[j]);
			}
			skill.frames.push_back(AnimationFrame(texMap[colTexure[j]], IntRect(colL[j], colT[j], colW[j], colH[j])));
		}

		skillAni.AddClip(skill);
	}

	animation.Play("Idle");
}
/**********************************************************
* 설명 : 플레이어의 스킬을 초기화한다.
***********************************************************/
void Player::SkillInit()
{
	/*skillPosition.x = 200;
	skillPosition.y = 500;

	spriteSkill.setPosition(skillPosition);
	spriteSkill.setOrigin(50, 50);
	spriteSkill.setScale(2.f, 2.f);
	skillAni.SetTarget(&spriteSkill);
	rapidcsv::Document clips("data_tables/animations/PlayerSkill/playerSkill_animation_clips.csv");
	std::vector<std::string> colId = clips.GetColumn<std::string>("ID");
	std::vector<int> colFps = clips.GetColumn<int>("FPS");
	std::vector<int> colLoop = clips.GetColumn<int>("LOOP TYPE(0:Single, 1:Loop)");
	std::vector<std::string> colPath = clips.GetColumn<std::string>("CLIP PATH");

	int totalClips = colId.size();
	for (int i = 0; i < totalClips; ++i)

	{
		AnimationClip skill;
		skill.id = colId[i];
		skill.fps = colFps[i];
		skill.loopType = (AnimationLoopTypes)colLoop[i];

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
				auto& ref = texMap[colTexure[j]];
				ref.loadFromFile(colTexure[j]);
			}
			skill.frames.push_back(AnimationFrame(texMap[colTexure[j]], IntRect(colL[j], colT[j], colW[j], colH[j])));
		}

		skillAni.AddClip(skill);
	}*/
	//skillAni.Play("SoulBurn");
}
/**********************************************************
* 설명 : 플레이어의 초기 생성 위치를 설정한다.
***********************************************************/
void Player::Spawn(IntRect arena, Vector2i res, int tileSize)
{

}
/**********************************************************
* 설명 : 플레이어의 키보드 입력값에 따른 동작을 구현한다.
***********************************************************/
void Player::UpdateInput()
{
	if (InputManager::instance()->GetKeyDown(Keyboard::Right))
	{
		isLeft = false;
		animation.Play("Walk");
		SpritePlayer.setScale(Player_Size, Player_Size);

	}
	if (InputManager::instance()->GetKeyDown(Keyboard::Left))
	{
		isLeft = true;
		SpritePlayer.setScale(Left_Player_Size, Player_Size);
		animation.Play("Walk");

	}
	if (InputManager::instance()->GetKeyUp(Keyboard::Right) ||
		InputManager::instance()->GetKeyUp(Keyboard::Left))
	{
		animation.Play("Idle");
		animation.PlayQueue("Idle");
	}

	if (InputManager::instance()->GetKeyDown(Keyboard::X))
	{

		animation.Play("Attack1");
		mPlayerAttacking = true;

		if (mPlayerAttacking == true && InputManager::instance()->GetKeyDown(Keyboard::X))
		{
			animation.PlayQueue("Attack2");

			if (mPlayerAttacking == true && InputManager::instance()->GetKeyDown(Keyboard::X))
			{
				animation.PlayQueue("Attack3");
				animation.PlayQueue("Idle");
				mPlayerAttacking = false;
			}
			animation.PlayQueue("Idle");
			mPlayerAttacking = false;
		}
		animation.PlayQueue("Idle");
		mPlayerAttacking = false;
	}
	if (InputManager::instance()->GetKeyDown(Keyboard::Z))
	{
		dirDash.x = mPlayerPosition.x;
		dirDash.y = mPlayerPosition.y;
		isDash = true;
		animation.Play("Dash");

		if (InputManager::instance()->GetKey(Keyboard::Right) || InputManager::instance()->GetKey(Keyboard::Left))
		{
			animation.PlayQueue("Walk");
		}
		else if (InputManager::instance()->GetKeyUp(Keyboard::Right) || InputManager::instance()->GetKeyUp(Keyboard::Left))
		{
			animation.Play("Idle");
		}
		animation.PlayQueue("Idle");
	}

	if (InputManager::instance()->GetKeyDown(Keyboard::C))
	{
		animation.PlayQueue("Jump");
	}

	if (InputManager::instance()->GetKeyDown(Keyboard::A))
	{
		skillAni.Play("SoulBurn");
		animation.PlayQueue("Skill1");
		
		animation.PlayQueue("Idle");
	}

}
/**********************************************************
* 설명 : 플레이어를 업데이트한다.
***********************************************************/
void Player::Update(float dt)
{
	UpdateInput();
	
	if (isDash)
	{
		if (isDash)
		{
			if (isLeft == true)
			{
				if (mPlayerPosition.x > dirDash.x - 300.f)
				{
					mPlayerPosition.x -= dt * mSpeed * 6.f;
				}
				else
				{
					isDash = false;
				}
			}
			else if (isLeft == false)
			{

				if (mPlayerPosition.x < dirDash.x + 300.f)
				{
					mPlayerPosition.x += dt * mSpeed * 6.f;
				}
				else
				{
					isDash = false;
				}
			}

		}
	}
	else
	{
		if (InputManager::instance()->GetKey(Keyboard::Right))
		{
			mPlayerPosition.x += mSpeed * dt;
		}
		if (InputManager::instance()->GetKey(Keyboard::Left))
		{
			mPlayerPosition.x -= mSpeed * dt;
		}
	}
  
	/*if (dir.x == 0.f && mLastDir != dir)
	{
		animation.Play("Idle");
		
	}
	if (dir.x > 0.f && mLastDir != dir)
	{
		animation.Play("RightWalk");
		mPlayerPosition.x += dir.x * mSpeed * dt;
	}
	if (dir.x < 0.f && mLastDir != dir)
	{
		animation.Play("LeftWalk");
		mPlayerPosition.x -= dir.x * mSpeed * dt;
	}*/

	//val += 980.f * dt;
	//mPlayerPosition.y += val * dt;
	SpritePlayer.setPosition(mPlayerPosition);

	animation.Update(dt);
}

Vector2f Player::GetPosition()
{
	return mPlayerPosition;
}

/**********************************************************
* 설명 : 플레이어의 sprite를 들고 온다.
***********************************************************/
Sprite Player::GetSprite()
{
	return SpritePlayer;
}

/**********************************************************
* 설명 : 플레이어 인식 범위 함수
***********************************************************/
FloatRect Player::GetGlobalBound()
{
	return SpritePlayer.getGlobalBounds();
}
/**********************************************************
* 설명 : 플레이어를 그린다.
***********************************************************/
void Player::Draw(RenderWindow& window)
{
	window.draw(SpritePlayer);
	window.draw(spriteSkill);
	//window.setView(mainView);
}

/**********************************************************
* 설명 : 플레이어의 최대 체력을 받아온다.
***********************************************************/
int Player::GetMaxPlayerHealth()
{
	return mMaxPlayerHealth;
}

/**********************************************************
* 설명 : 플레이어의 현재 체력을 받아온다.
***********************************************************/
int Player::GetCurrentPlayerHealth()
{
	return mCurrentPlayerHealth;
}
