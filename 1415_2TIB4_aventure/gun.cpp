/*
#include "flib.h"
#include "gun.h"
#include "entities.h"


const float TILE = 32;		// Tiles size


int n = 0;		// Number of actual bullet

bool bulletexist = false;	// A bullet exists at this frame

int delay = 0;				// Delay between shoots

float screensizex = (GfxGetDisplaySizeX() / TILE);	// Screen X size


void BulletGesture(bullet bullets[3])		// Move or destroy bullets
{
	int i = 0;

	for (i = 0; i < 3; i++)		// Browse bullet structures
	{
		if (bullets[i].exist)		// If bullet exists...
		{
			if (bullets[i].right)		// ... and is going right
			{
				GfxSpriteSetPosition(bullets[i].sprite, (bullets[i].x + 1), bullets[i].y);	// ... make it go right
			}

			else if (bullets[i].left)	// ... or if it's going left
			{
				GfxSpriteSetPosition(bullets[i].sprite, (bullets[i].x - 1), bullets[i].y);	// ... make it go left
			}


			if (bullets[i].x >= screensizex)		// If bullet hits right border...
			{
				GfxSpriteDestroy(bullets[i].sprite);	// ... destroy it and reinitialize datas

				bullets[i].x = 0;
				bullets[i].y = 0;

				bullets[i].right = false;

				bullets[i].exist = false;
			}

			else if (bullets[i].x <= 0)		// If bullet hits left border
			{
				GfxSpriteDestroy(bullets[i].sprite);	// ... destroy it and reinitialize datas

				bullets[i].x = 0;
				bullets[i].y = 0;

				bullets[i].right = false;

				bullets[i].exist = false;
			}
		}
	}
}

void BulletCreate(bullet bullets[3], hero Hero)		// Create bullet if one is shooted
{
	if (!bullets[n].exist)		// If bullet n° n doesn't exist, create it and set attributes
	{
		bullets[n].sprite = GfxLineSpriteCreate();		// Create a linesprite

		GfxSpriteSetPosition(bullets[n].sprite, Hero.x, Hero.y);	// Create it where the hero is

		bullets[n].x = Hero.x;		// Record x position
		bullets[n].y = Hero.y;		// Record y position

		if (Hero.dir.wasgoingright)		// If hero is looking right, bullet goes right
		{
			bullets[n].right = true;
		}

		else if (Hero.dir.wasgoingleft)	// If hero is looking left, bullet goes left
		{
			bullets[n].left = true;
		}

		bullets[n].exist = true;		// Record that bullet n° n now exists

		n++;		// Increase n number to jump to next bullet structure for next time
	}

	else		// If bullet n° n already exists...
	{
		n++;	// Jump to next bullet structure

		if (n == 3)		// Go to the first if we passed the last
		{
			n = 0;
		}

		if (!bullets[n].exist)		// Check if bullet n° n already exist, and if not, create it and set attributes
		{
			bullets[n].sprite = GfxLineSpriteCreate();		// Create a linesprite

			GfxSpriteSetPosition(bullets[n].sprite, Hero.x, Hero.y);	// Create it where the hero is

			bullets[n].x = Hero.x;		// Record x position
			bullets[n].y = Hero.y;		// Record y position

			if (Hero.dir.wasgoingright)		// If hero is looking right, bullet goes right
			{
				bullets[n].right = true;
			}

			else if (Hero.dir.wasgoingleft)	// If hero is looking left, bullet goes left
			{
				bullets[n].left = true;
			}

			bullets[n].exist = true;		// Record that bullet n° n now exists

			n++;		// Increase n number to jump to next bullet structure for next time
		}
	}
}

void GunShoot(bullet bullets[3], hero Hero)		// Check if player tries to shoot at this frame
{
	int i = 0;

	if (GfxInputIsPressed(EGfxInputID_KeyCharE) && delay == 0)	// If Z is pressed and delay is ok
	{
		BulletCreate(bullets, Hero);		// Create bullet

		delay++;
	}

	if (delay == 10)		// Delay duration
	{
		delay = 0;
	}

	else if (delay != 0)	// If delay have been engaged, pursue it
	{
		delay++;
	}

	for (i = 0; i < 3; i++)		// Browse bullet structures
	{
		if (bullets[i].exist)		// If a bullet exists, record it
		{
			bulletexist = true;
		}

		else						// If not, record that none exist.
		{
			bulletexist = false;
		}
	}

	if (bulletexist)		// If a bullet exists, manage it
	{
		BulletGesture(bullets);
	}
}*/