#include "Player.h"
#include "../Animation/rapidcsv.h"
#include "../Utils/Utils.h"

void Player::Init()
{
	mPlayerPosition.x = 512.f;
	mPlayerPosition.y = 512.f;
	mSpeed = START_PLAYER_SPEED;

	SpritePlayer.setPosition(880, 700);
	SpritePlayer.setOrigin(100, 100);
	SpritePlayer.setScale(2.f, 2.f);
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
	animation.Play("Idle");
}

void Player::Spawn(IntRect arena, Vector2i res, int tileSize)
{

}

void Player::UpdateInput()
{
	//Play를 여러번 해주면 프레임에서 멈춘다?
	if (InputManager::instance()->GetKeyDown(Keyboard::Right))
	{
		animation.Play("RightWalk");
	}
	if (InputManager::instance()->GetKeyDown(Keyboard::Left))
	{
		animation.Play("LeftWalk");
	}

	if (InputManager::instance()->GetKeyUp(Keyboard::Right) ||
		InputManager::instance()->GetKeyUp(Keyboard::Left))
	{
		animation.Play("Idle");
		animation.PlayQueue("Idle");
	}
	if (InputManager::instance()->GetKeyDown(Keyboard::X))
	{
		
		animation.Play("Attack");
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

void Player::Update(float dt)
{
	UpdateInput();
	
	float h = InputManager::GetAxisRaw(Axis::Horizontal);
	float v = InputManager::GetAxisRaw(Axis::Vertical);
	Vector2f dir(h, v);

	Utils::Normalize(dir);

	//이동처리를 하는 곳이긴한데... 아직 빡숙 불가...
	//if (dir.x == 0.f && mLastDir != dir)
	//{
	//	animation.Play("Idle");
	//	
	//}
	//if (dir.x > 0.f && mLastDir != dir)
	//{
	//	animation.Play("RightWalk");
	//	mPlayerPosition.x += dir.x * mSpeed * dt;
	//}
	//if (dir.x < 0.f && mLastDir != dir)
	//{
	//	animation.Play("LeftWalk");
	//	mPlayerPosition.x -= dir.x * mSpeed * dt;
	//}
	//탑뷰든 사이드 뷰든 노상관~
	//위는 X
	if (InputManager::instance()->GetKey(Keyboard::Right))
	{
		mPlayerPosition.x +=  mSpeed * dt;
	}

	mLastDir = dir;
	SpritePlayer.setPosition(mPlayerPosition);

	animation.Update(dt);
}


Sprite Player::GetSprite()
{
	return SpritePlayer;
}

void Player::Draw(RenderWindow& window)
{
	window.draw(SpritePlayer);
}
