#include "ResourceMgr.h"
#include <list>
/**********************************************************
* 설명 : Resource파일들을 초기화 한다.
***********************************************************/
void ResourceMgr::Init()
{
	std::list<Resource*> loaded;	//리스트에
	loaded.push_back(new Resource("MAINFONT", "fonts/KOMIKAP_.ttf", ResourceTypes::Font));
	loaded.push_back(new Resource("TITLETEX", "graphics/menu/title.png", ResourceTypes::Texture));
	loaded.push_back(new Resource("STARTTEX1", "graphics/menu/GameStartIcon.png", ResourceTypes::Texture));
	loaded.push_back(new Resource("STARTTEX2", "graphics/menu/GameStartIcon2.png", ResourceTypes::Texture));
	
	//loaded.push_back(new Resource("MAINBGTEX", "graphics/background.png", ResourceTypes::Texture));
	///*loaded.push_back(new Resource("MAINTITLETEX", "graphics/title.png", ResourceTypes::Texture));*/
	//loaded.push_back(new Resource("MAINBEETEX", "graphics/bee.png", ResourceTypes::Texture));
	//loaded.push_back(new Resource("MAINCLOUDTEX", "graphics/cloud.png", ResourceTypes::Texture));
	//loaded.push_back(new Resource("MAINTREETEX", "graphics/tree.png", ResourceTypes::Texture));
	//loaded.push_back(new Resource("MAINBRANCHTEX", "graphics/branch.png", ResourceTypes::Texture));
	//loaded.push_back(new Resource("MAINPLAYERTEX", "graphics/player.png", ResourceTypes::Texture));

	//loaded.push_back(new Resource("MAINRIPTEX", "graphics/rip.png", ResourceTypes::Texture));
	//loaded.push_back(new Resource("MAINAXETEX", "graphics/axe.png", ResourceTypes::Texture));
	//loaded.push_back(new Resource("MAINLOGTEX", "graphics/log.png", ResourceTypes::Texture));
	//loaded.push_back(new Resource("CHOPSOUND", "sound/chop.wav", ResourceTypes::SoundBuffer));
	//loaded.push_back(new Resource("DEATHSOUND", "sound/death.wav", ResourceTypes::SoundBuffer));
	//loaded.push_back(new Resource("OOTSOUND", "sound/out_of_time.wav", ResourceTypes::SoundBuffer));
	
	for (std::list<Resource*>::iterator it = loaded.begin(); it != loaded.end(); ++it)
	{
		Resource* res = (*it);
		if (!res->Load())
		{
			delete res;
			// 메세지
			continue;
		}
		resouceMap[(*it)->id] = res;
	}
}

Resource* ResourceMgr::GetResource(std::string id)
{
	std::map<std::string, Resource*>::iterator find = resouceMap.find(id);
	if (find == resouceMap.end())
	{
		return nullptr;
	}
	return find->second;
}

Texture* ResourceMgr::GetTexture(std::string id)
{
	Resource* find = GetResource(id);
	if (!find)
		return nullptr;
	return find->texture;
}

Font* ResourceMgr::GetFont(std::string id)
{
	Resource* find = GetResource(id);
	if (!find)
		return nullptr;
	return find->font;
}

SoundBuffer* ResourceMgr::GetSoundBuffer(std::string id)
{
	Resource* find = GetResource(id);
	if (!find)
		return nullptr;
	return find->soundBuffer;
}
