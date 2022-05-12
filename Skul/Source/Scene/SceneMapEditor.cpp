#include "SceneMapEditor.h"
#include "../Manager/ResourceMgr.h"

void SceneMapEditor::Init()
{
    CurrentMousePosition = true;
    currentInputState = InputState::BLOCK;
    gridSizeU =static_cast<unsigned>(gridSizeF);

    tileMap.resize(MAPWIDTH, vector<RectangleShape>());
    for (int i = 0; i < MAPWIDTH; i++)
    {
        tileMap[i].resize(MAPHEIGHT, RectangleShape());
        for (int j = 0; j < MAPHEIGHT; j++)
        {
            tileMap[i][j].setSize(Vector2f(gridSizeF, gridSizeF));
            tileMap[i][j].setFillColor(Color::White);
            tileMap[i][j].setOutlineThickness(1.f);
            tileMap[i][j].setOutlineColor(Color::Black);
            tileMap[i][j].setPosition(i * gridSizeF, j * gridSizeF);
        }
    }

    //왼쪽 타일셀렉터
    tileSelector.setSize(Vector2f(gridSizeF, gridSizeF));
    tileSelector.setFillColor(sf::Color::Transparent);
    tileSelector.setOutlineThickness(1.f);
    tileSelector.setOutlineColor(sf::Color::Red);

    //오른쪽 타일셀렉터
    sampleSelector.setSize(Vector2f(gridSizeF * 5, gridSizeF * 5));
    sampleSelector.setFillColor(sf::Color::Transparent);
    sampleSelector.setOutlineThickness(1.f);
    sampleSelector.setOutlineColor(sf::Color::Blue);

    //16:9 기본화면 세팅
    text.setFont(*ResourceMgr::instance()->GetFont("MAINFONT"));
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Red);
    text.setPosition(0.f, 0.f);

    text2.setFont(*ResourceMgr::instance()->GetFont("MAINFONT"));
    text2.setCharacterSize(36);
    text2.setFillColor(sf::Color::Blue);
    text2.setPosition(1500.f, 20.f);

    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;
    tileView = new View(FloatRect(0, 0, resolution.x, resolution.y));
    tileView->setSize(1920.f, 1080.f);

    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;
    uiView = new View(FloatRect(0, 0, resolution.x, resolution.y));
    uiView->setSize(1920.f, 1080.f);
    spriteTile.setTexture(*ResourceMgr::instance()->GetTexture("TILETEX"));
    spriteTile.setPosition(0.f, 0.f);
    spriteTile.setScale(5.f, 5.f);
    spriteBackground.setTexture(*ResourceMgr::instance()->GetTexture("EDITORBACKGROUNDTEX"));
}

void SceneMapEditor::Release()
{
    delete tileView;
    delete uiView;
    delete spriteTile.getTexture();
    delete spriteBackground.getTexture();
    for (auto it : rects)
    {
        delete it;
    }
    rects.clear();
}

