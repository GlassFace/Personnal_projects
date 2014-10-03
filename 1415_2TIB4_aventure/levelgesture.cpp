#include "flib.h"

const int TILE = 32;		// Tiles size

const int XSCREENLENGHT = 15;	// Number of tiles on x


void LoadLevel(char grid[][15], TGfxFile *level)	// Loading level from level.txt
{
	int i = 0;
	int j = 0;

	unsigned char charread = 0;

	level = GfxFileOpenRead("level.txt");		// Opening level.txt


	
	if (level != nullptr)		// If opening level.txt succeeded
	{
		while (charread != 'e')		// While file not ended
		{
			charread = GfxFileReadChar(level);		// Read character
			

			if (charread == '0')		// Nothing at this case
			{
				grid[i][j] = '0';
			}

			else if (charread == '1')	// Ground at this case
			{
				grid[i][j] = '1';
			}

			else if (charread == '2')	// Water at this case
			{
				grid[i][j] = '2';
			}

			else if (charread == ' ')	// End of line
			{
				i++;
				j = 0;
			}


			if (j < XSCREENLENGHT && charread != ' ')	// Next collumn
			{
				j++;
			}
		}

		

		GfxFileClose(level);		// Closing file
	}

	else
	{
		GfxDbgPrintf("Opening level.txt failed for some reason.\n");		// Error output if file failed to be opened

		GfxExitRequest();
	}
}


void CreateGround(TGfxTexture *groundset, char grid[][15], TGfxSprite *groundtiles[15], float screensizey)	// Creating level (ground only for now) from screen grid infos
{
	int i = 0;

	for (i = 0; i < XSCREENLENGHT; i++)		// Checking every floor case to create appropriate ground
	{
		switch (grid[9][i])
		{
		case '1':		// If tile should be ground
			groundtiles[i] = GfxSpriteCreate(groundset);												// Creating ground sprite
			GfxSpriteSetCutout(groundtiles[i], 0 * TILE, 0 * TILE, TILE, TILE);							// Picking ground sprite on tileset
			GfxSpriteSetPosition(groundtiles[i], float(i * TILE), float((screensizey - 1) * TILE));		// Placing ground

			break;

		case '2':		// If tile should be water
			groundtiles[i] = GfxSpriteCreate(groundset);												// Creating water sprite
			GfxSpriteSetCutout(groundtiles[i], 1 * TILE, 0 * TILE, TILE, TILE);							// Picking water sprite on tileset
			GfxSpriteSetPosition(groundtiles[i], float(i * TILE), float((screensizey - 1) * TILE));		// Placing water
		}
	}
}