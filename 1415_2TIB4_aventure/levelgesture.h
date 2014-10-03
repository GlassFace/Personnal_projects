
void LoadLevel(char grid[][14], TGfxFile *level);		// Loading level from level.txt

void CreateGround(TGfxTexture *groundset, char grid[][14], TGfxSprite *groundtiles[14], float screensizey, const int TILE);	// Creating level (ground only for now) from screen grid infos