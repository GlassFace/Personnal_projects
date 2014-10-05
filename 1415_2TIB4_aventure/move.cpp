#include "flib.h"
#include "move.h"
#include <stdio.h>
#include <math.h>

const float TILE = 32;		// Tiles size

const int XSCREENLENGHT = 15;	// Number of tiles on x

const float SPEED = 0.03;		// Speed increase every loop
const float SPEEDMAX = 0.6;		// Maximum speed

direction herodir = { 0 };		// Directions record structure

int delay = 0;		// Move delay

float heroxrelative = 0;	// Fake hero x position for falling equation
float t = 0;				// Time for jump

bool descending = false;	// 


void CheckCollision(float *herox, float *heroy, const float screensizex, const float screensizey, const char grid[][15])	// Check collisions
{
	int intherox = int(*herox);		// Conversion hero position from float to int
	int intheroy = int(*heroy);		// Conversion hero position from float to int


	if (*herox < 0 || *herox > screensizex - 1)							// Border collision
	{
		if (herodir.right)
		{
			*herox = screensizex - 1;
		}

		if (herodir.left)
		{
			*herox = 0;
		}
	}

	else
	{
		if (grid[intheroy][intherox] == '1' || grid[intheroy][intherox] == '2')		// Wall collision
		{
			if (herodir.right)
			{
				(*herox)--;
			}

			if (herodir.left)
			{
				(*herox)++;
			}
		}
	}

	if (herodir.v == 0)			// If speed is nul, stop moving
	{
		herodir.right = false;
		herodir.left = false;
	}
}


void GetInput()		// Get input
{
	if (GfxInputIsPressed(EGfxInputID_KeyCharD))			// Go right
	{
		herodir.right = true;

		if (herodir.v < SPEEDMAX)			// Increasing speed
		{
			herodir.v = herodir.v + SPEED;
		}

		if (herodir.wasgoingleft)		// If turning back, reinitialize delay to move instantly
		{
			herodir.left = false;

			if (herodir.v > 0)
			{
				herodir.v = 0;			// And reinitializing speed

				if (herodir.v < 0)
				{
					herodir.v = 0;
				}
			}

			delay = 0;

			herodir.wasgoingleft = false;
		}
		herodir.wasgoingright = true;	// Record the direction of this frame for the next one
	}

	else if (GfxInputIsPressed(EGfxInputID_KeyCharQ))		// Go left
	{
		herodir.left = true;

		if (herodir.v < SPEEDMAX)			// Increasing speed
		{
			herodir.v = herodir.v + SPEED;
		}

		if (herodir.wasgoingright)		// If turning back, reinitialize delay to move instantly
		{
			herodir.right = false;

			if (herodir.v > 0)
			{
				herodir.v = 0;			// And reinitializing speed

				if (herodir.v < 0)
				{
					herodir.v = 0;
				}
			}

			delay = 0;

			herodir.wasgoingright = false;
		}

		herodir.wasgoingleft = true;	// Record the direction of this frame for the next one
	}

	else if (GfxInputIsJustPressed(EGfxInputID_KeyCharZ))	// Jump
	{
		if (!herodir.jump && !herodir.wasfalling)								// If hero wasn't jumping or falling yet...
		{
			herodir.jump = true;
		}
	}

	else			// Decresing speed if hero stops moving
	{
		if (herodir.v > 0)
		{
			herodir.v = herodir.v - SPEED;
		}
		else if (herodir.v < 0)
		{
			herodir.v = 0;
		}
	}
}



void MoveHero(TGfxSprite *hero, float *herox, float *heroy, const char grid[][15], TGfxSprite *cases[15], const float screensizex, const float screensizey)		// Move hero
{
	int intherox = int(*herox);		// Conversion hero position from float to int
	int intheroy = int(*heroy);		// Conversion hero position from float to int

	float groundbeneathy = 0;


	*herox = (GfxSpriteGetPositionX(hero) / TILE);			// Getting hero position + downscaling
	*heroy = (GfxSpriteGetPositionY(hero) / TILE);


	GetInput();		// Get input at this frame


	if (grid[intheroy + 1][intherox] == '0' && herodir.jump == false)				// Fall if nothing beneath hero
	{
		*heroy = *heroy + ((heroxrelative / TILE) * (heroxrelative / TILE));

		if (heroxrelative < 25)
		{
			heroxrelative++;
		}

		herodir.wasfalling = true;
	}

	else
	{
		if (herodir.wasfalling)
		{
			groundbeneathy = (GfxSpriteGetPositionY(cases[intherox - 1]) / TILE);	// Correcting misplacing into the ground after a fall

			*heroy = groundbeneathy - 1;

			herodir.wasfalling = false;
		}
	}
	
	if (herodir.jump && descending && grid[intheroy + 1][intherox] == '1' || herodir.jump && descending && grid[intheroy + 1][intherox] == '2')		// If hitting the ground after jumping
	{
		herodir.jump = false;		// Record end of the jump
		descending = false;		// Record end of descent
		t = 0;					// Reinitialize time for fall equation

		groundbeneathy = (GfxSpriteGetPositionY(cases[intherox - 1]) / TILE);	// Correcting misplacing into the ground after jump
		*heroy = groundbeneathy - 1;
	}



	if (delay == 1)		// Delay time
	{
		delay = 0;
	}


	if (herodir.right)				// Go right
	{
		if (delay == 0)
		{
			*herox = *herox + herodir.v;
		}

		(delay)++;
	}

	if (herodir.left)				// Go left
	{
		if (delay == 0)
		{
			*herox = *herox - herodir.v;
		}

		(delay)++;
	}

	if (herodir.jump == true)		// Jump
	{
		if (*heroy <= (t - float(sqrt(2.0))) * (t - float(sqrt(2.0))) + 5 && descending == false)		// If hero is going up
		{
			descending = false;
		}
		else			// If hero is going down
		{
			descending = true;
		}

		*heroy = (t - float(sqrt(2.0))) * (t - float(sqrt(2.0))) + 5;		// Jumping equation

		t = t + 0.09;		// Time update
	}

	if (!herodir.right && !herodir.left && delay != 0)		// If delay engaged but no key pressed at this frame, finish it anyway
	{
		(delay)++;
	}

	CheckCollision(herox, heroy, screensizex, screensizey, grid);		// Check collisions


	GfxSpriteSetPosition(hero, (*herox) * TILE, (*heroy) * TILE);				// Update hero x position
}