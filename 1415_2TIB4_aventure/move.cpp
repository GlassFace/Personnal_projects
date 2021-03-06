
#include <stdio.h>
#include <math.h>
#include "flib.h"
#include "entities.h"



/*			Headers are in entities.h			 */



const float TILE = 32;		// Tiles size

const float SPEED = float(0.03);		// Speed increase every loop
const float SPEEDMAX = float(0.6);		// Maximum speed


void CheckCollision(hero *Hero, const float screensizex, const float screensizey, const char grid[11][16])	// Check collisions
{
	int intherox = int((*Hero).x);		// Conversion hero position from float to int
	int intheroy = int((*Hero).y);		// Conversion hero position from float to int


	if ((*Hero).dir.right)		// If going right
	{
		if ((*Hero).x > screensizex - 1 - (1 / TILE))		// Screen border collision
		{
			(*Hero).dir.right = false;

			(*Hero).x = float(intherox);	// Rounding hero position to avoid glitches
		}

		else if (grid[intheroy][intherox + 1] == '1' || grid[intheroy][intherox + 1] == '2')	// Sprites collision
		{
			(*Hero).dir.right = false;

			(*Hero).x = float(intherox);	// Rounding hero position to avoid glitches
		}
	}

	if ((*Hero).dir.left)		// If going left
	{
		if ((*Hero).x <= 0 || grid[intheroy][intherox - 1] == '1' || grid[intheroy][intherox - 1] == '2')	// Screen border and sprites collision
		{
			(*Hero).dir.left = false;

			(*Hero).x = float(intherox);	// Rounding hero position to avoid glitches
		}
	}

	if ((*Hero).dir.v == 0)			// If speed is nul, stop moving
	{
		(*Hero).dir.right = false;
		(*Hero).dir.left = false;
	}
}


void GetInput(hero *Hero)		// Get input
{



	if (GfxInputIsPressed(EGfxInputID_KeyCharD))			// Right
	{
		(*Hero).dir.right = true;

		if (GfxInputIsPressed(EGfxInputID_KeyCharZ) && !(*Hero).dir.jump && !(*Hero).dir.wasfalling)	// If up is pressed at the same time and hero wasn't falling or jumping
		{
			(*Hero).dir.jump = true;
		}

		if ((*Hero).dir.v < SPEEDMAX)			// Increasing speed
		{
			(*Hero).dir.v = (*Hero).dir.v + SPEED;
		}

		if ((*Hero).dir.wasgoingleft)		// If turning back, reinitialize delay to move instantly
		{
			(*Hero).dir.left = false;

			GfxSpriteSetScale((*Hero).sprite, 1, 1);			// Mirroring hero sprite
			GfxSpriteSetCutout((*Hero).sprite, 0, 0, 32, 32);	// Setting cutout to avoid sprite misplacing

			if ((*Hero).dir.v > 0)
			{
				(*Hero).dir.v = 0;			// And reinitializing speed

				if ((*Hero).dir.v < 0)
				{
					(*Hero).dir.v = 0;
				}
			}

			(*Hero).dir.movedelay = 0;

			(*Hero).dir.wasgoingleft = false;
		}
		(*Hero).dir.wasgoingright = true;	// Record the direction of this frame for the next one
	}




	else if (GfxInputIsPressed(EGfxInputID_KeyCharQ))		// Left
	{
		(*Hero).dir.left = true;

		if (GfxInputIsPressed(EGfxInputID_KeyCharZ) && !(*Hero).dir.jump && !(*Hero).dir.wasfalling)	// If up is pressed at the same time and hero wasn't falling or jumping
		{
			(*Hero).dir.jump = true;
		}

		if ((*Hero).dir.v < SPEEDMAX)			// Increasing speed
		{
			(*Hero).dir.v = (*Hero).dir.v + SPEED;
		}

		if ((*Hero).dir.wasgoingright)		// If turning back, reinitialize delay to move instantly
		{
			(*Hero).dir.right = false;

			GfxSpriteSetScale((*Hero).sprite, -1, 1);				// Mirroring hero sprite
			GfxSpriteSetCutout((*Hero).sprite, 32, 0, -32, 32);		// Changing cutout to avoid sprite misplacing

			if ((*Hero).dir.v > 0)
			{
				(*Hero).dir.v = 0;			// And reinitializing speed

				if ((*Hero).dir.v < 0)
				{
					(*Hero).dir.v = 0;
				}
			}

			(*Hero).dir.movedelay = 0;

			(*Hero).dir.wasgoingright = false;
		}

		(*Hero).dir.wasgoingleft = true;	// Record the direction of this frame for the next one
	}




	else if (GfxInputIsPressed(EGfxInputID_KeyCharZ) && !(*Hero).dir.jump && !(*Hero).dir.wasfalling)	// Jump
	{
		(*Hero).dir.jump = true;

		(*Hero).dir.yinitial = (*Hero).y;
	}

	else			// Decresing speed if hero stops moving
	{
		if ((*Hero).dir.v > 0)
		{
			(*Hero).dir.v = (*Hero).dir.v - SPEED;
		}
		else if ((*Hero).dir.v < 0)
		{
			(*Hero).dir.v = 0;
		}
	}
}



