#include "flib.h"
#include "move.h"

const int TILE = 32;		// Tiles size

const int XSCREENLENGHT = 15;	// Number of tiles on x

direction dir = { 0 };		// Directions record structure

int delay = 0;		// Move delay

float heroxrelative = 0;		// X value for falling and jumping equations


void CheckCollision(float *herox, float *heroy, const float screensizex, const float screensizey, const char grid[][15])	// Check collisions
{
	int intherox = int(*herox);		// Conversion hero position from float to int
	int intheroy = int(*heroy);		// Conversion hero position from float to int


	if (*herox < 0 || *herox > screensizex - 1)							// Border collision
	{
		if (dir.right)
		{
			*herox = screensizex - 1;
		}

		if (dir.left)
		{
			*herox = 0;
		}
	}

	else
	{
		if (grid[intheroy][intherox] == '1' || grid[intheroy][intherox] == '2')		// Wall collision
		{
			if (dir.right)
			{
				(*herox)--;
			}

			if (dir.left)
			{
				(*herox)++;
			}
		}
	}

	dir.right = false;
	dir.left = false;
}


void GetInput(float *herox, float *heroy)		// Get input
{
	if (GfxInputIsPressed(EGfxInputID_KeyCharD))			// Go right
	{
		dir.right = true;

		if (dir.wasgoingleft)		// If turning back, reinitialize delay to move instantly
		{
			delay = 0;

			dir.wasgoingleft = false;
		}

		dir.wasgoingright = true;	// Record the direction of this frame for the next one
	}

	else if (GfxInputIsPressed(EGfxInputID_KeyCharQ))		// Go left
	{
		dir.left = true;

		if (dir.wasgoingright)		// If turning back, reinitialize delay to move instantly
		{
			delay = 0;

			dir.wasgoingright = false;
		}

		dir.wasgoingleft = true;	// Record the direction of this frame for the next one
	}

	else if (GfxInputIsJustPressed(EGfxInputID_KeyCharZ))	// Jump
	{
		if (!dir.jump)								// If hero wasn't jumping yet...
		{
			if (!dir.wasfalling)
			{
				dir.jump = true;
			}
		}
	}

	else			// If nothing pressed, record that hero doesn't move this frame
	{
		dir.wasgoingleft = false;
		dir.wasgoingright = false;
	}
}



void MoveHero(TGfxSprite *hero, float *herox, float *heroy, const char grid[][15], TGfxSprite *cases[15], const float screensizex, const float screensizey)		// Move hero
{
	int intherox = int(*herox);		// Conversion hero position from float to int
	int intheroy = int(*heroy);		// Conversion hero position from float to int

	float groundbeneathy = 0;


	*herox = (GfxSpriteGetPositionX(hero) / TILE);			// Getting hero position + downscaling
	*heroy = (GfxSpriteGetPositionY(hero) / TILE);


	GetInput(herox, heroy);		// Get input at this frame


	if (grid[intheroy + 1][intherox] == '0' && dir.jump == false)				// Fall if nothing beneath hero
	{
		*heroy = *heroy + ((heroxrelative / TILE) * (heroxrelative / TILE));

		if (heroxrelative < 25)
		{
			heroxrelative++;
		}

		dir.wasfalling = true;
	}

	else
	{
		if (dir.wasfalling)
		{
			groundbeneathy = (GfxSpriteGetPositionY(cases[intherox - 1]) / TILE);

			*heroy = groundbeneathy - 1;

			dir.wasfalling = false;
			heroxrelative = 0;
		}
	}



	if (delay == 10)		// Delay time
	{
		delay = 0;
	}


	if (dir.right)				// Go right
	{
		if (delay == 0)
		{
			(*herox)++;
		}

		(delay)++;
	}

	if (dir.left)				// Go left
	{
		if (delay == 0)
		{
			(*herox)--;
		}

		(delay)++;
	}

	if (dir.jump == true)		// Jump
	{
		
	}

	if (!dir.right && !dir.left && delay != 0)		// If delay engaged but no key pressed at this frame, finish it anyway
	{
		(delay)++;
	}

	CheckCollision(herox, heroy, screensizex, screensizey, grid);		// Check collisions


	GfxSpriteSetPosition(hero, (*herox) * TILE, (*heroy) * TILE);				// Update hero x position
}