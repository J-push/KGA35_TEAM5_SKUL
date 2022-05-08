#include "Tilemap.h"

/**********************************************************
* 설명 : 전체 맵 길이와 높이 초기 설정, 타일 샘플 사진에 접근.
***********************************************************/
void Tilemap::Init()
{
    backGround.width = BACKGROUND_WIDTH;
    backGround.height = BACKGROUND_HEIGHT;
    CreateTestRect();
    spriteTile.setTexture(*ResourceMgr::instance()->GetTexture("TILETEX"));
}

/**********************************************************
* 설명 : 더미맵 만드는 과정이다. 전체 맵(3200x3200) tile 사이즈(32)로 나누어 세부적으로 분리하였고
* 가로길이는 cols , 세로길이는 rows이다. 위치에 따라 무슨 타일로 할 것인지 정했다고 인지하면 되겠다.
* vertexIndex 아래 부분 부턴 타일 샘플사진에 대한 코드이다. texIndex -> 타일 샘플사진 인덱스번호
* 첫번째 타일이 index -> 0이고 , 아래로 내려갈수록 index번호가 올라가는 방식인데, 해당 열의 마지막 타일인 경우, 다음 열로 이동해야하므로 조건을 걸어주었다.
***********************************************************/
int Tilemap::CreateBackGround()
{
    int cols = backGround.width / TILE_SIZE;
    int rows = backGround.height / TILE_SIZE;

    tileMap.setPrimitiveType(Quads);
    tileMap.resize(cols * rows * VERTS_IN_QUAD * 3);

    for (int r = 0; r < rows; ++r)
    {
        for (int c = 0; c < cols; ++c)
        {
            int index = r * cols + c;

            float x = c * TILE_SIZE;
            float y = r * TILE_SIZE;

            int vertexIndex = index * VERTS_IN_QUAD;

            tileMap[vertexIndex + 0].position = Vector2f(x, y);  
            tileMap[vertexIndex + 1].position = Vector2f(x + TILE_SIZE, y);
            tileMap[vertexIndex + 2].position = Vector2f(x + TILE_SIZE, y + TILE_SIZE);
            tileMap[vertexIndex + 3].position = Vector2f(x, y + TILE_SIZE);

            texIndex = 5;
            if (texIndex == 0 || texIndex == 1 || texIndex == 4 || texIndex == 6 || texIndex == 7 || texIndex == 31)
            {
                TileType::Ground;
            }
            else if (texIndex == 2)
            {
                TileType::Null;
            }
            else if (texIndex == 3 || texIndex == 9 || texIndex == 15 || texIndex == 24)
            {
                TileType::HalfGround;
            }
            else if (texIndex == 27 || texIndex == 25 || texIndex == 18 || texIndex == 13 || texIndex == 12)
            {
                TileType::Wall;
            }
            else if (texIndex == 5)
            {
                TileType::None;
            }
            //r , c 값에 따른 타일 샘플 세팅
            if (r <= 25 && c <= 3)
            {
                texIndex = 2;
            }
            else if (r == 25 && c == 5)
            {
                texIndex = 31;
            }
            else if (r < 25 && c == 4)
            {
                texIndex = 18;
            }
            else if (r == 25 && c == 4)
            {
                texIndex = 27;
            }
            else if (r == 25 && c > 5)
            {
                texIndex = 6;
                if (c == 35)
                {
                    texIndex = 4;
                }
                if (c > 35 && c < 50)
                {
                    texIndex = 5;
                }
                if (c == 36 && r == 28)
                {
                    texIndex = 0;
                }
                if (c == 50)
                {
                    texIndex = 31;
                }
            }
            else if (r > 25 && r < 35)
            {
                texIndex = 2;
                if (r >= 26 && r <= 28 && c == 35)
                {
                    texIndex = 27;
                }
                if (c > 35 && c < 50 && r < 28 )
                {
                    texIndex = 5;
                }
                if (c > 35 && c < 50 && r == 28)
                {
                    texIndex = 6;
                }
                if (r == 28 && c == 35)
                {
                    texIndex = 27;
                }
                if (r >= 26 && r <= 28 && c == 50)
                {
                    texIndex = 27;
                }
                if (r == 28 && c == 49)
                {
                    texIndex = 4;
                }
                if (r == 28 && c == 36)
                {
                    texIndex = 31;
                }
            }
            else if (r == 22 && c ==25)
            {
                texIndex = 3;
            }
            else if (r == 22 && c > 25 && c < 35)
            {
                texIndex = 15;
            }
            else if (r == 22 && c == 35)
            {
                texIndex = 9;
            }
            float offset = texIndex * TILE_SIZE;
            tileMap[vertexIndex + 0].texCoords = Vector2f(TILE_SIZE * 0, offset);
            tileMap[vertexIndex + 1].texCoords = Vector2f(TILE_SIZE * 1, offset);
            tileMap[vertexIndex + 2].texCoords = Vector2f(TILE_SIZE * 1, offset + TILE_SIZE);
            tileMap[vertexIndex + 3].texCoords = Vector2f(TILE_SIZE * 0, offset + TILE_SIZE);

            //texIndex 열의 마지막 부분일 떄
            if (5 < texIndex && texIndex <= 11)
            {
                float offset = (texIndex - 6) * TILE_SIZE;
                tileMap[vertexIndex + 0].texCoords = Vector2f(TILE_SIZE * 1, offset);
                tileMap[vertexIndex + 1].texCoords = Vector2f(TILE_SIZE * 2, offset);
                tileMap[vertexIndex + 2].texCoords = Vector2f(TILE_SIZE * 2, offset + TILE_SIZE);
                tileMap[vertexIndex + 3].texCoords = Vector2f(TILE_SIZE * 1, offset + TILE_SIZE);
            }
            if (11 < texIndex && texIndex <= 17)
            {
                float offset = (texIndex - 12) * TILE_SIZE;
                tileMap[vertexIndex + 0].texCoords = Vector2f(TILE_SIZE * 2, offset);
                tileMap[vertexIndex + 1].texCoords = Vector2f(TILE_SIZE * 3, offset);
                tileMap[vertexIndex + 2].texCoords = Vector2f(TILE_SIZE * 3, offset + TILE_SIZE);
                tileMap[vertexIndex + 3].texCoords = Vector2f(TILE_SIZE * 2, offset + TILE_SIZE);
            }
            if (17 < texIndex && texIndex <= 23)
            {
                float offset = (texIndex - 18) * TILE_SIZE;
                tileMap[vertexIndex + 0].texCoords = Vector2f(TILE_SIZE * 3, offset);
                tileMap[vertexIndex + 1].texCoords = Vector2f(TILE_SIZE * 4, offset);
                tileMap[vertexIndex + 2].texCoords = Vector2f(TILE_SIZE * 4, offset + TILE_SIZE);
                tileMap[vertexIndex + 3].texCoords = Vector2f(TILE_SIZE * 3, offset + TILE_SIZE);
            }
            if (23 < texIndex && texIndex <= 29)
            {
                float offset = (texIndex - 24) * TILE_SIZE;
                tileMap[vertexIndex + 0].texCoords = Vector2f(TILE_SIZE * 4, offset);
                tileMap[vertexIndex + 1].texCoords = Vector2f(TILE_SIZE * 5, offset);
                tileMap[vertexIndex + 2].texCoords = Vector2f(TILE_SIZE * 5, offset + TILE_SIZE);
                tileMap[vertexIndex + 3].texCoords = Vector2f(TILE_SIZE * 4, offset + TILE_SIZE);
            }
            if (29 < texIndex && texIndex <= 35)
            {
                float offset = (texIndex - 30) * TILE_SIZE;
                tileMap[vertexIndex + 0].texCoords = Vector2f(TILE_SIZE * 5, offset);
                tileMap[vertexIndex + 1].texCoords = Vector2f(TILE_SIZE * 6, offset);
                tileMap[vertexIndex + 2].texCoords = Vector2f(TILE_SIZE * 6, offset + TILE_SIZE);
                tileMap[vertexIndex + 3].texCoords = Vector2f(TILE_SIZE * 5, offset + TILE_SIZE);
            }
        }
    }
    return cols * rows;
}

