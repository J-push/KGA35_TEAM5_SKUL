/******************************************************************************
* 작 성 자 : 김 재 휘
* 작 성 일 : 2022-05-04
* 내    용 : 전체 프레임워크의 리소스를 관리한다.
* 수 정 일 :
*******************************************************************************/
/*include될 헤더*/
#include "../Manager/ResourceMgr.h"
#include <list>

/**********************************************************
* 설명 : Resource파일들을 초기화 한다.
***********************************************************/
void ResourceMgr::Init()
{
	std::list<Resource *> loaded;	//리스트에 // 나중에지울것들?
	loaded.push_back(new Resource("MAINFONT", "fonts/KOMIKAP_.ttf", ResourceTypes::Font));
	loaded.push_back(new Resource("TITLETEX", "graphics/menu/title.png", ResourceTypes::Texture));
	loaded.push_back(new Resource("STARTTEX1", "graphics/menu/GameStartIcon.png", ResourceTypes::Texture));
	loaded.push_back(new Resource("STARTTEX2", "graphics/menu/GameStartIcon2.png", ResourceTypes::Texture));

	//2022.05.04 재휘커서 추가, 지용 배경 추가
	loaded.push_back(new Resource("CURSORTEX", "graphics/menu/Cursor.png", ResourceTypes::Texture));
	//loaded.push_back(new Resource("CHOPSOUND", "sound/chop.wav", ResourceTypes::SoundBuffer));
	loaded.push_back(new Resource("BACKGROUNDTEX", "graphics/background.png", ResourceTypes::Texture));
	loaded.push_back(new Resource("EDITORBACKGROUNDTEX", "graphics/editorbackground.png", ResourceTypes::Texture));
	loaded.push_back(new Resource("TILETEX", "graphics/TileGrass.png", ResourceTypes::Texture));

	// ui추가
	loaded.push_back(new Resource("MAINFRAMETEX", "graphics/UI/PlayerFrame.png", ResourceTypes::Texture));
	loaded.push_back(new Resource("HPBARTEX", "graphics/UI/HpBar.png", ResourceTypes::Texture));
	loaded.push_back(new Resource("ABUTTONTEX", "graphics/UI/Abutton.png", ResourceTypes::Texture));

	loaded.push_back(new Resource("REAPERICONTEX1", "graphics/UI/GrimReaper1.png", ResourceTypes::Texture));
	loaded.push_back(new Resource("REAPERICONTEX3", "graphics/UI/GrimReaper3.png", ResourceTypes::Texture));
	loaded.push_back(new Resource("REAPERSKILLTEX", "graphics/UI/GrimReaperSkill.png", ResourceTypes::Texture));
	loaded.push_back(new Resource("BONEICONTEX1", "graphics/UI/LittleBone1.png", ResourceTypes::Texture));
	loaded.push_back(new Resource("BONEICONTEX3", "graphics/UI/LittleBone3.png", ResourceTypes::Texture));

	loaded.push_back(new Resource("BOSSFRAMETEX", "graphics/UI/BossFrame.png", ResourceTypes::Texture));
	loaded.push_back(new Resource("BOSSHPBARTEX", "graphics/UI/BossHpBar.png", ResourceTypes::Texture));
	




	// boss 
	loaded.push_back(new Resource("BOSSTEX1", "graphics/Boss/bosstext1.png", ResourceTypes::Texture));
	loaded.push_back(new Resource("BOSSTEX2", "graphics/Boss/bosstext2.png", ResourceTypes::Texture));
	loaded.push_back(new Resource("BOSSTEX3", "graphics/Boss/bosstext3.png", ResourceTypes::Texture));

	loaded.push_back(new Resource("PLAYERATTACKSOUND", "sound/player/Attack.wav", ResourceTypes::SoundBuffer));
	loaded.push_back(new Resource("PLAYERCHANGESOUND", "sound/player/Change.wav", ResourceTypes::SoundBuffer));
	loaded.push_back(new Resource("PLAYERDASHSOUND", "sound/player/Dash.wav", ResourceTypes::SoundBuffer));
	loaded.push_back(new Resource("PLAYERJUMPSOUND", "sound/player/Jump.wav", ResourceTypes::SoundBuffer));
	loaded.push_back(new Resource("PLAYERDEATHSOUND", "sound/player/Death.wav", ResourceTypes::SoundBuffer));

	loaded.push_back(new Resource("SWORDMANATTACKSOUND", "sound/swordman/attack.wav", ResourceTypes::SoundBuffer));
	loaded.push_back(new Resource("PINKENTATTACKSOUND", "sound/pinkent/attack.wav", ResourceTypes::SoundBuffer));



	// endScene용
	loaded.push_back(new Resource("SCORETEX", "graphics/UI/ScoreFrame.png", ResourceTypes::Texture));
	loaded.push_back(new Resource("ENDTEX", "graphics/UI/DieFrame.png", ResourceTypes::Texture));

	for (std::list<Resource *>::iterator it = loaded.begin(); it != loaded.end(); ++it)
	{
		Resource *res = (*it);
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
***********************************************************/
Resource *ResourceMgr::GetResource(std::string id)
{
	std::map<std::string, Resource *>::iterator find = resouceMap.find(id);
	if (find == resouceMap.end())
	{
		return nullptr;
	}
	return find->second;
}
/**********************************************************
* 설명 : 이미지 리소스들을 가지고 온다.
***********************************************************/
Texture *ResourceMgr::GetTexture(std::string id)
{
	Resource *find = GetResource(id);
	if (!find)
		return nullptr;
	return find->texture;
}
/**********************************************************
* 설명 : 폰트 리소스를 가져온다.
***********************************************************/
Font *ResourceMgr::GetFont(std::string id)
{
	Resource *find = GetResource(id);
	if (!find)
		return nullptr;
	return find->font;
}
/**********************************************************
* 설명 : 사운드 리소스를 가져온다.
***********************************************************/
SoundBuffer *ResourceMgr::GetSoundBuffer(std::string id)
{
	Resource *find = GetResource(id);
	if (!find)
		return nullptr;
	return find->soundBuffer;
}
