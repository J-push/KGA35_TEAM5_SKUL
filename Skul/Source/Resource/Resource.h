#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>

using namespace sf;

enum class ResourceTypes
{
	None = -1,
	Texture,
	Font,
	SoundBuffer,
	Count,
};

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

