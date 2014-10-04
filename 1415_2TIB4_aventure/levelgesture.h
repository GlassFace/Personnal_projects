
void LoadLevel(char grid[][15]);		// Loading level from level.txt

void CreateGround(TGfxTexture *groundset, char grid[][15], TGfxSprite *groundtiles[15], float screensizey);	// Creating level (ground only for now) from screen grid infos