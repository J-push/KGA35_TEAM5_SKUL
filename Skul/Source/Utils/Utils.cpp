/******************************************************************************
* 작 성 자 : 김 재 휘
* 작 성 일 : 2022-05-03
* 내    용 : 게임의 전체적인 Utility(함수)들을 담당한다.
* 수 정 일 :
*******************************************************************************/
/*include될 헤더*/
#include "Utils.h"
#include <iostream>
#include <cmath>

/*static 변수 선언*/
std::random_device Utils::rd;
std::mt19937 Utils::gen(rd());

/**********************************************************
* 설명 : 텍스트 좌표의 값을 preset으로 지정한다.
***********************************************************/
void Utils::SetOrigin(sf::Text &text, Pivots preset)
{
	SetOrigin(text, text.getLocalBounds(), preset);
}
/**********************************************************
* 설명 : 도형의 좌표의 값을 preset으로 지정한다.
***********************************************************/
void Utils::SetOrigin(sf::Shape &shape, Pivots preset)
{
	SetOrigin(shape, shape.getLocalBounds(), preset);
}
/**********************************************************
* 설명 : 그림의 좌표의 값을 preset으로 지정한다.
***********************************************************/
void Utils::SetOrigin(sf::Sprite &sprite, Pivots preset)
{
	SetOrigin(sprite, sprite.getLocalBounds(), preset);
}
/**********************************************************
* 설명 : 전체적인 Origin을 설정하기 위한 함수.
***********************************************************/
void Utils::SetOrigin(sf::Transformable &tr, sf::FloatRect bounds, Pivots preset)
{
	switch (preset)
	{
	case Pivots::LT:
		tr.setOrigin(bounds.left, bounds.top);
		break;
	case Pivots::LC:
		tr.setOrigin(bounds.left, bounds.height * 0.5f);
		break;
	case Pivots::LB:
		tr.setOrigin(bounds.left, bounds.height);
		break;
	case Pivots::CT:
		tr.setOrigin(bounds.width * 0.5f, bounds.top);
		break;
	case Pivots::CC:
		tr.setOrigin(bounds.width * 0.5f, bounds.height * 0.5f);
		break;
	case Pivots::CB:
		tr.setOrigin(bounds.width * 0.5f, bounds.height);
		break;
	case Pivots::RT:
		tr.setOrigin(bounds.width, bounds.top);
		break;
	case Pivots::RC:
		tr.setOrigin(bounds.width, bounds.height * 0.5f);
		break;
	case Pivots::RB:
		tr.setOrigin(bounds.width, bounds.height);
		break;

	default:
		break;
	}
}
/**********************************************************
* 설명 : 랜덤 범위를 설정한다.
***********************************************************/
int Utils::RandomRange(int min, int excludeMax)
{
	int range = excludeMax - min;
	return min + gen() % range;
}

/**********************************************************
* 설명 : 여기서 standRect는 다른 클래스에서 불러오는 거고 testRect는 현재 클래스, 즉 기준이 된다.
* ex) 플레이어와 벽과의 충돌을 적으려 할 때 플레이어 클래스에서 이용하면 된다. standRect -> Wall  , testRect -> Player 
***********************************************************/
Pivots Utils::CollisionDir(FloatRect standRect, FloatRect testRect)
{
	//testRect를 기준

	//testRect의 왼쪽
	if (testRect.left < standRect.left + standRect.width
		&& testRect.left + testRect.width > standRect.left + standRect.width)
	{
		return Pivots::LC;
	}

	//오른쪽
	else if (testRect.left + testRect.width > standRect.left && testRect.left < standRect.left)
	{
		return Pivots::RC;
	}
	
	//위
	else if (testRect.top < standRect.top + standRect.height && testRect.top + testRect.height > standRect.top + standRect.height)
	{
		return Pivots::CT;
	}

	//아래
	else
	{
		return Pivots::CB;
	}

	return Pivots();
}
/**********************************************************
* 설명 : 길이를 들고온다.
***********************************************************/
float Utils::GetLength(const Vector2f &vector)
{
	return sqrt(vector.x * vector.x + vector.y * vector.y);
}
/**********************************************************
* 설명 : 정규화한다.
***********************************************************/
Vector2f Utils::Normalize(const Vector2f &vector)
{
	Vector2f v = vector;
	float length = GetLength(vector);

	if (length > 0)
	{
		v /= length;
	}

	return v;
}
/**********************************************************
* 설명 : 회전. 쓰지않을 듯?
***********************************************************/
float Utils::GetAngel(const Vector2f &from, const Vector2f &to)
{
	Vector2f dir = to - from;
	float radian = atan2(dir.y, dir.x);
	return radian * 180.f / 3.141592;
}
