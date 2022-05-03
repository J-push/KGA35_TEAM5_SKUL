#include "Tilemap.h"

void Tilemap::Init()
{
    backGround.width = BACKGROUND_WIDTH;
    backGround.height = BACKGROUND_HEIGHT;
    spriteTile.setTexture(*ResourceMgr::instance()->GetTexture("TILETEX"));
}


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

            tileMap[vertexIndex + 0].position = Vector2f(x, y);    // »ç°¢ÇüÀÇ ¸Ç ÁÂ»ó´Ü ÁÂÇ¥
            tileMap[vertexIndex + 1].position = Vector2f(x + TILE_SIZE, y);
            tileMap[vertexIndex + 2].position = Vector2f(x + TILE_SIZE, y + TILE_SIZE);
            tileMap[vertexIndex + 3].position = Vector2f(x, y + TILE_SIZE);

            int texIndex = 5;
            if (r == 25 && c == 0)
            {
                texIndex = 0;
            }
            else if (r == 25 && c > 0)
            {
                texIndex = 6;
            }
            else if (r > 25 && r < 35)
            {
                texIndex = 2;
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

void Tilemap::Draw(sf::RenderWindow *window)
{
    window->draw(tileMap, ResourceMgr::instance()->GetTexture("TILETEX"));
}