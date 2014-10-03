#include "flib.h"

const int TILE = 32;		// Tiles size

const int XSCREENLENGHT = 15;	// Number of tiles on x


void CheckCollision(float *herox, const bool *right, const bool *left, const float screensizex, const float screensizey, const char grid[][15])
{
	int intherox = int(*herox);		// Conversion hero position from float to int


	if (*herox < 0 || *herox > screensizex - 1)							// Border collision
	{
		if (*right)
		{
			(*herox)--;
		}

		if (*left)
		{
			(*herox)++;
		}
	}


	if (grid[7][intherox] == '1' || grid[7][intherox] == '2')		// Wall collision
	{
		if (*right)
		{
			(*herox)--;
		}

		if (*left)
		{
			(*herox)++;
		}
	}
}


void GetInput(bool *right, bool *left)		// Get input
{
	if (GfxInputIsPressed(EGfxInputID_KeyCharD))
	{
		*right = true;
	}

	else if (GfxInputIsPressed(EGfxInputID_KeyCharQ))
	{
		*left = true;
	}
}



void MoveHero(TGfxSprite *hero, float *herox, float *heroy, int *delay, const char grid[][15], const float screensizex, const float screensizey)		// Move hero
{
	bool right = false;
	bool left = false;

	*herox = (GfxSpriteGetPositionX(hero) / TILE);			// Getting hero position + downscaling
	*heroy = (GfxSpriteGetPositionY(hero) / TILE);


	GetInput(&right, &left);		// Get input at this frame


	if (*delay == 10)		// Delay time
	{
		*delay = 0;
	}


	if (right)
	{
		if (*delay == 0)
		{
			(*herox)++;
		}

		(*delay)++;
	}

	if (left)
	{
		if (*delay == 0)
		{
			(*herox)--;
		}


		(*delay)++;
	}

	if (!right && !left && *delay != 0)		// If delay engaged but no key pressed at this frame, finish it anyway
	{
		(*delay)++;
	}

	CheckCollision(herox, &right, &left, screensizex, screensizey, grid);		// Check collisions


	GfxSpriteSetPosition(hero, (*herox) * TILE, (*heroy) * TILE);				// Update hero x position
}