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
	IntRect texCoord; // LT��ǥ��, �簢���� ����� ���ڷ� ����

	AnimationFrame(const Texture tex, const IntRect coord);
};


struct AnimationClip
{
	std::string id;
	std::vector<AnimationFrame> frames; // �� �������� ���Ϳ� ����?
	AnimationLoopTypes loopType;
	int fps; // 1�ʴ� �󸶳� ��������
};






