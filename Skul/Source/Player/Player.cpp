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
#include <iostream>

/**********************************************************
* 설명 : 플레이어를 초기화한다.
***********************************************************/
void Player::Init()
{

	Player player;
	// 재휘 현재,최대체력 초기화
	maxPlayerHealth = START_PLAYER_HEALTH;
	currentPlayerHealth = START_PLAYER_HEALTH;
	playerAttackDamage = START_PLAYER_STR;
	playerPosition.x = 900.f;
	playerPosition.y = 250.f;


	playerSpeed = START_PLAYER_SPEED;
	isJump = false;
	isAttack = false;
	isDash = false;
	isSkill = false;

	SpritePlayer.setPosition(playerPosition);
	SpritePlayer.setOrigin(150, 100);
	SpritePlayer.setScale(PLAYER_SIZE, PLAYER_SIZE);
	animation.SetTarget(&SpritePlayer);
	rapidcsv::Document clips("data_tables/animations/Player/player_animation_clips.csv");

	std::vector<std::string> colId = clips.GetColumn<std::string>("ID");
	std::vector<int> colFps = clips.GetColumn<int>("FPS");
	std::vector<int> colLoop = clips.GetColumn<int>("LOOP TYPE(0:Single, 1:Loop)");
	std::vector<std::string> colPath = clips.GetColumn<std::string>("CLIP PATH");

	//View mainView(FloatRect(0, 0, resolution.x, resolution.y));
	//resolution.x = VideoMode::getDesktopMode().width;
	//resolution.y = VideoMode::getDesktopMode().height;

	//mainView.setCenter(player.GetPosition());

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
* 설명 : 플레이어의 키보드 입력값에 따른 동작을 구현한다.
***********************************************************/
void Player::UpdateInput(float dt)
{
	//오른쪽
	//if (InputManager::instance()->GetKeyDown(Keyboard::Right))
	//{
	//	currentAction = PlayerState::MOVE;
	//	isLeft = false;

	//	animation.Play("Walk");

	//	SpritePlayer.setScale(PLAYER_SIZE, PLAYER_SIZE);
	//	playerAttackRect.setScale(1.5f, 1.5f);
//}
////왼쪽
//if (InputManager::instance()->GetKeyDown(Keyboard::Left))
//{
//	currentAction = PlayerState::MOVE;
//	isLeft = true;

//	animation.Play("Walk");

//	SpritePlayer.setScale(LEFT_PLAYER_SIZE, PLAYER_SIZE);
//	playerAttackRect.setScale(-1.5f, 1.5f);
//}
////오른쪽 왼쪽 떼면
//if (InputManager::instance()->GetKeyUp(Keyboard::Right) ||
//	InputManager::instance()->GetKeyUp(Keyboard::Left))
//{
//	
//	currentAction = PlayerState::IDLE;

//	animation.Play("Idle");
//}

//if (InputManager::instance()->GetKeyDown(Keyboard::Z))
//{
//	currentAction = PlayerState::DASH;
//	isDash = true;

//	dashPosition.x = playerPosition.x;			
//	dashPosition.y = playerPosition.y;

//	animation.Play("Dash");

//	if (InputManager::instance()->GetKey(Keyboard::Right) || InputManager::instance()->GetKey(Keyboard::Left))
//	{
//		currentAction = PlayerState::MOVE;
//		animation.PlayQueue("Walk");
//	}
//}

////공격키
//if (InputManager::instance()->GetKeyDown(Keyboard::X))
//{
//	currentAction = PlayerState::ATTACK;
//	isAttack = true;

//	animation.Play("Attack1");
//	animation.PlayQueue("Idle");
//}
//


//if (InputManager::instance()->GetKeyDown(Keyboard::C))
//{
//	currentAction = PlayerState::JUMP;
//	isJump = true;
//	oldJumpPos.y = playerPosition.y;
//	animation.Play("Jump");
//	
//}

//if (InputManager::instance()->GetKeyDown(Keyboard::A))
//{
//	currentAction = PlayerState::SKILLATTACK;
//	isSkill = true;
//	if (isLeft)
//	{
//		skillPosition.x = playerPosition.x - 300.f;
//		skillPosition.y = playerPosition.y - 400.f;
//		spriteSkill.setScale(4.0f, 4.0f);
//	}
//	else if (!isLeft)
//	{
//		skillPosition.x = playerPosition.x + 300.f;
//		skillPosition.y = playerPosition.y - 400.f;
//		spriteSkill.setScale(-4.0f, 4.0f);
//	}

//	skillAnimation.Play("SoulBurn");
//	animation.Play("Skill1");
//	animation.PlayQueue("Idle");
//}

}

/**********************************************************
* 설명 : 플레이어를 업데이트한다.
***********************************************************/
void Player::Update(float dt, std::vector<TestRectangle*> rects)
{
	stateDt = dt;
	switch (currentAction)
	{
	case PlayerState::IDLE:
		break;
	case PlayerState::MOVE:
		Move();
		break;
	case PlayerState::ATTACK:
		Attack();
		break;
	case PlayerState::SKILLATTACK:
		break;
	case PlayerState::COMBOATTACK:
		break;
	case PlayerState::JUMP:
		Jump();
		break;
	case PlayerState::DOWN:
		break;
	case PlayerState::DASH:
		Dash();
		break;
	default:
		break;
	}

	if (isSkill)
	{
		SkillAttack();
	}

	std::cout << (int)currentAction << std::endl;
	//std::cout << jumpForce << std::endl;
	if (jumpForce < 0)
	{
		jumpForce = 0;
	}

	AnimationUpdate(dt);

	//충돌
	PlayerConllision(rects);

	//중력
	valocity += 980.f * dt;
	playerPosition.y += valocity * dt;

	SpritePlayer.setPosition(playerPosition);
	spriteSkill.setPosition(skillPosition.x, skillPosition.y - 50);
	playerRect.setPosition(playerPosition.x, playerPosition.y - 50);
	playerAttackRect.setPosition(playerPosition.x, playerPosition.y - 100);
	playerSkillRect.setPosition(skillPosition.x, skillPosition.y - 50);
	animation.Update(dt);
	skillAnimation.Update(dt);
}
/**********************************************************
* 설명 : 유한 상태 머신(FSM)
***********************************************************/
void Player::AnimationUpdate(float dt)
{
	switch (currentAction)
	{
	case PlayerState::IDLE:
		if (InputManager::instance()->GetKeyDown(Keyboard::Right))
		{
			isLeft = false;
			SetState(PlayerState::MOVE);
		}
		else if (InputManager::instance()->GetKeyDown(Keyboard::Left))
		{
			isLeft = true;
			SetState(PlayerState::MOVE);
		}
		else if (InputManager::instance()->GetKey(Keyboard::Right) || InputManager::instance()->GetKey(Keyboard::Left))
		{
			SetState(PlayerState::MOVE);
		}
		else if (InputManager::instance()->GetKeyDown(Keyboard::A))
		{
			SetState(PlayerState::SKILLATTACK);
		}
		else if (InputManager::instance()->GetKeyDown(Keyboard::Z))
		{
			SetState(PlayerState::DASH);
		}
		else if (InputManager::instance()->GetKeyDown(Keyboard::X))
		{
			SetState(PlayerState::ATTACK);
		}
		else if (InputManager::instance()->GetKeyDown(Keyboard::C))
		{
			SetState(PlayerState::JUMP);
		}
		break;

	case PlayerState::MOVE:
		if ((InputManager::instance()->GetKeyUp(Keyboard::Right) || InputManager::instance()->GetKeyUp(Keyboard::Left)))
		{
			SetState(PlayerState::IDLE);
		}
		else if (InputManager::instance()->GetKeyDown(Keyboard::A))
		{
			SetState(PlayerState::SKILLATTACK);
		}
		else if (InputManager::instance()->GetKeyDown(Keyboard::Z))
		{
			SetState(PlayerState::DASH);
		}
		else if (InputManager::instance()->GetKeyDown(Keyboard::X))
		{
			SetState(PlayerState::ATTACK);
		}
		else if (InputManager::instance()->GetKeyDown(Keyboard::C))
		{
			SetState(PlayerState::JUMP);
		}
		break;

	case PlayerState::ATTACK:
		if (InputManager::instance()->GetKey(Keyboard::Right))
		{
			isLeft = false;
			SetState(PlayerState::MOVE);
		}
		else if (InputManager::instance()->GetKey(Keyboard::Left))
		{
			isLeft = true;
			SetState(PlayerState::MOVE);
		}
		else if (InputManager::instance()->GetKeyDown(Keyboard::A))
		{
			SetState(PlayerState::SKILLATTACK);
		}
		else if (InputManager::instance()->GetKeyDown(Keyboard::Z))
		{
			SetState(PlayerState::DASH);
		}
		else if (InputManager::instance()->GetKeyDown(Keyboard::C))
		{
			SetState(PlayerState::JUMP);
		}
		break;

	case PlayerState::SKILLATTACK:
		if (InputManager::instance()->GetKeyDown(Keyboard::Right))
		{
			isLeft = false;
			SetState(PlayerState::MOVE);
		}
		else if (InputManager::instance()->GetKeyDown(Keyboard::Left))
		{
			isLeft = true;
			SetState(PlayerState::MOVE);
		}
		else if (InputManager::instance()->GetKeyDown(Keyboard::Z))
		{
			SetState(PlayerState::DASH);
		}
		break;

	case PlayerState::COMBOATTACK:
		break;

	case PlayerState::JUMP:
		if (InputManager::instance()->GetKeyDown(Keyboard::Right))
		{
			isLeft = false;
			SetState(PlayerState::MOVE);
		}
		else if (InputManager::instance()->GetKeyDown(Keyboard::Left))
		{
			isLeft = true;
			SetState(PlayerState::MOVE);
		}
		else if (InputManager::instance()->GetKey(Keyboard::Right) || InputManager::instance()->GetKey(Keyboard::Left))
		{
			SetState(PlayerState::MOVE);
		}
		else if (InputManager::instance()->GetKeyDown(Keyboard::X))
		{
			SetState(PlayerState::ATTACK);
		}
		else if (InputManager::instance()->GetKeyDown(Keyboard::Z))
		{
			SetState(PlayerState::DASH);
		}
		break;
	case PlayerState::DOWN:
		break;

	case PlayerState::DASH:
		if (InputManager::instance()->GetKeyDown(Keyboard::Right))
		{
			isLeft = false;
			SetState(PlayerState::MOVE);
		}
		else if (InputManager::instance()->GetKeyDown(Keyboard::Left))
		{
			isLeft = true;
			SetState(PlayerState::MOVE);
		}
		else if (InputManager::instance()->GetKeyDown(Keyboard::C))
		{
			SetState(PlayerState::JUMP);
		}
		else if (InputManager::instance()->GetKeyDown(Keyboard::X))
		{
			SetState(PlayerState::ATTACK);
		}
		break;

	default:
		break;
	}
}



/**********************************************************
* 설명 : 상태를 설정한다.
***********************************************************/
void Player::SetState(PlayerState newAction)
{
	PlayerState prevAction = currentAction;
	currentAction = newAction;

	switch (currentAction)
	{
	case PlayerState::IDLE:
		animation.Play("Idle");

		break;
	case PlayerState::MOVE:
		if (isLeft)
		{
			animation.Play("Walk");
			SpritePlayer.setScale(LEFT_PLAYER_SIZE, PLAYER_SIZE);
			playerAttackRect.setScale(-1.5f, 1.5f);
		}
		else
		{
			animation.Play("Walk");
			SpritePlayer.setScale(PLAYER_SIZE, PLAYER_SIZE);
			playerAttackRect.setScale(1.5f, 1.5f);
		}
		break;
	case PlayerState::ATTACK:
		animation.Play("Attack1");
		animation.OnComplete = std::bind(&Player::GetStateIdle, this);
		animation.PlayQueue("Idle");
		break;
	case PlayerState::SKILLATTACK:
		isSkill = true;
		tempPos = playerPosition;
		if (isLeft)
		{
			skillPosition.x = playerPosition.x - 300.f;
			skillPosition.y = playerPosition.y - 400.f;
			spriteSkill.setScale(4.0f, 4.0f);
		}
		else if (!isLeft)
		{
			skillPosition.x = playerPosition.x + 300.f;
			skillPosition.y = playerPosition.y - 400.f;
			spriteSkill.setScale(-4.0f, 4.0f);
		}
		skillAnimation.Play("SoulBurn");
		animation.Play("Skill1");
		
		break;
	case PlayerState::COMBOATTACK:
		break;
	case PlayerState::JUMP:
		isJump = true;
		isGround = false;
		oldJumpPos = playerPosition;
		animation.Play("Jump");
		break;
	case PlayerState::DOWN:
		break;
	case PlayerState::DASH:
		isDash = true;
		dashPosition = playerPosition;
		animation.Play("Dash");
		animation.PlayQueue("Idle");
		break;
	default:
		break;
	}
}


/**********************************************************
* 설명 : 플레이어의 이동 동작을 구현한다.
***********************************************************/
void Player::Move()
{
	float h = InputManager::GetAxisRaw(Axis::Horizontal);
	float v = InputManager::GetAxisRaw(Axis::Vertical);

	Vector2f dir(h, v);

	if (InputManager::instance()->GetKey(Keyboard::Right))
	{
		isLeft = false;
		playerPosition.x += dir.x * playerSpeed * stateDt;
	}
	else if (InputManager::instance()->GetKey(Keyboard::Left))
	{
		isLeft = true;
		playerPosition.x += dir.x * playerSpeed * stateDt;
	}
}
/**********************************************************
* 설명 : 플레이어의 공격 동작을 구현한다.
***********************************************************/
void Player::Attack()
{
	isAttack = true;
}

/**********************************************************
* 설명 : 플레이어의 스킬 공격 동작을 구현한다.
***********************************************************/
void Player::SkillAttack()
{
	isSkill = true;
	skillDown = 700.f;
	skillPosition.y += skillDown * stateDt;
	
	if (skillPosition.y > tempPos.y)
	{
		skillPosition.y = tempPos.y;
	}
	//스킬 이펙트 그리는게 끝나면
	//isSkill = false;
}

/**********************************************************
* 설명 : 플레이어의 공격 동작을 구현한다.
***********************************************************/
void Player::Dash()
{
	if (isDash)
	{
		if (isLeft == true)
		{
			if (playerPosition.x > dashPosition.x - 300.f)
			{
				playerPosition.x -= stateDt * playerSpeed * 6.f;
			}
			else
			{
				isDash = false;
			}
		}
		else if (isLeft == false)
		{

			if (playerPosition.x < dashPosition.x + 300.f)
			{
				playerPosition.x += stateDt * playerSpeed * 6.f;
			}
			else
			{
				isDash = false;
			}
		}
	}
	if (!isDash)
	{
		currentAction = PlayerState::IDLE;
	}
}

/**********************************************************
* 설명 : 플레이어의 점프 동작을 구현한다.
***********************************************************/
void Player::Jump()
{
	if (isJump == true)
	{
		jumpForce = 700.f;

		playerPosition.y -= jumpForce * stateDt;

		jumpForce -= valocity;
		//std::cout << "돼";
	}
	

}
/**********************************************************
* 설명 : 플레이어의 충돌을 정의한다.
***********************************************************/
void Player::PlayerConllision(std::vector<TestRectangle*> rects)
{
	for (auto v : rects)
	{
		if (playerRect.getGlobalBounds().intersects(v->GetRect()))
		{
			Pivots pivot = Utils::CollisionDir(v->GetRect(), playerRect.getGlobalBounds());

			switch (pivot)
			{
			case Pivots::LC:
				playerPosition.x += (v->GetRect().left + v->GetRect().width) - (playerRect.getGlobalBounds().left);
				InputManager::HorizontalInit();
				break;

			case Pivots::RC:
				playerPosition.x -= (playerRect.getGlobalBounds().left + playerRect.getGlobalBounds().width) - (v->GetRect().left);
				InputManager::HorizontalInit();
				break;

			case Pivots::CT:
				playerPosition.y += (v->GetRect().top + v->GetRect().height) - (playerRect.getGlobalBounds().top);
				InputManager::VerticalInit();
				break;

			case Pivots::CB:
				playerPosition.y -= (playerRect.getGlobalBounds().top + playerRect.getGlobalBounds().height) - (v->GetRect().top);
				isGround = true;
				valocity = -20;
				InputManager::VerticalInit();
				break;

			defalut:
				break;
			}
			playerRect.setPosition(playerPosition.x, playerPosition.y - 50);
		}
	}
}
/**********************************************************
* 설명 : 플레이어의 포지션을 들고 온다.
***********************************************************/
Vector2f Player::GetPosition()
{
	return playerPosition;
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
	
	window.draw(playerRect);
	if (currentAction == PlayerState::ATTACK)
	{
		window.draw(playerAttackRect);
	}

	if (isSkill)
	{
		window.draw(spriteSkill);
		window.draw(playerSkillRect);
	}
	

	//window.setView(mainView);
}

/**********************************************************
* 설명 : 플레이어의 최대 체력을 받아온다.
***********************************************************/
int Player::GetMaxPlayerHealth()
{
	return maxPlayerHealth;
}

/**********************************************************
* 설명 : 플레이어의 현재 체력을 받아온다.
***********************************************************/
int Player::GetCurrentPlayerHealth()
{
	return currentPlayerHealth;
}

void Player::JeaHit()
{
	if (currentPlayerHealth > 0)
	{
		currentPlayerHealth -= 10;
	}
}

Vector2f Player::GetPlayerPosition()
{
	return playerPosition;
}

FloatRect Player::GetPlayerRect()
{
	return playerRect.getGlobalBounds();
}

FloatRect Player::GetPlayerAttackRect()
{
	return playerAttackRect.getGlobalBounds();
}

FloatRect Player::GetPlayerSkiilRect()
{
	return playerSkillRect.getGlobalBounds();
}

int Player::GetPlayerDamage()
{

	return playerAttackDamage;
}

void Player::GetStateIdle()
{
	currentAction = PlayerState::IDLE;
}
