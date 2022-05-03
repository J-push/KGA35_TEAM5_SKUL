#include "../Manager/ResourceMgr.h"
#include <list>
/**********************************************************
* ���� : Resource���ϵ��� �ʱ�ȭ �Ѵ�.
***********************************************************/
void ResourceMgr::Init()
{
	std::list<Resource*> loaded;	//����Ʈ��
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
			// �޼���
			continue;
		}
		resouceMap[(*it)->id] = res;
	}
}

/**********************************************************
* ���� : Resource���ϵ��� ������ �´�.
* ����1 : ���ҽ��� �Ҵ��� ���̵�
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
