#include "flib.h"


void LoadLevel(char grid[][14], TGfxFile *level)
{
	int i = 0;
	int j = 0;

	unsigned char charread = 0;

	level = GfxFileOpenRead("level.txt");
	
	if (level != nullptr)
	{
		while (charread != 'e')
		{
			charread = GfxFileReadChar(level);
			

			if (charread == '0')
			{
				grid[i][j] = '0';
			}

			else if (charread == '1')
			{
				grid[i][j] = '1';
			}

			else if (charread == '2')
			{
				grid[i][j] = '2';
			}

			else if (charread == 'l')
			{
				i++;
				j = 0;
			}

			if (j < 14 && charread != 'l')
			{
				j++;
			}
		}
	}
}


void CreateGround(TGfxTexture *groundset, char grid[][14], TGfxSprite *groundtiles[15], int TILE, float screensizey)
{
	int i = 0;

	for (i = 0; i < 15; i++)
	{
		switch (grid[8][i])
		{
		case '1':
			groundtiles[i] = GfxSpriteCreate(groundset);									// Creating ground sprite
			GfxSpriteSetCutout(groundtiles[i], 0 * TILE, 0 * TILE, TILE, TILE);				// Picking ground sprite on tileset
			GfxSpriteSetPosition(groundtiles[i], float(i * TILE), float((screensizey - 1) * TILE));		// Placing ground

			break;

		case '2':
			groundtiles[i] = GfxSpriteCreate(groundset);									// Creating water sprite
			GfxSpriteSetCutout(groundtiles[i], 1 * TILE, 0 * TILE, TILE, TILE);				// Picking water sprite on tileset
			GfxSpriteSetPosition(groundtiles[i], float(i * TILE), float((screensizey - 1) * TILE));		// Placing water
		}
	}
}