void MoveHero(hero *Hero, const char grid[11][16], const int tilenumber[11][16], TGfxSprite *cases[20], const float screensizex, const float screensizey)		// Move hero
{
	int intherox = int((*Hero).x);		// Conversion hero position from float to int
	int intheroy = int((*Hero).y);		// Conversion hero position from float to int


	(*Hero).x = (GfxSpriteGetPositionX((*Hero).sprite) / TILE);			// Getting hero position + downscaling
	(*Hero).y = (GfxSpriteGetPositionY((*Hero).sprite) / TILE);


	GetInput(Hero);		// Get input at this frame

	CheckCollision(Hero, screensizex, screensizey, grid);		// Check collisions


														/*			 FALL			*/

	if (grid[intheroy + 1][intherox] == '0' && (*Hero).dir.jump == false && grid[intheroy + 1][intherox + 1] == '0')				// Fall if nothing beneath hero
	{
		(*Hero).y = (*Hero).y + (((*Hero).dir.t / TILE) * ((*Hero).dir.t / TILE));


		if ((*Hero).dir.t < 25)
		{
			(*Hero).dir.t++;
		}

		(*Hero).dir.wasfalling = true;
	}

	else
	{
		if ((*Hero).dir.wasfalling)			// Correcting misplacing into the ground after a fall
		{
			(*Hero).y = float(intheroy);		// Placing hero exactly ne tile up this ground

			(*Hero).dir.t = 0;

			(*Hero).dir.jump = false;

			(*Hero).dir.wasfalling = false;
		}
	}

													/*			  END OF FALL				*/




															/*			MOVE			*/

	if ((*Hero).dir.movedelay == 1)		// Delay time
	{
		(*Hero).dir.movedelay = 0;
	}


	if ((*Hero).dir.right)				// Go right
	{
		if ((*Hero).dir.movedelay == 0)
		{
			(*Hero).x = (*Hero).x + (*Hero).dir.v;
		}

		((*Hero).dir.movedelay)++;
	}

	if ((*Hero).dir.left)				// Go left
	{
		if ((*Hero).dir.movedelay == 0)
		{
			(*Hero).x = (*Hero).x - (*Hero).dir.v;
		}

		((*Hero).dir.movedelay)++;
	}

													/*				END OF MOVE				 */



													/*				   JUMP					*/


		/* If hitting the ground after jumping  */

	// (Long if because of the ability to walk on left edge of tiles)

	if ((*Hero).y >= screensizey - 1 && (*Hero).dir.descending || (*Hero).dir.jump && (*Hero).dir.descending && grid[intheroy + 1 - (1 / 2)][intherox] == '1' || (*Hero).dir.jump && (*Hero).dir.descending && grid[intheroy + 1][intherox] == '2' || (*Hero).dir.jump && (*Hero).dir.descending && grid[intheroy + 1][intherox + 1 + (1 / int(TILE))] == '1' || (*Hero).dir.jump && (*Hero).dir.descending && grid[intheroy + 1][intherox + 1 + (1 / int(TILE))] == '2')
	{
		(*Hero).dir.jump = false;		// Record end of the jump
		(*Hero).dir.descending = false;		// Record end of descent
		(*Hero).dir.t = 0;					// Reinitialize time for fall equation

		(*Hero).y = float(intheroy);
	}




	if ((*Hero).dir.jump == true)		// Jump
	{
		if ((*Hero).y >= ((*Hero).dir.t - float(sqrt(2.0))) * ((*Hero).dir.t - float(sqrt(2.0))) - (3 - (*Hero).dir.yinitial) && (*Hero).dir.descending == false)	// If hero is going up
		{
			(*Hero).dir.descending = false;
		}
		else			// If hero is going down
		{
			(*Hero).dir.descending = true;
		}
		GfxDbgPrintf("Hero y = %f\n", (*Hero).y);

		(*Hero).y = ((*Hero).dir.t - float(sqrt(2.0))) * ((*Hero).dir.t - float(sqrt(2.0))) - (3 - (*Hero).dir.yinitial);		// Jumping equation

		(*Hero).dir.t = (*Hero).dir.t + float(0.09);		// Time update
	}

													/*				END OF JUMP				*/



	if (!(*Hero).dir.right && !(*Hero).dir.left && (*Hero).dir.movedelay != 0)		// If delay engaged but no key pressed at this frame, finish it anyway
	{
		((*Hero).dir.movedelay)++;
	}

	GfxSpriteSetPosition((*Hero).sprite, ((*Hero).x) * TILE, ((*Hero).y) * TILE);				// Update hero x position
}