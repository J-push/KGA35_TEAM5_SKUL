#include "SceneMapEditor.h"
#include "../Manager/ResourceMgr.h"

void SceneMapEditor::Init()
{
	//tileView = new View(FloatRect(0, 0, 1080.f, 1080.f));
	//tileView->setViewport(sf::FloatRect(0.f, 0.f, 0.56f, 0.56f));
	//mapSampleView->setViewport(sf::FloatRect(0.56f, 0.56f, 1.f, 1.f));
	//spriteBackground.setTexture(*ResourceMgr::instance()->GetTexture("EDITORBACKGROUNDTEX"));
	//spriteBackground.setScale(Vector2f(0.5f, 1.f));
	//spriteTile.setTexture(*ResourceMgr::instance()->GetTexture("TILETEX"));
	//spriteTile.setPosition(1335.f, 0.f);
	//spriteTile.setScale(3.f, 3.f);
}

void SceneMapEditor::Release()
{
	delete tileView;
}

void SceneMapEditor::Start()
{
}

void SceneMapEditor::End()
{
}
void SceneMapEditor::Update(float dt)
{
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		tileView->move(-20.f, 0.f);
	}
	else if (Keyboard::isKeyPressed(Keyboard::D))
	{
		tileView->move(20.f, 0.f);
	}
	else if (Keyboard::isKeyPressed(Keyboard::W))
	{
		tileView->move(0.f, -20.f);
	}
	else if (Keyboard::isKeyPressed(Keyboard::S))
	{
		tileView->move(0.f, 20.f);
	}
}

void SceneMapEditor::Draw(sf::RenderWindow* window)
{
	window->clear();
	window->setView(*tileView);

	window->clear();
	window->setView(*mapSampleView);
	window->draw(spriteBackground);
	window->draw(spriteTile);
}