int SceneMapEditor::CreateTile(int c, int r, int idx)
{
    int cols = MAPWIDTH;
    int rows = MAPHEIGHT;

    palette.setPrimitiveType(Quads);
    palette.resize(cols * rows * VERTS_IN_QUAD);

    int index = r * cols + c;

    float x = c * gridSizeF;
    float y = r * gridSizeF;

    int vertexIndex = index * VERTS_IN_QUAD;

    palette[vertexIndex + 0].position = Vector2f(x, y);
    palette[vertexIndex + 1].position = Vector2f(x + gridSizeF, y);
    palette[vertexIndex + 2].position = Vector2f(x + gridSizeF, y + gridSizeF);
    palette[vertexIndex + 3].position = Vector2f(x, y + gridSizeF);

    for (int r = 0; r < rows; ++r)
    {
        for (int c = 0; c < cols; ++c)
        {
            texIndex = 11;
            texIndex = idx;

            float offset = texIndex * gridSizeF;
            palette[vertexIndex + 0].texCoords = Vector2f(gridSizeF * 0, offset);
            palette[vertexIndex + 1].texCoords = Vector2f(gridSizeF * 1, offset);
            palette[vertexIndex + 2].texCoords = Vector2f(gridSizeF * 1, offset + gridSizeF);
            palette[vertexIndex + 3].texCoords = Vector2f(gridSizeF * 0, offset + gridSizeF);

            //texIndex 열의 마지막 부분일 떄
            if (5 < texIndex && texIndex <= 11)
            {
                float offset = (texIndex - 6) * gridSizeF;
                palette[vertexIndex + 0].texCoords = Vector2f(gridSizeF * 1, offset);
                palette[vertexIndex + 1].texCoords = Vector2f(gridSizeF * 2, offset);
                palette[vertexIndex + 2].texCoords = Vector2f(gridSizeF * 2, offset + gridSizeF);
                palette[vertexIndex + 3].texCoords = Vector2f(gridSizeF * 1, offset + gridSizeF);
            }
            if (11 < texIndex && texIndex <= 17)
            {
                float offset = (texIndex - 12) * gridSizeF;
                palette[vertexIndex + 0].texCoords = Vector2f(gridSizeF * 2, offset);
                palette[vertexIndex + 1].texCoords = Vector2f(gridSizeF * 3, offset);
                palette[vertexIndex + 2].texCoords = Vector2f(gridSizeF * 3, offset + gridSizeF);
                palette[vertexIndex + 3].texCoords = Vector2f(gridSizeF * 2, offset + gridSizeF);
            }
            if (17 < texIndex && texIndex <= 23)
            {
                float offset = (texIndex - 18) * gridSizeF;
                palette[vertexIndex + 0].texCoords = Vector2f(gridSizeF * 3, offset);
                palette[vertexIndex + 1].texCoords = Vector2f(gridSizeF * 4, offset);
                palette[vertexIndex + 2].texCoords = Vector2f(gridSizeF * 4, offset + gridSizeF);
                palette[vertexIndex + 3].texCoords = Vector2f(gridSizeF * 3, offset + gridSizeF);
            }
            if (23 < texIndex && texIndex <= 29)
            {
                float offset = (texIndex - 24) * gridSizeF;
                palette[vertexIndex + 0].texCoords = Vector2f(gridSizeF * 4, offset);
                palette[vertexIndex + 1].texCoords = Vector2f(gridSizeF * 5, offset);
                palette[vertexIndex + 2].texCoords = Vector2f(gridSizeF * 5, offset + gridSizeF);
                palette[vertexIndex + 3].texCoords = Vector2f(gridSizeF * 4, offset + gridSizeF);
            }
            if (29 < texIndex && texIndex <= 35)
            {
                float offset = (texIndex - 30) * gridSizeF;
                palette[vertexIndex + 0].texCoords = Vector2f(gridSizeF * 5, offset);
                palette[vertexIndex + 1].texCoords = Vector2f(gridSizeF * 6, offset);
                palette[vertexIndex + 2].texCoords = Vector2f(gridSizeF * 6, offset + gridSizeF);
                palette[vertexIndex + 3].texCoords = Vector2f(gridSizeF * 5, offset + gridSizeF);
            }
        }
    }
    return cols * rows;
}

void SceneMapEditor::Start()
{
}

void SceneMapEditor::End()
{
}
void SceneMapEditor::CreateRects()
{
    for (auto v : rects)
    {
        delete v;
    }

    rects.clear();

    // 왼쪽벽
    ColliderRect *rect = new ColliderRect(downGrid.x, upGrid.x, downGrid.y, upGrid.y);
    rects.push_back(rect);
}
void SceneMapEditor::CreateBlocks(int fromX, int toX, int fromY, int toY)
{
}

