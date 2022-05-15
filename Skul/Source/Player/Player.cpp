/******************************************************************************
* 작 성 자 : 임 병 록
* 작 성 일 : 2022-05-04
* 내    용 : Player의 동작을 구현한다.
* 수 정 일 :
*******************************************************************************/
/*include될 헤더*/
#include "Player.h"
#include "../Animation/rapidcsv.h"
#include "../Manager/ResourceMgr.h"
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
	playerSpeed = START_PLAYER_SPEED;
	jumpForce = 0.f;


	playerPosition.x = 600.f;
	playerPosition.y = 500.f;


	isAlive = true;
	isGround = false;
	// 현섭 공격 맞는 시간 추가
	hitDelay = 1.f;

	playerSpeed = START_PLAYER_SPEED;
	isJump = false;
	isAttack = false;
	isSkill = false;
	isDash = false;
	isSkulChange = true;

	SpritePlayer.setPosition(playerPosition);
	SpritePlayer.setOrigin(70, 62);
	SpritePlayer.setScale(2.5f, 2.5f);
	animation.SetTarget(&SpritePlayer);
	rapidcsv::Document clips("data_tables/animations/Player/player_animation_clips.csv");

	std::vector<std::string> colId = clips.GetColumn<std::string>("ID");
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

	animation.Play("L_Idle");
	currentAction = PlayerState::IDLE;

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

	attack.setBuffer(*ResourceMgr::instance()->GetSoundBuffer("PLAYERATTACKSOUND"));

	change.setBuffer(*ResourceMgr::instance()->GetSoundBuffer("PLAYERCHANGESOUND"));

	dash.setBuffer(*ResourceMgr::instance()->GetSoundBuffer("PLAYERDASHSOUND"));

	jump.setBuffer(*ResourceMgr::instance()->GetSoundBuffer("PLAYERJUMPSOUND"));

	death.setBuffer(*ResourceMgr::instance()->GetSoundBuffer("PLAYERDEATHSOUND"));
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
* 설명 : 플레이어의 스킬을 초기화한다.
***********************************************************/
void Player::ChangeEffectInit()
{
	
	spriteChangeEffect.setPosition(changeEffectPosition);
	spriteChangeEffect.setOrigin(50, 50);
	spriteChangeEffect.setScale(4.f, 4.f);
	changeEffectAnimation.SetTarget(&spriteChangeEffect);
	rapidcsv::Document clips("data_tables/animations/PlayerSkill/playerSkill_animation_clips.csv");
	std::vector<std::string> colId = clips.GetColumn<std::string>("ID");
	std::vector<int> colFps = clips.GetColumn<int>("FPS");
	std::vector<int> colLoop = clips.GetColumn<int>("LOOP TYPE(0:Single, 1:Loop)");
	std::vector<std::string> colPath = clips.GetColumn<std::string>("CLIP PATH");

	int totalClips = colId.size();
	for (int i = 0; i < totalClips; ++i)
	{
		AnimationClip effect;
		effect.id = colId[i];
		effect.fps = colFps[i];
		effect.loopType = (AnimationLoopTypes)colLoop[i];

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
			effect.frames.push_back(AnimationFrame(texMap[colTexure[j]], IntRect(colL[j], colT[j], colW[j], colH[j])));
		}

		changeEffectAnimation.AddClip(effect);
	}
}

