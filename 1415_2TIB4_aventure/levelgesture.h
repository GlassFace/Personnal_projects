
void LoadLevel(char grid[][14], TGfxFile *level);		// Loading level from level.txt

void CreateGround(TGfxTexture *groundset, char grid[][14], TGfxSprite *groundtiles[15], int TILE, float screensizey);	// Creating level (ground only for now) from screen grid infos