void SceneMapEditor::Update(float dt, RenderWindow *window, View *mainView)
{
    if (Keyboard::isKeyPressed(Keyboard::A))
    {
        text.move(-VIEW_SPEED * dt, 0.f);
        tileView->move(-VIEW_SPEED * dt, 0.f);
    }
    else if (Keyboard::isKeyPressed(Keyboard::D))
    {
        text.move(VIEW_SPEED * dt, 0.f);
        tileView->move(VIEW_SPEED * dt, 0.f);
    }
    if (Keyboard::isKeyPressed(Keyboard::W))
    {
        text.move(0.f, -VIEW_SPEED * dt);
        tileView->move(0.f, -VIEW_SPEED * dt);
    }
    else if (Keyboard::isKeyPressed(Keyboard::S))
    {
        text.move(0.f, VIEW_SPEED * dt);
        tileView->move(0.f, VIEW_SPEED * dt);
    }
    if (InputManager::GetKeyDown(Keyboard::Add))
    {
        tileView->zoom(0.5f);
    }
    if (InputManager::GetKeyDown(Keyboard::Subtract))
    {
        tileView->zoom(2.f);
    }
    mousePosScreen = Mouse::getPosition();
    mousePosWindow = Mouse::getPosition(*window);
    
    const View &temp = window->getView();

    window->setView(*tileView);
    if (mousePosWindow.x < 960.f)
    {
        mousePosView = window->mapPixelToCoords(mousePosWindow);
        CurrentMousePosition = true;
        mousePosView2.x = 0;
        mousePosView2.y = 0;
 
    }
    window->setView(*uiView);
    if (mousePosWindow.x >= 960.f)
    {
        mousePosView2 = window->mapPixelToCoords(mousePosWindow);
        CurrentMousePosition = false;
        mousePosView.x = 0;
        mousePosView.y = 0;
    }

    window->setView(temp);

    //타일 뷰 그리드
    if (mousePosView.x >= 0.f && mousePosView.y >= 0.f && mousePosView.x <= gridSizeU * MAPWIDTH && mousePosView.y <= gridSizeU * MAPHEIGHT)
    {
        mousePosGrid.x = mousePosView.x / gridSizeF;
        mousePosGrid.y = mousePosView.y / gridSizeF;
    }


    //ui 뷰(타일 샘플) 그리드
    if (mousePosView2.x >= 0.f && mousePosView2.y >= 0.f && mousePosView2.x < 960.f && mousePosView2.y < 960.f)
    {
        mousePosGrid2.x = mousePosView2.x / (gridSizeF * 5.f);
        mousePosGrid2.y = mousePosView2.y / (gridSizeF * 5.f);
    }

    //타일 그리기 
    if (InputManager::GetMouseButtonDown(Mouse::Button::Left) && currentInputState == InputState::BLOCK && CurrentMousePosition)
    {
        finalGrid.clear();
        downGrid = mousePosGrid;
        std::cout << "DGrid : " << downGrid.x << " " << downGrid.y << "\n";

        drag = new RectangleShape(Vector2f(0.f, 0.f));
        drag->setFillColor({ 100, 100, 200, 125 });
        drag->setPosition(downGrid.x * gridSizeF, downGrid.y * gridSizeF);
    }

    if (InputManager::GetMouseButton(Mouse::Button::Left) && currentInputState == InputState::BLOCK && CurrentMousePosition)
    {
        drag->setSize(Vector2f(((int)mousePosGrid.x - (int)downGrid.x) * gridSizeF, ((int)mousePosGrid.y - (int)downGrid.y) * gridSizeF));

        if (((int)mousePosGrid.x - (int)downGrid.x) >= 0)
        {
            drag->setSize(Vector2f(drag->getSize().x + gridSizeF, drag->getSize().y));
        }

        if (((int)mousePosGrid.y - (int)downGrid.y) >= 0)
        {
            drag->setSize(Vector2f(drag->getSize().x, drag->getSize().y + gridSizeF));
        }
    }
    switch (currentInputState)
    {
    case::InputState::IMAGE:
        if (InputManager::GetMouseButtonDown(Mouse::Button::Left))
        {
            //타일 선택
            int count = 0;
            if (!CurrentMousePosition)
            {
                for (int x = 0; x <= 5; x++)
                {
                    for (int y = 0; y <= 5; y++)
                    {
                        if (mousePosGrid2.x == x && mousePosGrid2.y == y)
                        {
                            currentIndex = count;
                            break;
                        }
                        else
                        {
                            count++;
                        }
                    }
                }
            }
        }
        if (InputManager::GetMouseButton(Mouse::Button::Left) && CurrentMousePosition)
        {
            CreateTile(mousePosGrid.x, mousePosGrid.y, currentIndex);
        }
        if (InputManager::GetMouseButton(Mouse::Button::Right) && CurrentMousePosition)
        {
            downGrid = mousePosGrid;
            CreateTile(mousePosGrid.x, mousePosGrid.y, 5);
        }
        break;
    case::InputState::BLOCK:
        if (InputManager::GetMouseButtonUp(Mouse::Button::Left))
        {
            ColliderRect *block = new ColliderRect(drag->getGlobalBounds(), downGrid);
            rects.push_back(block);

            upGrid = mousePosGrid;

            CreateBlocks(downGrid.x, upGrid.x, downGrid.y, upGrid.y);
        }
        break;
    }
    //화면 나누기
    tileView->setViewport(sf::FloatRect(0.f, 0.f, 0.5f, 1.f));
    uiView->setViewport(sf::FloatRect(0.5f, 0.f, 0.5f, 1.f));

    //게임 요소 추가 
    if (mousePosWindow.x <= 960.f)
    {
        tileSelector.setPosition(mousePosGrid.x * gridSizeF, mousePosGrid.y * gridSizeF);
    }
    else if (mousePosWindow.x > 960.f)
    {
        CurrentMousePosition = false;
        sampleSelector.setPosition(mousePosGrid2.x * gridSizeF * 5.f, mousePosGrid2.y * gridSizeF * 5.f);
    }

    //UI 업데이트
    std::stringstream ss;

    ss  << "Screen: " << mousePosScreen.x << " " << mousePosScreen.y << "\n"
        << "Window: " << mousePosWindow.x << " " << mousePosWindow.y << "\n"
        << "View: " << mousePosView.x << " " << mousePosView.y << "\n"
        << "Grid: " << mousePosGrid.x << " " << mousePosGrid.y << "\n";

    std::stringstream ss1;

    ss1 << "Screen: " << mousePosScreen.x << " " << mousePosScreen.y << "\n"
        << "Window: " << mousePosWindow.x << " " << mousePosWindow.y << "\n"
        << "View: " << mousePosView2.x << " " << mousePosView2.y << "\n"
        << "Grid: " << mousePosGrid2.x << " " << mousePosGrid2.y << "\n"
        << "CurrentIndex: " << currentIndex << "\n";

    text.setString(ss.str());
    text2.setString(ss1.str());
}

void SceneMapEditor::Draw(sf::RenderWindow *window, View *mainView, View *uiView)
{
    window->setView(*tileView);
    window->draw(spriteBackground);
    for (int x = 0; x < MAPWIDTH; x++)
    {
        for (int y = 0; y < MAPHEIGHT; y++)
        {
            window->draw(tileMap[x][y]);
        }
    }
    for (auto blockshape : rects)
    {
        window->draw(blockshape->GetRectShape());
    }
    window->draw(palette, ResourceMgr::instance()->GetTexture("TILETEX"));
    window->draw(text);
    if (CurrentMousePosition)
    {
        window->draw(tileSelector);
    }
    if (InputManager::GetMouseButton(Mouse::Button::Left) && currentInputState == InputState::BLOCK)
    {
        window->draw(*drag);
    }

    window->setView(*(this->uiView));
    window->draw(spriteBackground);
    window->draw(spriteTile);
    window->draw(text2);
    if (!CurrentMousePosition)
    {
        window->draw(sampleSelector);
    }
    window->setView(*tileView);
}


