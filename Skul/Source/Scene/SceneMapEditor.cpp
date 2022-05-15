#include "SceneMapEditor.h"
#include "../Manager/ResourceMgr.h"
#include "../TileMap/csvfile.h"

int SceneMapEditor::CreateTile(int c, int r, int idx)
{
    int cols = mapWidth;
    int rows = mapHeight;

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
            texIndex = 5;
            texIndex = idx;

            float offset = texIndex * gridSizeF;
            palette[vertexIndex + 0].texCoords = Vector2f(gridSizeF * 0, offset);
            palette[vertexIndex + 1].texCoords = Vector2f(gridSizeF * 1, offset);
            palette[vertexIndex + 2].texCoords = Vector2f(gridSizeF * 1, offset + gridSizeF);
            palette[vertexIndex + 3].texCoords = Vector2f(gridSizeF * 0, offset + gridSizeF);

            
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

void SceneMapEditor::CreateRects()
{
    ColliderRect *rect = new ColliderRect(drag->getGlobalBounds(), downGrid);
    rects.push_back(rect);
    cout << rect->GetRect().top << " " << rect->GetRect().left << " " << rect->GetRect().width << " " << rect->GetRect().height << "\n";
}

void SceneMapEditor::DeleteRects()
{
    rects.pop_back();
}

void SceneMapEditor::MoveMap(float dt)
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
}

