#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include <vector>

using namespace sf;

enum class AnimationLoopTypes
{
	Single,
	Loop,
};

struct AnimationFrame
{
	Texture texture;
	IntRect texCoord; // LT좌표와, 사각형의 사이즈를 인자로 받음

	AnimationFrame(const Texture tex, const IntRect coord);
};


struct AnimationClip
{
	std::string id;
	std::vector<AnimationFrame> frames; // 각 프레임을 벡터에 저장?
	AnimationLoopTypes loopType;
	int fps; // 1초당 얼마나 찍을껀가
};






