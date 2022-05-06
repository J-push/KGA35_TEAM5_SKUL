#include "SceneMapEditor.h"
#include "../Manager/ResourceMgr.h"

void SceneMapEditor::Init()
{
	spriteTile.setTexture(*ResourceMgr::instance()->GetTexture("TILETEX"));
	spriteTile.setPosition(1500.f, 180.f);
	spriteTile.setScale(2.f, 2.f);
}

void SceneMapEditor::Release()
{
}

void SceneMapEditor::Start()
{
}

void SceneMapEditor::End()
{
}
void SceneMapEditor::Update(float dt)
{
	
}

void SceneMapEditor::Draw(sf::RenderWindow* window)
{
	window->draw(spriteTile);
}
