
#include <stdio.h>
#include <math.h>
#include "flib.h"
#include "move.h"
#include "main.h"


const float TILE = 32;		// Tiles size

const float SPEED = float(0.03);		// Speed increase every loop
const float SPEEDMAX = float(0.6);		// Maximum speed


void CheckCollision(hero Hero, const float screensizex, const float screensizey, const char grid[][15])	// Check collisions
{
	int intherox = int(Hero.x);		// Conversion hero position from float to int
	int intheroy = int(Hero.y);		// Conversion hero position from float to int


	if (Hero.x < 0 || Hero.x > screensizex - 1)							// Border collision
	{
		if (Hero.dir.right)
		{
			Hero.x = screensizex - 1;
		}

		if (Hero.dir.left)
		{
			Hero.x = 0;
		}
	}

	else
	{
		if (grid[intheroy][intherox] == '1' || grid[intheroy][intherox] == '2')		// Wall collision
		{
			if (Hero.dir.right)
			{
				(Hero.x)--;
			}

			if (Hero.dir.left)
			{
				(Hero.x)++;
			}
		}
	}

	if (Hero.dir.v == 0)			// If speed is nul, stop moving
	{
		Hero.dir.right = false;
		Hero.dir.left = false;
	}
}


void GetInput(hero Hero)		// Get input
{
	if (GfxInputIsPressed(EGfxInputID_KeyCharD))			// Go right
	{
		Hero.dir.right = true;

		if (GfxInputIsPressed(EGfxInputID_KeyCharZ) && !Hero.dir.jump && !Hero.dir.wasfalling)	// If up is pressed at the same time and hero wasn't falling or jumping
		{
			Hero.dir.jump = true;
		}

		if (Hero.dir.v < SPEEDMAX)			// Increasing speed
		{
			Hero.dir.v = Hero.dir.v + SPEED;
		}

		if (Hero.dir.wasgoingleft)		// If turning back, reinitialize delay to move instantly
		{
			Hero.dir.left = false;

			if (Hero.dir.v > 0)
			{
				Hero.dir.v = 0;			// And reinitializing speed

				if (Hero.dir.v < 0)
				{
					Hero.dir.v = 0;
				}
			}

			Hero.dir.movedelay = 0;

			Hero.dir.wasgoingleft = false;
		}
		Hero.dir.wasgoingright = true;	// Record the direction of this frame for the next one
	}

	else if (GfxInputIsPressed(EGfxInputID_KeyCharQ))		// Go left
	{
		Hero.dir.left = true;

		if (GfxInputIsPressed(EGfxInputID_KeyCharZ) && !Hero.dir.jump && !Hero.dir.wasfalling)	// If up is pressed at the same time and hero wasn't falling or jumping
		{
			Hero.dir.jump = true;
		}

		if (Hero.dir.v < SPEEDMAX)			// Increasing speed
		{
			Hero.dir.v = Hero.dir.v + SPEED;
		}

		if (Hero.dir.wasgoingright)		// If turning back, reinitialize delay to move instantly
		{
			Hero.dir.right = false;

			if (Hero.dir.v > 0)
			{
				Hero.dir.v = 0;			// And reinitializing speed

				if (Hero.dir.v < 0)
				{
					Hero.dir.v = 0;
				}
			}

			Hero.dir.movedelay = 0;

			Hero.dir.wasgoingright = false;
		}

		Hero.dir.wasgoingleft = true;	// Record the direction of this frame for the next one
	}

	else if (GfxInputIsPressed(EGfxInputID_KeyCharZ) && !Hero.dir.jump && !Hero.dir.wasfalling)	// Jump (if hero wasn't falling or jumping)
	{
		Hero.dir.jump = true;
	}

	else			// Decresing speed if hero stops moving
	{
		if (Hero.dir.v > 0)
		{
			Hero.dir.v = Hero.dir.v - SPEED;
		}
		else if (Hero.dir.v < 0)
		{
			Hero.dir.v = 0;
		}
	}
}



void MoveHero(hero Hero, const char grid[][15], TGfxSprite *cases[15], const float screensizex, const float screensizey)		// Move hero
{
	int intherox = int(Hero.x);		// Conversion hero position from float to int
	int intheroy = int(Hero.y);		// Conversion hero position from float to int

	float groundbeneathy = 0;


	Hero.x = (GfxSpriteGetPositionX(Hero.sprite) / TILE);			// Getting hero position + downscaling
	Hero.y = (GfxSpriteGetPositionY(Hero.sprite) / TILE);


	GetInput(Hero);		// Get input at this frame


	if (grid[intheroy + 1][intherox] == '0' && Hero.dir.jump == false)				// Fall if nothing beneath hero
	{
		Hero.y = Hero.y + ((Hero.dir.t / TILE) * (Hero.dir.t / TILE));

		if (Hero.dir.t < 25)
		{
			Hero.dir.t++;
		}

		Hero.dir.wasfalling = true;
	}

	else
	{
		if (Hero.dir.wasfalling)			// Correcting misplacing into the ground after a fall
		{
			groundbeneathy = (GfxSpriteGetPositionY(cases[intherox - 1]) / TILE);	// Getting y position of ground beneath

			Hero.y = groundbeneathy - 1;		// Placing hero exactly ne tile up this ground

			Hero.dir.t = 0;

			Hero.dir.wasfalling = false;
		}
	}
	
	if (Hero.dir.jump && Hero.dir.descending && grid[intheroy + 1][intherox] == '1' || Hero.dir.jump && Hero.dir.descending && grid[intheroy + 1][intherox] == '2')		// If hitting the ground after jumping
	{
		Hero.dir.jump = false;		// Record end of the jump
		Hero.dir.descending = false;		// Record end of descent
		Hero.dir.t = 0;					// Reinitialize time for fall equation

		groundbeneathy = (GfxSpriteGetPositionY(cases[intherox - 1]) / TILE);	// Correcting misplacing into the ground after jump
		Hero.y = groundbeneathy - 1;
	}



	if (Hero.dir.movedelay == 1)		// Delay time
	{
		Hero.dir.movedelay = 0;
	}


	if (Hero.dir.right)				// Go right
	{
		if (Hero.dir.movedelay == 0)
		{
			Hero.x = Hero.x + Hero.dir.v;
		}

		(Hero.dir.movedelay)++;
	}

	if (Hero.dir.left)				// Go left
	{
		if (Hero.dir.movedelay == 0)
		{
			Hero.x = Hero.x - Hero.dir.v;
		}

		(Hero.dir.movedelay)++;
	}

	if (Hero.dir.jump == true)		// Jump
	{
		if (Hero.y <= (Hero.dir.t - float(sqrt(2.0))) * (Hero.dir.t - float(sqrt(2.0))) + 5 && Hero.dir.descending == false)		// If hero is going up
		{
			Hero.dir.descending = false;
		}
		else			// If hero is going down
		{
			Hero.dir.descending = true;
		}

		Hero.y = (Hero.dir.t - float(sqrt(2.0))) * (Hero.dir.t - float(sqrt(2.0))) + 5;		// Jumping equation

		Hero.dir.t = Hero.dir.t + float(0.09);		// Time update
	}

	if (!Hero.dir.right && !Hero.dir.left && Hero.dir.movedelay != 0)		// If delay engaged but no key pressed at this frame, finish it anyway
	{
		(Hero.dir.movedelay)++;
	}

	CheckCollision(Hero, screensizex, screensizey, grid);		// Check collisions


	GfxSpriteSetPosition(Hero.sprite, (Hero.x) * TILE, (Hero.y) * TILE);				// Update hero x position
}