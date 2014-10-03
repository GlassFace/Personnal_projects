#include "flib.h"


void AnimateWater(TGfxSprite *watersprite, int waterdelay, int TILE)		// Animate water
{
	if (waterdelay < 10)
	{
		GfxSpriteSetCutout(watersprite, 1 * TILE, 0 * TILE, TILE, TILE);	// First frame
	}
	else if (waterdelay < 20)
	{
		GfxSpriteSetCutout(watersprite, 2 * TILE, 0 * TILE, TILE, TILE);	// Second frame
	}
}