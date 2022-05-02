#include "Resource.h"

Resource::Resource()
{
	id = "";
	path = "";
	resourceType = ResourceTypes::None;

	texture = nullptr;
	font = nullptr;
	soundBuffer = nullptr;
}

Resource::Resource(std::string id, std::string path, ResourceTypes resourceType)
{
	this->id = id;
	this->path = path;
	this->resourceType = resourceType;

	texture = nullptr;
	font = nullptr;
	soundBuffer = nullptr;
}

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
