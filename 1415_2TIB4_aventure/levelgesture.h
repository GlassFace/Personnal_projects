
#ifndef LEVELGESTURE
#define LEVELGESTURE

void LoadLevel(char grid[11][16], int tilenumber[11][16]);		// Loading level from level.txt

void CreateGround(TGfxTexture *groundset, char grid[11][16], TGfxSprite *groundtiles[20]);	// Creating level (ground only for now) from screen grid infos

#endif