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
	mPlayerPosition.y = 250.f;
	

	mSpeed = START_PLAYER_SPEED;
	isJump = false;
	isAttack = false;
	isDash = false;
	SpritePlayer.setPosition(mPlayerPosition);
	SpritePlayer.setOrigin(150, 100);
	SpritePlayer.setScale(PLAYER_SIZE, PLAYER_SIZE);
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
	animation.Play("Idle");

	playerRect.setSize(Vector2f(28, 60));
	playerRect.setScale(1.5f, 1.5f);
	playerRect.setOrigin(Vector2f(14, 0));
	playerRect.setFillColor(Color::Transparent);
	playerRect.setOutlineColor(Color::Red);
	playerRect.setOutlineThickness(2);

	playerAttackRect.setSize(Vector2f(120, 114));
	playerAttackRect.setScale(1.5f, 1.5f);
	playerAttackRect.setOrigin(Vector2f(22, 0));
	playerAttackRect.setFillColor(Color::Transparent);
	playerAttackRect.setOutlineColor(Color::Yellow);
	playerAttackRect.setOutlineThickness(2);
	
	playerSkillRect.setSize(Vector2f(80, 80));
	playerSkillRect.setScale(4.f, 4.f);
	playerSkillRect.setOrigin(Vector2f(40, 40));
	playerSkillRect.setFillColor(Color::Transparent);
	playerSkillRect.setOutlineColor(Color::Black);
	playerSkillRect.setOutlineThickness(2);

}

/**********************************************************
* 설명 : 플레이어의 스킬을 초기화한다.
***********************************************************/
void Player::SkillInit()
{
	spriteSkill.setPosition(skillPosition);
	spriteSkill.setOrigin(50, 50);
	spriteSkill.setScale(4.f, 4.f);
	skillAnimation.SetTarget(&spriteSkill);
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

		skillAnimation.AddClip(skill);
	}
}
/**********************************************************
* 설명 : 플레이어의 이동 동작을 구현한다.
***********************************************************/
void Player::Move(float dt)
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
/**********************************************************
* 설명 : 플레이어의 공격 동작을 구현한다.
***********************************************************/
void Player::Attack()
{

}

/**********************************************************
* 설명 : 플레이어의 점프 동작을 구현한다.
***********************************************************/
void Player::Jump(float dt)
{
	if (isJump == true)
	{
		jumpForce = 600.f;
		mPlayerPosition.y -= jumpForce * dt;

		jumpForce -= graviteSpeed;
		
		if (jumpForce == 0)
		{
			graviteSpeed = 0;
		}

	}




	/*if (isJump == false)
	{
		action = PlayerStatus::IDLE;
	}*/
	//isJump = false;
	/*if ()
	{
		isJump = false;
	}*/
}

/**********************************************************
* 설명 : 플레이어의 키보드 입력값에 따른 동작을 구현한다.
***********************************************************/
void Player::UpdateInput(float dt)
{
	if (InputManager::instance()->GetKeyDown(Keyboard::Right))
	{
		action = PlayerStatus::MOVE;
		isLeft = false;
		animation.Play("Walk");
		SpritePlayer.setScale(PLAYER_SIZE, PLAYER_SIZE);
		playerAttackRect.setScale(1.5f, 1.5f);
	}
	//왼쪽
	if (InputManager::instance()->GetKeyDown(Keyboard::Left))
	{
		action = PlayerStatus::MOVE;
		isLeft = true;
		SpritePlayer.setScale(LEFT_PLAYER_SIZE, PLAYER_SIZE);
		playerAttackRect.setScale(-1.5f, 1.5f);
		animation.Play("Walk");
	}
	//오른쪽 왼쪽 떼면
	if (InputManager::instance()->GetKeyUp(Keyboard::Right) ||
		InputManager::instance()->GetKeyUp(Keyboard::Left))
	{
		action = PlayerStatus::IDLE;
		animation.Play("Idle");
	}

	//공격키
	if (InputManager::instance()->GetKeyDown(Keyboard::X))
	{
		action = PlayerStatus::ATTACK;
		animation.Play("Attack1");

		isAttack = true;

		animation.PlayQueue("Idle");
	}
	if (InputManager::instance()->GetKeyDown(Keyboard::Z))
	{
		action = PlayerStatus::DASH;
		dashPosition.x = mPlayerPosition.x;
		dashPosition.y = mPlayerPosition.y;
		isDash = true;

		animation.Play("Dash");

		if (InputManager::instance()->GetKey(Keyboard::Right) || InputManager::instance()->GetKey(Keyboard::Left))
		{
			action = PlayerStatus::MOVE;
			animation.PlayQueue("Walk");
		}
		/*else if (InputManager::instance()->GetKeyUp(Keyboard::Right) || InputManager::instance()->GetKeyUp(Keyboard::Left))
		{
			animation.Play("Idle");
		}*/
		action = PlayerStatus::IDLE;
		animation.PlayQueue("Idle");
		
	}

	if (InputManager::instance()->GetKeyDown(Keyboard::C))
	{
		action = PlayerStatus::JUMP;
		isJump = true;
		oldJumpPos.y = mPlayerPosition.y;
		animation.PlayQueue("Jump");
		
	}

	if (InputManager::instance()->GetKeyDown(Keyboard::A))
	{
		action = PlayerStatus::ATTACK;
		isSkill = true;
		if (isLeft)
		{
			skillPosition.x = mPlayerPosition.x - 300.f;
			skillPosition.y = mPlayerPosition.y - 400.f;
			spriteSkill.setScale(4.0f, 4.0f);
		}
		else if (!isLeft) 
		{
			skillPosition.x = mPlayerPosition.x + 300.f;
			skillPosition.y = mPlayerPosition.y - 400.f;
			spriteSkill.setScale(-4.0f, 4.0f);
		}
		
		skillAnimation.Play("SoulBurn");
		animation.Play("Skill1");
		animation.PlayQueue("Idle");
	}

}

