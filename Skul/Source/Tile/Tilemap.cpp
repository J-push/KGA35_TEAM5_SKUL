#include "Tilemap.h"

Tilemap::Tilemap()
{
	backGround.width = BACKGROUND_WIDTH;
	backGround.height = BACKGROUND_HEIGHT;
}

void Tilemap::CreateGrass()
{
}

void Tilemap::CreateWall()
{
}

int Tilemap::CreateBackGround()
{
	int cols = backGround.width / TILE_SIZE;
	int rows = backGround.height / TILE_SIZE;

	tileMap.setPrimitiveType(Quads);
	tileMap.resize(cols * rows * VERTS_IN_QUAD);

	int index = 0;

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

			int texIndex = 
			if (r == 0 || r == rows - 1 || c == 0 || c == cols - 1)
			{
				texIndex = 3;
			}
			float offset = texIndex * TILE_SIZE;
			tileMap[vertexIndex + 0].texCoords = Vector2f(0.f, offset);
			tileMap[vertexIndex + 1].texCoords = Vector2f(TILE_SIZE, offset);
			tileMap[vertexIndex + 2].texCoords = Vector2f(TILE_SIZE, offset + TILE_SIZE);
			tileMap[vertexIndex + 3].texCoords = Vector2f(0.f, offset + TILE_SIZE);
		}
	}
}

Tilemap::~Tilemap()
{
}
