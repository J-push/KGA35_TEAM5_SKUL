#pragma once
#include "Singleton.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include "Resource.h"
#include <map>

using namespace sf;

class ResourceMgr : public Singleton<ResourceMgr>
{
private:
	std::map<std::string, Resource*> resouceMap;


public:
	void Init();
	//void Release();
	
	Resource* GetResource(std::string id);
	Texture* GetTexture(std::string id);
	Font* GetFont(std::string id);
	SoundBuffer* GetSoundBuffer(std::string id);

};

