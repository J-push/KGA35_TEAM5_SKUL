#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Player
{
private:
	const float START_PLAYER_HEALTH = 100;		//���� �÷��̾� ü��;
	const float START_PLAYER_SPEED = 200;		//���� �÷��̾� �ӵ�;



	Vector2f mPlayerPosition;					//player ��ǥ

	int mTileSize;								//Ÿ���� ũ��

	float mSpeed;								//player �ӵ�
	int mMaxPlayerHealth;						//player �ִ� ü��
	int mCurrentPlayerHealth;					//player ���� ü��

	int mPlayerType;							//�� Ÿ��? ���� ����

	bool mPlayerDash;							//player�뽬 ����

	float mSkillCoolTime;						//��ų ��Ÿ��
public:
	Player();
	~Player();




};

