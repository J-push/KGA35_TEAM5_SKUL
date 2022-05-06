#pragma once
#include <SFML/Graphics.hpp>
#include <random>

using namespace sf;
/**********************************************************
* 설명 : 좌표를 지정해주기 위한 틀.
***********************************************************/
enum class Pivots
{
	// L, CH, R
	// T, CV, R
	LT, CT, RT,
	LC, CC, RC,
	LB, CB, RB
};
/**********************************************************
* 설명 : Utils 클래스
***********************************************************/
class Utils
{
private:
	static std::random_device rd;
	static std::mt19937 gen;

public:
	static void SetOrigin(Text &text, Pivots preset);
	
	static void SetOrigin(Sprite &sprite, Pivots preset);

	static void SetOrigin(Shape &shape, Pivots preset);

	static void SetOrigin(Transformable &tr, FloatRect bounds, Pivots preset);

	static int RandomRange(int min, int excludeMax);

	static float GetLength(const Vector2f &vector);
	static Vector2f Normalize(const Vector2f &vector);
	static float GetAngel(const Vector2f &from, const Vector2f &to);

	static Pivots CollisionDir(FloatRect standRect, FloatRect testRect);
};