void Tilemap::CreateTestRect()
{
    for (auto v : rects)
    {
        delete v;
    }

    rects.clear();

   // 왼쪽벽
    TestRectangle *rect1 = new TestRectangle(64.f, 540.f, 128.f, 1080.f);
    rects.push_back(rect1);
    //지형
    TestRectangle *rect2 = new TestRectangle(630.f, 982.f, 1042.f, 360.f);
    rects.push_back(rect2);
    //낮은지형
    TestRectangle *rect3 = new TestRectangle(1374.f, 987.f, 448.f, 176.f);  //1120 top, 888 left, 1568 width, 1080 height
    rects.push_back(rect3);
    //오른쪽 끝 지형
    TestRectangle *rect4 = new TestRectangle(1776.f, 954.f, 354.f, 308.f);
    rects.push_back(rect4);
    //위에 떠있는 지형
    TestRectangle *rect5 = new TestRectangle(992, 714, 320, 16);
    rects.push_back(rect5);
}

std::vector<TestRectangle*> Tilemap::GetRects()
{
    return rects;   
}

/**********************************************************
* 설명 : 샘플 사진을 이용하여 tileMap을 그려준다. (게임씬에는 이 draw함수를 호출)
***********************************************************/
void Tilemap::Draw(sf::RenderWindow *window)
{
    for (auto rects : rects)
    {
        window->draw(rects->GetRectShape());
    }
    window->draw(tileMap, ResourceMgr::instance()->GetTexture("TILETEX"));
}