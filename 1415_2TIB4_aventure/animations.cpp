#include "flib.h"
#include "animations.h"

const float TILE = 32;		// Tiles size

const int XSCREENLENGHT = 16;	// Number of tiles on x
const int YSCREENLENGHT = 11;

int waterdelay = 0;


void AnimateWater(char grid[11][16], TGfxSprite *groundcase[20], const int tilenumber[11][16])		// Animate water
{
	int i = 0;
	int j = 0;

	for (i = 0; i < (YSCREENLENGHT); i++)
	{
		for (j = 0; j < (XSCREENLENGHT); j++)
		{
			if (grid[i][j] == '2')								// If there is water at this ground tile...
			{
				if (waterdelay < 10)
				{
					GfxSpriteSetCutout(groundcase[tilenumber[i][j]], int(1 * TILE), int(0 * TILE), int(TILE), int(TILE));	// First frame
				}
				else if (waterdelay < 20)
				{
					GfxSpriteSetCutout(groundcase[tilenumber[i][j]], int(2 * TILE), int(0 * TILE), int(TILE), int(TILE));	// Second frame
				}
			}
		}
	}


	(waterdelay)++;

	if (waterdelay == 20)			// Reinitializing water animation delay if 20 frames passed
	{
		waterdelay = 0;
	}
}