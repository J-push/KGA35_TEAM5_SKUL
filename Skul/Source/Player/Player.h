#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Player
{
private:
	const float START_PLAYER_HEALTH = 100;		//시작 플레이어 체력;
	const float START_PLAYER_SPEED = 200;		//시작 플레이어 속도;



	Vector2f mPlayerPosition;					//player 좌표

	int mTileSize;								//타일의 크기

	float mSpeed;								//player 속도
	int mMaxPlayerHealth;						//player 최대 체력
	int mCurrentPlayerHealth;					//player 현재 체력

	int mPlayerType;							//뼈 타입? 아직 미정

	bool mPlayerDash;							//player대쉬 유무

	float mSkillCoolTime;						//스킬 쿨타임
public:
	Player();
	~Player();




};

