#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include <vector>

using namespace sf;
/**********************************************************
* ���� : Loop�� ������ �Ǵ��ϴ� enum class
***********************************************************/
enum class AnimationLoopTypes
{
	Single,
	Loop,
};

/**********************************************************
* ���� : Texture�� ��ǥ���� �ʱ�ȭ�ϴ� ����ü
***********************************************************/
struct AnimationFrame
{
	Texture *texture;
	IntRect texCoord; // LT��ǥ��, �簢���� ����� ���ڷ� ����

	AnimationFrame(Texture &tex, const IntRect coord);
};

/**********************************************************
* ���� : ��ü���� Ʋ
***********************************************************/
struct AnimationClip
{
	std::string id;
	std::vector<AnimationFrame> frames; // �� �������� ���Ϳ� ����?
	AnimationLoopTypes loopType;
	int fps; // 1�ʴ� �󸶳� ��������
};






