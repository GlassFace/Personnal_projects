
#include "structures.h"

void CheckCollision(hero Hero, const float screensizex, const float screensizey, const char grid[][15]);	// Chek collisions

void GetInput(hero Hero);			// Get input

void MoveHero(hero Hero, const char grid[][15], TGfxSprite *cases[15], const float screensizex, const float screensizey);	// Move hero