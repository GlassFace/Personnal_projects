
#ifndef MAIN
#define MAIN

typedef struct hero hero;		// Hero structure
struct hero
{
	TGfxSprite * sprite;	// Sprite

	float x;				// X position
	float y;				// Y position

	direction dir;			// Directions structure
};

#endif