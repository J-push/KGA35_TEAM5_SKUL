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
	IntRect texCoord;

	AnimationFrame(const Texture tex, const IntRect coord);
};


struct AnimationClip
{
	std::string id;
	std::vector<AnimationFrame> frames;
	AnimationLoopTypes loopType;
	int fps; // 1ÃÊ´ç ¾ó¸¶³ª ÂïÀ»²«°¡
};