/**********************************************************
* 설명 : 플레이어를 업데이트한다.
***********************************************************/
void Player::Update(float dt, std::vector<ColliderRect*> rects)
{
	stateDt = dt;
	Move();
  
	//살음
	if (isAlive == true)
	{
		if (isGround == true && isJump == false)
		{
			if (InputManager::instance()->GetKeyDown(Keyboard::C))
			{
				isJump = true;
				isGround = false;
			}
		}
		if (isAttack == false && isSkill == false)
		{
			if (InputManager::instance()->GetKeyDown(Keyboard::X))
			{
				isAttack = true;
			}
			else if (InputManager::instance()->GetKeyDown(Keyboard::A))
			{
				isSkill = true;
			}
		}
		//공격
		if (isAttack == true)
		{
			Attack();
		}
		//스킬
		else if (isSkill == true)
		{
			SkillAttack();
		}
		//이동

		if (isJump == false)
		{
			//중력
			gravity += GRAVITY_POWER * dt;
			if (gravity > 1000.f)
			{
				gravity = 1000.f;
			}
		}
		else if (isJump == true)
		{

			Jump();
		}
		playerPosition.y += gravity * dt;
		
		//점프
	
	
		if (currentAction == PlayerState::DASH)
		{
			Dash();
		}
	}
	//죽음
	else if(isAlive == false)
	{
		isAttack = false;
		isJump = false;
		isSkill = false;
	}

	//std::cout << jumpForce << std::endl;


	AnimationUpdate(dt);

	//충돌
	PlayerConllision(rects);



	SpritePlayer.setPosition(playerPosition);
	spriteSkill.setPosition(skillPosition.x, skillPosition.y - 50);
	playerRect.setPosition(playerPosition.x, playerPosition.y - 50);
	changeEffectPosition.x = playerPosition.x - 850;
	changeEffectPosition.y = playerPosition.y - 420;
	spriteChangeEffect.setPosition(changeEffectPosition);

	if (isAttack == true)
	{
		playerAttackRect.setPosition(playerPosition.x, playerPosition.y - 100);
	}
	if (isSkill == true)
	{
		playerSkillRect.setPosition(skillPosition.x, skillPosition.y - 50);
	}
	
	animation.Update(dt);
	skillAnimation.Update(dt);
	changeEffectAnimation.Update(dt);

}
/**********************************************************
* 설명 : 유한 상태 머신(FSM)
***********************************************************/
void Player::AnimationUpdate(float dt)
{
	switch (currentAction)
	{
	case PlayerState::IDLE:

		if (InputManager::instance()->GetKeyDown(Keyboard::Right))				//우
		{
			isLeft = false;
			SetState(PlayerState::MOVE);
		}
		if (InputManager::instance()->GetKeyDown(Keyboard::Left))			//좌
		{
			isLeft = true;
			SetState(PlayerState::MOVE);
		}
		if (InputManager::instance()->GetKey(Keyboard::Right) || InputManager::instance()->GetKey(Keyboard::Left)) //지속
		{
			SetState(PlayerState::MOVE);
		}
		if (InputManager::instance()->GetKeyDown(Keyboard::A))				//공격
		{
			SetState(PlayerState::SKILLATTACK);
		}
		if (InputManager::instance()->GetKeyDown(Keyboard::Z))				//대쉬
		{
			SetState(PlayerState::DASH);
		}
		if (InputManager::instance()->GetKeyDown(Keyboard::X))				//공격
		{
			SetState(PlayerState::ATTACK);
		}
		if (InputManager::instance()->GetKeyDown(Keyboard::C))
		{
			SetState(PlayerState::JUMP);
		}
		if (InputManager::instance()->GetKeyDown(Keyboard::Space))
		{
			change.play();
			if (isSkulChange)
			{
				isSkulChange = false;
				isChangeEffect = true;
			}
			else
			{
				isSkulChange = true;
				isChangeEffect = false;
			}
			SetState(PlayerState::IDLE);
		}
		if (currentPlayerHealth <= 0)
		{
			SetState(PlayerState::DEAD);
		}
		break;

	case PlayerState::MOVE:
		if ((InputManager::instance()->GetKeyUp(Keyboard::Right) || InputManager::instance()->GetKeyUp(Keyboard::Left)))
		{
			isMoving = false;
			SetState(PlayerState::IDLE);
		}
		if (InputManager::instance()->GetKeyDown(Keyboard::A))
		{
			SetState(PlayerState::SKILLATTACK);
		}
		if (InputManager::instance()->GetKeyDown(Keyboard::Z))
		{
			SetState(PlayerState::DASH);
		}
		if (InputManager::instance()->GetKeyDown(Keyboard::X))
		{
			SetState(PlayerState::ATTACK);
		}
		if (InputManager::instance()->GetKeyDown(Keyboard::C))
		{
			SetState(PlayerState::JUMP);
		}
		if (currentPlayerHealth <= 0)
		{
			SetState(PlayerState::DEAD);
		}
		break;

	case PlayerState::ATTACK:
		if (InputManager::instance()->GetKeyDown(Keyboard::Z))
		{
			isAttack = false;
			SetState(PlayerState::DASH);
		}
		if (InputManager::instance()->GetKeyDown(Keyboard::C))
		{
			isAttack = false;
			SetState(PlayerState::JUMP);
		}
		if (currentPlayerHealth <= 0)
		{
			SetState(PlayerState::DEAD);
		}
		break;
		
	case PlayerState::SKILLATTACK:
		if (InputManager::instance()->GetKeyDown(Keyboard::Right))
		{
			isLeft = false;
			SetState(PlayerState::MOVE);
		}
		if (InputManager::instance()->GetKeyDown(Keyboard::Left))
		{
			isLeft = true;
			SetState(PlayerState::MOVE);
		}
		if (InputManager::instance()->GetKeyDown(Keyboard::Z))
		{
			SetState(PlayerState::DASH);
		}
		if (InputManager::instance()->GetKeyDown(Keyboard::C))
		{
			SetState(PlayerState::JUMP);
		}
		if (currentPlayerHealth <= 0)
		{
			SetState(PlayerState::DEAD);
		}
		break;

	case PlayerState::JUMP:
		if (InputManager::instance()->GetKeyDown(Keyboard::X))
		{
			SetState(PlayerState::ATTACK);
		}
		if (InputManager::instance()->GetKeyDown(Keyboard::Z))
		{
			SetState(PlayerState::DASH);
		}
		if (isJump && InputManager::instance()->GetKeyDown(Keyboard::Right))
		{
			isLeft = false;
			SetState(PlayerState::MOVE);
		}
		if (isJump && InputManager::instance()->GetKeyDown(Keyboard::Left))
		{
			isLeft = true;
			SetState(PlayerState::MOVE);
		}
		if (currentPlayerHealth <= 0)
		{
			SetState(PlayerState::DEAD);
		}
		break;
	case PlayerState::DOWN:
		break;

	case PlayerState::DASH:
	
		if (InputManager::instance()->GetKeyDown(Keyboard::C))
		{
			SetState(PlayerState::JUMP);
		}
		if (InputManager::instance()->GetKeyDown(Keyboard::X))
		{
			SetState(PlayerState::ATTACK);
		}
		if (InputManager::instance()->GetKeyDown(Keyboard::Right))
		{
			isLeft = false;
			SetState(PlayerState::MOVE);
		}
		if (InputManager::instance()->GetKeyDown(Keyboard::Left))
		{
			isLeft = true;
			SetState(PlayerState::MOVE);
		}
		if (currentPlayerHealth <= 0)
		{
			SetState(PlayerState::DEAD);
		}
		break;
	case PlayerState::DEAD:
	default:
		break;
	}
}

