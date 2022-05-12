#pragma once
#include <SFML/Graphics.hpp>
#include "../Utils/Singleton.h"


//#include "Scene.h"
// TITLE, MENU, GAME, CHARACTER

/**********************************************************
* 설명 : Scene 0~4 enum class 선언
***********************************************************/
enum class Scenes
{
	TITLE, MENU, GAME, EDITOR, END, COUNT
};
class Scene;

class SceneMgr : public Singleton<SceneMgr>
{
private:
	Scene* scenes[(int)Scenes::COUNT];
	Scenes currentScene;

public:
	void Init();
	void Release();
	void ChangeScene(Scenes newScene);

	void Update(float dt, sf::RenderWindow *window, sf::View *mainView);
	void Draw(sf::RenderWindow *window, sf::View *mainView, sf::View *uiView);
	
	Scenes GetCurrentScene();
};

