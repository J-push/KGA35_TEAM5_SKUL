#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>

using namespace sf;

/**********************************************************
* 설명 : 리소스의 종류를 나타내는 enum class
***********************************************************/
enum class ResourceTypes
{
	None = -1,
	Texture,
	Font,
	SoundBuffer,
	Count,
};
/**********************************************************
* 설명 : Resource의 틀을 만드는 구조체
***********************************************************/
struct Resource
{
	std::string id;
	std::string path;
	ResourceTypes resourceType;

	Texture* texture;
	Font* font;
	SoundBuffer* soundBuffer;

	Resource();
	Resource(std::string id, std::string path, ResourceTypes resourceType);
	~Resource();
	bool Load();
};

