#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include <vector>

using namespace sf;
/**********************************************************
* 설명 : Loop의 유무를 판단하는 enum class
***********************************************************/
enum class AnimationLoopTypes
{
	Single,
	Loop,
};

/**********************************************************
* 설명 : Texture와 좌표값을 초기화하는 구조체
***********************************************************/
struct AnimationFrame
{
	Texture *texture;

	IntRect texCoord; // LT좌표와, 사각형의 사이즈를 인자로 받음
	AnimationFrame(Texture &tex, const IntRect coord);

};

/**********************************************************
* 설명 : 전체적인 틀
***********************************************************/
struct AnimationClip
{
	std::string id;
	std::vector<AnimationFrame> frames; // 각 프레임을 벡터에 저장?
	AnimationLoopTypes loopType;
	int fps; // 1초당 얼마나 찍을껀가
};






