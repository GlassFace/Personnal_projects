
#include "flib.h"
#include "levelgesture.h"


const float TILE = 32;		// Tiles size

const int XSCREENLENGHT = 16;	// Number of tiles on x
const int YSCREENLENGHT = 11;


void LoadLevel(char grid[11][16], int tilenumber[11][16])	// Loading level from level.txt
{
	int i = 0;
	int j = 0;
	int e = 0;

	unsigned char charread = 0;

	TGfxFile * level = nullptr;			// File* for level.txt

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

			else if (charread == '0')
			{
				grid[i][j] = '0';

				tilenumber[i][j] = e;

				e++;
			}

			else if (charread == '1')	// Ground at this case
			{
				grid[i][j] = '1';

				tilenumber[i][j] = e;

				e++;
			}

			else if (charread == '2')	// Water at this case
			{
				grid[i][j] = '2';

				tilenumber[i][j] = e;

				e++;
			}

			else if (charread == ' ')	// End of line
			{
				i++;
				j = 0;
			}

			if (j < (XSCREENLENGHT - 1) && charread != ' ')	// Next collumn
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


void CreateGround(TGfxTexture *groundset, char grid[11][16], TGfxSprite *groundtiles[20])	// Creating level (ground only for now) from screen grid infos
{
	int i = 0;
	int j = 0;
	int e = 0;

	for (i = 0; i < (YSCREENLENGHT); i++)		// Checking every floor case to create appropriate ground
	{
		for (j = 0; j < (XSCREENLENGHT); j++)
		{
			switch (grid[i][j])
			{
			case '1':		// If tile should be ground
				groundtiles[e] = GfxSpriteCreate(groundset);												// Creating ground sprite
				GfxSpriteSetCutout(groundtiles[e], int(0 * TILE), int(0 * TILE), int(TILE), int(TILE));							// Picking ground sprite on tileset
				GfxSpriteSetPosition(groundtiles[e], float(j * TILE), float(i * TILE));		// Placing ground

				e++;

				break;

			case '2':		// If tile should be water
				groundtiles[e] = GfxSpriteCreate(groundset);												// Creating water sprite
				GfxSpriteSetCutout(groundtiles[e], int(1 * TILE), int(0 * TILE), int(TILE), int(TILE));							// Picking water sprite on tileset
				GfxSpriteSetPosition(groundtiles[e], float(j * TILE), float(i * TILE));		// Placing water

				e++;

				break;
			}
		}
	}
}