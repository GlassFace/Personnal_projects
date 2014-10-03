#include "flib.h"

const int TILE = 32;		// Tiles size

const int XSCREENLENGHT = 15;	// Number of tiles on x


void CheckCollision(float *herox, float *heroy, const bool *right, const bool *left, const float screensizex, const float screensizey, const char grid[][15])
{
	int intherox = int(*herox);		// Conversion hero position from float to int
	int intheroy = int(*heroy);		// Conversion hero position from float to int


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

	else
	{
		if (grid[intheroy][intherox] == '1' || grid[intheroy][intherox] == '2')		// Wall collision
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
}


void GetInput(bool *right, bool *left, bool *jump, bool *wasgoingleft, bool *wasgoingright, int *delay, bool *wasfalling, float *jumpmaxheight, float *heroy)		// Get input
{
	if (GfxInputIsPressed(EGfxInputID_KeyCharD))			// Go right
	{
		*right = true;

		if (*wasgoingleft)		// If turning back, reinitialize delay to move instantly
		{
			*delay = 0;

			*wasgoingleft = false;
		}

		*wasgoingright = true;	// Record the direction of this frame for the next one
	}

	else if (GfxInputIsPressed(EGfxInputID_KeyCharQ))		// Go left
	{
		*left = true;

		if (*wasgoingright)		// If turning back, reinitialize delay to move instantly
		{
			*delay = 0;

			*wasgoingright = false;
		}

		*wasgoingleft = true;	// Record the direction of this frame for the next one
	}

	else if (GfxInputIsJustPressed(EGfxInputID_KeyCharZ))	// Jump
	{
		if (!*jump)								// If hero wasn't jumping yet...
		{
			*jumpmaxheight = *heroy - 2;		// ... set jump max height

			if (!*wasfalling)
			{
				*jump = true;
			}
		}
	}

	else			// If nothing pressed, record that hero doesn't move this frame
	{
		*wasgoingleft = 0;
		*wasgoingright = 0;
	}
}



void MoveHero(TGfxSprite *hero, float *herox, float *heroy, int *delay, bool *wasgoingleft, bool *wasgoingright, bool *wasfalling, bool *jump, float *jumpmaxheight, const char grid[][15], const float screensizex, const float screensizey)		// Move hero
{
	bool right = false;
	bool left = false;

	int intherox = int(*herox);		// Conversion hero position from float to int
	int intheroy = int(*heroy);		// Conversion hero position from float to int


	*herox = (GfxSpriteGetPositionX(hero) / TILE);			// Getting hero position + downscaling
	*heroy = (GfxSpriteGetPositionY(hero) / TILE);


	GetInput(&right, &left, jump, wasgoingleft, wasgoingright, delay, wasfalling, jumpmaxheight, heroy);		// Get input at this frame


	if (grid[intheroy + 1][intherox] == '0' && *jump == false)		// Fall if nothing beneath hero
	{
		*wasfalling = true;
		*heroy = *heroy + float(0.1);
	}

	else
	{
		*wasfalling = false;
	}


	if (*delay == 10)		// Delay time
	{
		*delay = 0;
	}


	if (right)				// Go right
	{
		if (*delay == 0)
		{
			(*herox)++;
		}

		(*delay)++;
	}

	if (left)				// Go left
	{
		if (*delay == 0)
		{
			(*herox)--;
		}


		(*delay)++;
	}

	if (*jump == true)		// Jump
	{
		if (*heroy > *jumpmaxheight)		// Go up until max jump height
		{
			*heroy = *heroy - float(0.1);
		}

		else
		{
			*jump = false;
		}
	}

	if (!right && !left && *delay != 0)		// If delay engaged but no key pressed at this frame, finish it anyway
	{
		(*delay)++;
	}

	CheckCollision(herox, heroy, &right, &left, screensizex, screensizey, grid);		// Check collisions


	GfxSpriteSetPosition(hero, (*herox) * TILE, (*heroy) * TILE);				// Update hero x position
}