void SceneMapEditor::SetView(RenderWindow *window)
{
    tileView->setViewport(sf::FloatRect(0.f, 0.f, 0.5f, 1.f));
    uiView->setViewport(sf::FloatRect(0.5f, 0.f, 0.5f, 1.f));

    mousePosScreen = Mouse::getPosition();
    mousePosWindow = Mouse::getPosition(*window);

    const View &temp = window->getView();

    window->setView(*tileView);
    
    if (mousePosView.x >= 0.f && mousePosView.y >= 0.f && mousePosView.x <= gridSizeU * mapWidth && mousePosView.y <= gridSizeU * mapHeight)
    {
        mousePosGrid.x = mousePosView.x / gridSizeF;
        mousePosGrid.y = mousePosView.y / gridSizeF;
    }

    if (mousePosView2.x >= 0.f && mousePosView2.y >= 0.f && mousePosView2.x < 960.f && mousePosView2.y < 960.f)
    {
        mousePosGrid2.x = mousePosView2.x / (gridSizeF * 5.f);
        mousePosGrid2.y = mousePosView2.y / (gridSizeF * 5.f);
    }
    if (mousePosWindow.x < 960.f)
    {
        mousePosView = window->mapPixelToCoords(mousePosWindow);
        currentMousePosition = true;
        mousePosView2.x = 0;
        mousePosView2.y = 0;

    }
    window->setView(*uiView);
    if (mousePosWindow.x >= 960.f)
    {
        mousePosView2 = window->mapPixelToCoords(mousePosWindow);
        currentMousePosition = false;
        mousePosView.x = 0;
        mousePosView.y = 0;
    }

    window->setView(temp);
    
    if (mousePosWindow.x <= 960.f)
    {
        tileSelector.setPosition(mousePosGrid.x * gridSizeF, mousePosGrid.y * gridSizeF);
    }
    else if (mousePosWindow.x > 960.f)
    {
        currentMousePosition = false;
        sampleSelector.setPosition(mousePosGrid2.x * gridSizeF * 5.f, mousePosGrid2.y * gridSizeF * 5.f);
    }

    
    std::stringstream ss;

    ss << "Screen: " << mousePosScreen.x << " " << mousePosScreen.y << "\n"
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

void SceneMapEditor::ChangeMode()
{
    if (InputManager::GetKeyDown(Keyboard::B))
    {
        currentInputState = InputState::BLOCK;
    }
    if (InputManager::GetKeyDown(Keyboard::I))
    {
        currentInputState = InputState::IMAGE;
    }
}

void SceneMapEditor::Init()
{
    //LoadRect();
    //LoadImage();
    currentState = true;
    currentMousePosition = true;
    currentInputState = InputState::IMAGE;
    gridSizeU =static_cast<unsigned>(gridSizeF);

    tileMap.resize(mapWidth, vector<RectangleShape>());
    for (int i = 0; i < mapWidth; i++)
    {
        tileMap[i].resize(mapHeight, RectangleShape());
        for (int j = 0; j < mapHeight; j++)
        {
            tileMap[i][j].setSize(Vector2f(gridSizeF, gridSizeF));
            tileMap[i][j].setFillColor(Color::White);
            tileMap[i][j].setOutlineThickness(1.f);
            tileMap[i][j].setOutlineColor(Color::Black);
            tileMap[i][j].setPosition(i * gridSizeF, j * gridSizeF);
        }
    }
    tileSelector.setSize(Vector2f(gridSizeF, gridSizeF));
    tileSelector.setFillColor(sf::Color::Transparent);
    tileSelector.setOutlineThickness(1.f);
    tileSelector.setOutlineColor(sf::Color::Red);

    
    sampleSelector.setSize(Vector2f(gridSizeF * 5, gridSizeF * 5));
    sampleSelector.setFillColor(sf::Color::Transparent);
    sampleSelector.setOutlineThickness(1.f);
    sampleSelector.setOutlineColor(sf::Color::Blue);

    
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

void SceneMapEditor::Update(float dt, RenderWindow *window, View *mainView)
{
    ChangeMode();
    MoveMap(dt);
    SetView(window);
    switch (currentInputState)
    {
    case::InputState::IMAGE:
        if (InputManager::GetMouseButtonDown(Mouse::Button::Left))
        {
            
            int count = 0;
            if (!currentMousePosition)
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
        if (InputManager::GetMouseButton(Mouse::Button::Left) && currentMousePosition)
        {
            CreateTile(mousePosGrid.x, mousePosGrid.y, currentIndex);
            cout << "Gridx : " << mousePosGrid.x << " " << "Gridy : " << mousePosGrid.y << " " << "index : " << currentIndex << "\n";
        }
        if (InputManager::GetMouseButton(Mouse::Button::Right) && currentMousePosition)
        {
            downGrid = mousePosGrid;
            CreateTile(mousePosGrid.x, mousePosGrid.y, 5);
        }
        break;
    case::InputState::BLOCK:
        if (InputManager::GetMouseButtonDown(Mouse::Button::Left) && currentMousePosition)
        {
            finalGrid.clear();
            downGrid = mousePosGrid;
            std::cout << "DGrid : " << downGrid.x << " " << downGrid.y << "\n";

            drag = new RectangleShape(Vector2f(0.f, 0.f));
            drag->setFillColor({ 100, 100, 200, 125 });
            drag->setPosition(downGrid.x * gridSizeF, downGrid.y * gridSizeF);
        }

        if (InputManager::GetMouseButton(Mouse::Button::Left) && currentMousePosition)
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

            if (((int)mousePosGrid.x - (int)downGrid.x) < 0)
            {
                drag->setSize(Vector2f(drag->getSize().x, drag->getSize().y));
            }

            if (((int)mousePosGrid.y - (int)downGrid.y) < 0)
            {
                drag->setSize(Vector2f(drag->getSize().x, drag->getSize().y));
            }
        }
        if (InputManager::GetMouseButtonUp(Mouse::Button::Left))
        {
            CreateRects();

            delete drag;
            upGrid = mousePosGrid;
            std::cout << "UGrid : " << upGrid.x << " " << upGrid.y << "\n";
        }
        if (InputManager::GetMouseButtonDown(Mouse::Button::Left) && !currentMousePosition)
        {
            currentInputState = InputState::IMAGE;
        }
        if (InputManager::GetMouseButtonDown(Mouse::Button::Right) && currentMousePosition)
        {
            finalGrid.clear();
            downGrid = mousePosGrid;
            drag = new RectangleShape(Vector2f(0.f, 0.f));
            drag->setFillColor({ 100, 100, 200, 125 });
            drag->setPosition(downGrid.x * gridSizeF, downGrid.y * gridSizeF);
        }

        if (InputManager::GetMouseButton(Mouse::Button::Right) && currentMousePosition)
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

            if (((int)mousePosGrid.x - (int)downGrid.x) < 0)
            {
                drag->setSize(Vector2f(drag->getSize().x, drag->getSize().y));
            }

            if (((int)mousePosGrid.y - (int)downGrid.y) < 0)
            {
                drag->setSize(Vector2f(drag->getSize().x, drag->getSize().y));
            }
        }
        if (InputManager::GetMouseButtonUp(Mouse::Button::Right))
        {
            DeleteRects();

            delete drag;
            upGrid = mousePosGrid;
        }
        break;
    }
    if (InputManager::GetKeyDown(Keyboard::L))
    {
        LoadRect();
        LoadImage();
    }
}

void SceneMapEditor::Draw(sf::RenderWindow *window, View *mainView, View *uiView)
{
    window->setView(*tileView);
    for (int x = 0; x < mapWidth; x++)
    {
        for (int y = 0; y < mapHeight; y++)
        {
            window->draw(tileMap[x][y]);
        }
    }
    window->draw(text);
    
    for (auto blockshape : rects)
    {
        window->draw(blockshape->GetRectShape());
    }

    if (InputManager::GetMouseButton(Mouse::Button::Left) && currentInputState == InputState::BLOCK)
    {
        window->draw(*drag);
    }

    window->draw(palette, ResourceMgr::instance()->GetTexture("TILETEX"));

    if (currentMousePosition)
    {
        window->draw(tileSelector);
    }

    window->setView(*(this->uiView));
    window->draw(spriteBackground);
    window->draw(spriteTile);
    window->draw(text2);
    if (!currentMousePosition)
    {
        window->draw(sampleSelector);
    }
    window->setView(*tileView);
}

void SceneMapEditor::InitMapData()
{
    rapidcsv::Document dataFile("data_tables/maps/Map_data.csv");
    std::vector<string> colId = dataFile.GetColumn<string>("mapId");
    std::vector<int> colWidth = dataFile.GetColumn<int>("mapWidth");
    std::vector<int> colHeight = dataFile.GetColumn<int>("mapHeight");

    this->mapWidth = colWidth[0];
    this->mapHeight = colHeight[0];
}

VertexArray SceneMapEditor::Getpalette()
{
    return palette;
}

vector<ColliderRect *> SceneMapEditor::Getrects()
{
    return rects;
}

vector<vector<RectangleShape>> SceneMapEditor::Gettile()
{
    return tileMap;
}

void SceneMapEditor::LoadRect()
{
    rapidcsv::Document dataFile("data_tables/maps/Stage1_mapRect_data.csv");

    std::vector<string> colId = dataFile.GetColumn<string>("Rect");
    std::vector<int> colTop = dataFile.GetColumn<int>("T");
    std::vector<int> colLeft = dataFile.GetColumn<int>("L");
    std::vector<int> colWidth = dataFile.GetColumn<int>("W");
    std::vector<int> colHeight = dataFile.GetColumn<int>("H");

    int totalRects = colId.size();

    for (int i = 0; i < totalRects; ++i)
    {
        ColliderRect *rect = new ColliderRect(colTop[i], colLeft[i], colWidth[i], colHeight[i]);
        rects.push_back(rect);
    }
}

void SceneMapEditor::LoadImage()
{
    rapidcsv::Document dataFile("data_tables/maps/Stage1_mapTile_data.csv");

    std::vector<string> colId = dataFile.GetColumn<string>("Tile");
    std::vector<int> colcol = dataFile.GetColumn<int>("cols");
    std::vector<int> colrow = dataFile.GetColumn<int>("rows");
    std::vector<int> colindex = dataFile.GetColumn<int>("index");

    int totalTiles = colId.size();
    for (int i = 0; i < totalTiles; ++i)
    {
        CreateTile(colcol[i], colrow[i], colindex[i]);
    }
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
