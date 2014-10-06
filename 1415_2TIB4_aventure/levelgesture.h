
#ifndef LEVELGESTURE
#define LEVELGESTURE

void LoadLevel(char grid[10][15], int tilenumber[10][15]);		// Loading level from level.txt

void CreateGround(TGfxTexture *groundset, char grid[10][15], TGfxSprite *groundtiles[20]);	// Creating level (ground only for now) from screen grid infos

#endif