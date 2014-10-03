#include "flib.h"


void AnimateWater(char grid[][14], TGfxSprite *groundcase[14], int *waterdelay, const int TILE)		// Animate water
{
	int i = 0;

	for (i = 0; i < 15; i++)
	{
		if (grid[8][i] == '2')								// If there is water at this ground tile...
		{
			if (*waterdelay < 10)
			{
				GfxSpriteSetCutout(groundcase[i], 1 * TILE, 0 * TILE, TILE, TILE);	// First frame
			}
			else if (*waterdelay < 20)
			{
				GfxSpriteSetCutout(groundcase[i], 2 * TILE, 0 * TILE, TILE, TILE);	// Second frame
			}
		}
	}


	(*waterdelay)++;

	if (*waterdelay == 20)			// Reinitializing water animation delay if 20 frames passed
	{
		*waterdelay = 0;
	}
}