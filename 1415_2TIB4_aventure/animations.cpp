#include "flib.h"
#include "animations.h"

const int TILE = 32;		// Tiles size

const int XSCREENLENGHT = 15;	// Number of tiles on x

int waterdelay = 0;


void AnimateWater(char grid[][15], TGfxSprite *groundcase[15])		// Animate water
{
	int i = 0;

	for (i = 0; i < XSCREENLENGHT; i++)
	{
		if (grid[9][i] == '2')								// If there is water at this ground tile...
		{
			if (waterdelay < 10)
			{
				GfxSpriteSetCutout(groundcase[i], 1 * TILE, 0 * TILE, TILE, TILE);	// First frame
			}
			else if (waterdelay < 20)
			{
				GfxSpriteSetCutout(groundcase[i], 2 * TILE, 0 * TILE, TILE, TILE);	// Second frame
			}
		}
	}


	(waterdelay)++;

	if (waterdelay == 20)			// Reinitializing water animation delay if 20 frames passed
	{
		waterdelay = 0;
	}
}