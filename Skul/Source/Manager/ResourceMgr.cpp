#include "../Manager/ResourceMgr.h"
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
	loaded.push_back(new Resource("BACKGROUNDTEX", "graphics/background.png", ResourceTypes::Texture));
	loaded.push_back(new Resource("TILETEX", "graphics/TileGrass.png", ResourceTypes::Texture));
	
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

/**********************************************************
* 설명 : Resource파일들을 가지고 온다.
* 변수1 : 리소스에 할당한 아이디
***********************************************************/
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