/**********************************************************
* 설명 : 상태를 설정한다. 		HyeonSeopSwordManHit(swordMan);
***********************************************************/
void Player::SetState(PlayerState newAction)
{
	PlayerState prevAction = currentAction;
	currentAction = newAction;

	switch (currentAction)
	{
	case PlayerState::IDLE:
		isAttack = false;
		animation.OnComplete = std::bind(&Player::ChangeSkul, this);
		break;

	case PlayerState::MOVE:
		if (isSkulChange && isLeft)
		{
			animation.Play("L_Walk");
			SpritePlayer.setScale(-2.5f, 2.5f);
			playerAttackRect.setScale(-1.5f, 1.5f);
		}
		else if (isSkulChange && !isLeft)
		{
			animation.Play("L_Walk");
			SpritePlayer.setScale(2.5f, 2.5f);
			playerAttackRect.setScale(1.5f, 1.5f);

		}
		else if (!isSkulChange && isLeft)
		{
			animation.Play("Walk");
			SpritePlayer.setScale(LEFT_PLAYER_SIZE, PLAYER_SIZE);
			playerAttackRect.setScale(-1.5f, 1.5f);
		}
		else if (!isSkulChange && !isLeft)
		{
			animation.Play("Walk");
			SpritePlayer.setScale(PLAYER_SIZE, PLAYER_SIZE);
			playerAttackRect.setScale(1.5f, 1.5f);

		}
		break;

	case PlayerState::ATTACK:
		isAttack = true;
		attack.play();
		if (isSkulChange)
		{
			animation.Play("L_Attack");
			animation.OnComplete = std::bind(&Player::GetStateIdle, this);
			animation.PlayQueue("L_Idle");
		}
		else
		{
			animation.Play("Attack1");
			animation.OnComplete = std::bind(&Player::GetStateIdle, this);
			animation.PlayQueue("Idle");
		}
		break;

	case PlayerState::SKILLATTACK:
		isSkill = true;
		tempPos = playerPosition;
		if (isSkulChange)
		{

		}
		else
		{
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
			animation.OnComplete = std::bind(&Player::GetStateIdle, this);
			skillAnimation.OnComplete = std::bind(&Player::SkillDelete, this);
			animation.PlayQueue("Idle");
		}
		break;

	case PlayerState::JUMP:
		jump.play();
		isJump = true;
		//oldJumpPos = playerPosition;
		if (isSkulChange)
		{
			animation.Play("L_Jump");
		}
		else
		{
			animation.Play("Jump");
		}
		break;

	/*case PlayerState::DOWN:
		animation.Play("Down");
		animation.PlayQueue("Idle");
		break;*/

	case PlayerState::DASH:
		dash.play();
		isDash = true;
		dashPosition = playerPosition;
		dashDelay = DASH_COOLTIME;
		if (isSkulChange)
		{
			animation.Play("L_Dash");
			animation.OnComplete = std::bind(&Player::GetStateIdle, this);
			animation.PlayQueue("L_Idle");
			
		}
		else
		{
			animation.Play("Dash");
			animation.OnComplete = std::bind(&Player::GetStateIdle, this);
			animation.PlayQueue("Idle");
		}
		break;

	case PlayerState::DEAD:
      
		if (isSkulChange)
		{
			animation.Play("L_Dead");
		}
		else
		{
			animation.Play("Dead");
		}
		animation.OnComplete = std::bind(&Player::AliveToDead, this);
		death.play();

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
	Utils::Normalize(dir);
	if (InputManager::instance()->GetKey(Keyboard::Right))
	{
		isLeft = false;
		//playerPosition.x += dir.x * playerSpeed * stateDt;
	}
	else if (InputManager::instance()->GetKey(Keyboard::Left))
	{
		isLeft = true;
		//playerPosition.x += dir.x * playerSpeed * stateDt;
	}
	playerPosition.x += dir.x * playerSpeed * stateDt;
}
/**********************************************************
* 설명 : 플레이어의 공격 동작을 구현한다.
***********************************************************/
void Player::Attack()
{
	isAttack = true;
	attackAlive -= stateDt;
	if (attackAlive < 0.f)
	{
		attackAlive = 0.5f;
		playerAttackRect.setPosition(0, 0);
		currentAction = PlayerState::IDLE;
		isAttack = false;
	}
}

/**********************************************************
* 설명 : 플레이어의 스킬 공격 동작을 구현한다.
***********************************************************/
void Player::SkillAttack()
{
	skillDown = 700.f;
	skillPosition.y += skillDown * stateDt;
	skillAlive -= stateDt;
	if (skillPosition.y > tempPos.y)
	{
		skillPosition.y = tempPos.y;
	}
	if (skillAlive < 0.f)
	{
		isSkill = false;
		skillAlive = 2.5f;
		skillPosition.x = 0.f;
		skillPosition.y = 0.f;
	}
}
/**********************************************************
* 설명 : 플레이어의 공격 동작을 구현한다.
***********************************************************/
void Player::Dash()
{
	if (isDash)
	{
		isJump = false;
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
	isGround = false;



	jumpForce -= GRAVITY_POWER * stateDt;
	playerPosition.y -= jumpForce * stateDt;

	if (jumpForce <= 0.f)
	{
		isJump = false;
		isDown = true;
		jumpForce = 800.f;

		currentAction = PlayerState::IDLE;
	}
}

/**********************************************************
* 설명 : 플레이어의 충돌을 정의한다.
***********************************************************/
void Player::PlayerConllision(std::vector<ColliderRect*> rects)
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
				gravity = -20;
				InputManager::VerticalInit();
				isGround = true;
				break;
			defalut:
				break;
			}
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
	//window.setView(*mainView);
	if (isAlive)
	{
		window.draw(SpritePlayer);

		window.draw(playerRect);
	}
	
	if (isAttack && currentAction == PlayerState::ATTACK)
	{
		window.draw(playerAttackRect);
	}

	if (isSkill && !isSkulChange)
	{
		window.draw(spriteSkill);
		window.draw(playerSkillRect);
	}
	if (isChangeEffect)
	{
		window.draw(spriteChangeEffect);
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

void Player::Hit(int damage)
{
	if (currentPlayerHealth > 0)
	{
		currentPlayerHealth -= damage;
	}
	if (currentPlayerHealth < 0)
	{
		currentPlayerHealth = 0;
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

bool Player::GetIsAttack()
{
	return isAttack;
}

bool Player::GetIsSkill()
{
	return isSkill;
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

void Player::ChangeSkul()
{
	if (isSkulChange)
	{
		if (isLeft)
		{
			SpritePlayer.setScale(-2.5f, 2.5f);
			SpritePlayer.setOrigin(70, 62);
			animation.Play("L_Idle");
		}
		else
		{
			SpritePlayer.setScale(2.5f, 2.5f);
			SpritePlayer.setOrigin(70, 62);
			animation.Play("L_Idle");
		}
	}
	else
	{
		if (isLeft)
		{
			SpritePlayer.setScale(-1.5f, 1.5f);
			SpritePlayer.setOrigin(150, 100);
			animation.Play("Idle");

			//changeEffectPosition = playerPosition;
			changeEffectAnimation.Play("ChangeEffect");
			changeEffectAnimation.OnComplete = std::bind(&Player::ChangeEffectOff, this);
		}
		else
		{
			SpritePlayer.setScale(1.5f, 1.5f);
			SpritePlayer.setOrigin(150, 100);
			animation.Play("Idle");

			//changeEffectPosition = playerPosition;
			changeEffectAnimation.Play("ChangeEffect");
			changeEffectAnimation.OnComplete = std::bind(&Player::ChangeEffectOff, this);
		}
		//currentAction = PlayerState::IDLE;
	}
}

void Player::ChangeEffectOff()
{
	isChangeEffect = false;
}

void Player::AliveToDead()
{
	isAlive = false;
	
}

void Player::SkillDelete()
{
	isSkill = false;
}

