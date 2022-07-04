/******************************************************************************
* 작 성 자 : 김 재 휘
* 작 성 일 : 2022-05-04
* 내    용 : Resource의 전체적인 틀을 담당한다.
* 수 정 일 :
*******************************************************************************/
/*include될 헤더*/
#include "Resource.h"

/**********************************************************
* 설명 : Resource의 매개변수들을 초기화한다.
***********************************************************/
Resource::Resource()
{
	id = "";
	path = "";
	resourceType = ResourceTypes::None;

	texture = nullptr;
	font = nullptr;
	soundBuffer = nullptr;
}
/**********************************************************
* 설명 : 생성자
***********************************************************/
Resource::Resource(std::string id, std::string path, ResourceTypes resourceType)
{
	this->id = id;
	this->path = path;
	this->resourceType = resourceType;

	texture = nullptr;
	font = nullptr;
	soundBuffer = nullptr;
}
/**********************************************************
* 설명 : 소멸자
***********************************************************/
Resource::~Resource()
{
	if (!texture)
		delete texture;
	if (!font)
		delete font;
	if (!soundBuffer)
		delete soundBuffer;
}
/**********************************************************
* 설명 : 리소스를 Load한다.
***********************************************************/
bool Resource::Load()
{
	switch (resourceType)
	{
	case ResourceTypes::Texture:
		texture = new Texture();
		return texture->loadFromFile(path);
	case ResourceTypes::Font:
		font = new Font();
		return font->loadFromFile(path);
	case ResourceTypes::SoundBuffer:
		soundBuffer = new SoundBuffer();
		return soundBuffer->loadFromFile(path);
	}

	return false;

}