/**********************************************************
* 설명 : 플레이어를 업데이트한다.
***********************************************************/
void Player::Update(float dt, std::vector<TestRectangle *> rects)
{
	UpdateInput(dt);
	attackDelay -= dt;
	switch (action)
	{
	case PlayerStatus::IDLE:
		//아무런 행동이 없다.
		isAttack = false;
		break;
	case PlayerStatus::MOVE:
		Move(dt);
		//이동한다.
		break;
	case PlayerStatus::ATTACK:
		Attack();
		attackDelay = ATTACK_DELAY;

		if (attackDelay < 0)
		{
			action = PlayerStatus::IDLE;
		}
		break;
	case PlayerStatus::COMBOATTACK:
		break;
	case PlayerStatus::JUMP:
	
			Jump(dt);

		
		break;
	case PlayerStatus::DOWN:
		break;
	case PlayerStatus::DASH:
		break;
	default:
		break;
	}

	
	if (isDash)
	{
		
		if (isLeft == true)
		{
			if (mPlayerPosition.x > dashPosition.x - 300.f)
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

			if (mPlayerPosition.x < dashPosition.x + 300.f)
			{
				mPlayerPosition.x += dt * mSpeed * 6.f;
			}
			else
			{
				isDash = false;
			}
		}
	}

	
	
	



	//충돌
	for (auto v : rects)
	{
		if (playerRect.getGlobalBounds().intersects(v->GetRect()))
		{
			Pivots pivot = Utils::CollisionDir(v->GetRect(), playerRect.getGlobalBounds());

			switch (pivot)
			{
			case Pivots::LC:
				mPlayerPosition.x += (v->GetRect().left + v->GetRect().width) - (playerRect.getGlobalBounds().left);
				InputManager::HorizontalInit();
				break;

			case Pivots::RC:
				mPlayerPosition.x -= (playerRect.getGlobalBounds().left + playerRect.getGlobalBounds().width) - (v->GetRect().left);
				InputManager::HorizontalInit();
				break;

			case Pivots::CT:
				mPlayerPosition.y += (v->GetRect().top + v->GetRect().height) - (playerRect.getGlobalBounds().top);
				InputManager::VerticalInit();
				break;

			case Pivots::CB:
				/*if (isJump)
				{
					isJump = false;
				}*/
				
				mPlayerPosition.y -= (playerRect.getGlobalBounds().top + playerRect.getGlobalBounds().height) - (v->GetRect().top);
				graviteSpeed = 0;
				InputManager::VerticalInit();
				val = 0;
				break;

			defalut:
				break;
			}
			playerRect.setPosition(mPlayerPosition.x, mPlayerPosition.y - 50);
		}
	}


	//중력
	graviteSpeed += 980.f * dt;
	mPlayerPosition.y += graviteSpeed * dt;

	//메테오처럼
	skillDown = 700.f;
	skillPosition.y += skillDown * dt;
	tempPos = mPlayerPosition;
	if (skillPosition.y > tempPos.y)

	{
		skillPosition.y = tempPos.y;
		isSkill = false;
	}
	



	SpritePlayer.setPosition(mPlayerPosition);
	spriteSkill.setPosition(skillPosition.x, skillPosition.y - 50);
	playerRect.setPosition(mPlayerPosition.x, mPlayerPosition.y - 50);
	playerAttackRect.setPosition(mPlayerPosition.x, mPlayerPosition.y - 100);
	playerSkillRect.setPosition(skillPosition.x, skillPosition.y - 50);
	animation.Update(dt);
	skillAnimation.Update(dt);

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
	window.draw(playerRect);
	
	if (action == PlayerStatus::ATTACK)
	{
		window.draw(playerAttackRect);
	}

	if (isJump == false && isSkill)
	{
		window.draw(playerSkillRect);
	}
	
	
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

void Player::JeaHit()
{	
	if (mCurrentPlayerHealth > 0)
	{			
		mCurrentPlayerHealth -= 10;		
	}
}

Vector2f Player::GetPlayerPosition()
{
	return mPlayerPosition;
}

