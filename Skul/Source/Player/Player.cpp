/******************************************************************************
* �� �� �� : �� �� ��
* �� �� �� : 2022-05-04
* ��    �� : Player�� ������ �����Ѵ�.
* �� �� �� :
*******************************************************************************/
/*include�� ���*/
#include "Player.h"
#include "../Animation/rapidcsv.h"
#include "../Utils/Utils.h"

/**********************************************************
* ���� : �÷��̾ �ʱ�ȭ�Ѵ�.
***********************************************************/
void Player::Init()
{
	Player player;
	mPlayerPosition.x = 512.f;
	mPlayerPosition.y = 750.f;
	mSpeed = START_PLAYER_SPEED;

	mPlayerAttacking = false;

	SpritePlayer.setPosition(880, 700);
	SpritePlayer.setOrigin(70, 100);
	SpritePlayer.setScale(2.f, 2.f);
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
}
/**********************************************************
* ���� : �÷��̾��� �ʱ� ���� ��ġ�� �����Ѵ�.
***********************************************************/
void Player::Spawn(IntRect arena, Vector2i res, int tileSize)
{

}
/**********************************************************
* ���� : �÷��̾��� Ű���� �Է°��� ���� ������ �����Ѵ�.
***********************************************************/
void Player::UpdateInput()
{
	
	//Play�� ������ ���ָ� �����ӿ��� �����?
	if (InputManager::instance()->GetKeyDown(Keyboard::Right))
	{
		
		animation.Play("Walk");
		SpritePlayer.setScale(2.f, 2.f);
	}
	if (InputManager::instance()->GetKeyDown(Keyboard::Left))
	{
		SpritePlayer.setScale(-2.f, 2.f);
		animation.Play("Walk");
		//animation.Play("LeftWalk");
		
	}

	if (InputManager::instance()->GetKeyUp(Keyboard::Right) ||
		InputManager::instance()->GetKeyUp(Keyboard::Left))
	{
		//SpritePlayer.setScale(3.f, 3.f);
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
			mPlayerAttacking = false;
			animation.PlayQueue("Idle");
		}
		animation.PlayQueue("Idle");
	}
	

	/*switch (event.type)
	{
	case Event::KeyPressed:
		switch (event.key.code)
		{
		case Keyboard::Down:
			animation.PlayQueue("Idle");
			break;
		case Keyboard::Right:
			animation.PlayQueue("RightWalk");
			break;
		case Keyboard::Left:
			animation.PlayQueue("LeftWalk");
			break;

		}
	}*/
}
/**********************************************************
* ���� : �÷��̾ ������Ʈ�Ѵ�.
***********************************************************/
void Player::Update(float dt)
{
	UpdateInput();
	
	/*float h = InputManager::GetAxisRaw(Axis::Horizontal);
	float v = InputManager::GetAxisRaw(Axis::Vertical);
	Vector2f dir(h, v);

	Utils::Normalize(dir);*/
	if (InputManager::instance()->GetKey(Keyboard::Right))
	{
		mPlayerPosition.x += mSpeed * dt;
	}
	if (InputManager::instance()->GetKey(Keyboard::Left))
	{
		mPlayerPosition.x -= mSpeed * dt;
	}
	//�̵�ó���� �ϴ� ���̱��ѵ�... ���� ���� �Ұ�...
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
	//ž��� ���̵� ��� ����~
	//���� X
	
	//mLastDir = dir;
	SpritePlayer.setPosition(mPlayerPosition);

	animation.Update(dt);
}

Vector2f Player::GetPosition()
{
	return mPlayerPosition;
}

/**********************************************************
* ���� : �÷��̾��� sprite�� ��� �´�.
***********************************************************/
Sprite Player::GetSprite()
{
	return SpritePlayer;
}
/**********************************************************
* ���� : �÷��̾ �׸���.
***********************************************************/
void Player::Draw(RenderWindow& window)
{
	window.draw(SpritePlayer);
	//window.setView(mainView);
}
