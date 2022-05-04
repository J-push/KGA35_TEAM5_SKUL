#pragma once
#include <SFML/Graphics.hpp>
#include "../Animation/AnimationController.h"
#include <map>
#include "../Manager/InputManager.h"

using namespace sf;

class Player
{
private:
	const float START_PLAYER_HEALTH = 100;		//���� �÷��̾� ü��;
	const float START_PLAYER_SPEED = 200;		//���� �÷��̾� �ӵ�;
	const float START_PLAYER_STR = 10;			//���� �÷��̾� ���ݷ�
	const float GRAVITY_POWER = 980.f;			//�߷�

	Texture texture;

	Sprite SpritePlayer;						//player �׸���
	Vector2f mPlayerPosition;					//player ��ǥ
	Vector2f mLastDir;
	AnimationController animation;

	IntRect gameMap;
	Vector2i resolution;

	std::map<std::string, Texture> texMap;


	int mTileSize;								//Ÿ���� ũ��

	bool isJump;								//�����ߴ�?

	float mSpeed;								//player �ӵ�

	int mMaxPlayerHealth;						//player �ִ� ü��
	int mCurrentPlayerHealth;					//player ���� ü��

	int mPlayerType;							//�� Ÿ��? ���� ����

	bool mPlayerDash;							//player�뽬 ����
	float mDashCoolTime;						//�뽬 ��Ÿ��

	int mPlayerAttackDamage;					//���� ������

	float mSkillCoolTime;						//��ų ��Ÿ��
public:
	void Init();
	void Start();
	void End();

	void Spawn(IntRect arena, Vector2i res, int tileSize);

	void Move(float speed);
	void Dash();
	void Jump();

	void UpdateInput();
	void Update(float dt);

	Sprite GetSprite();

	void Draw(RenderWindow &window);



};

