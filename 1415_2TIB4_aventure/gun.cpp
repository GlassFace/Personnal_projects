
#include "flib.h"
#include "gun.h"
#include "entities.h"


const float TILE = 32;		// Tiles size

const int BULLETSMAXAMMOUNT = 4;	// Maximum ammount of bullets existing at the same time


int n = 0;					// Cursor on actual bullet
int bulletsexisting = 0;		// Number of bullets that exists at this frame

bool (*Hero) = false;	// A bullet exists at this frame

int delay = 0;				// Delay between shoots


void BulletGesture(bullet bullets[4], const int i, const float screensizex)		// Move or destroy bullets
{
	if (bullets[i].right)		// If bullet is going right...
	{
		(bullets[i].x)++;

		GfxSpriteSetPosition(bullets[i].sprite, bullets[i].x * TILE, bullets[i].y * TILE);	// ... make it go right
	}

	else if (bullets[i].left)	// If bullet is going left...
	{
		(bullets[i].x)--;

		GfxSpriteSetPosition(bullets[i].sprite, bullets[i].x * TILE, bullets[i].y * TILE);	// ... make it go left
	}


	if (bullets[i].x >= screensizex)		// If bullet hits right border...
	{
		GfxSpriteDestroy(bullets[i].sprite);	// ... destroy it and reinitialize datas

		bullets[i].sprite = nullptr;

		bullets[i].x = 0;
		bullets[i].y = 0;

		bullets[i].right = false;

		bullets[i].exist = false;

		bulletsexisting--;		// Decreasing number of bullets
	}

	else if (bullets[i].x <= 0)		// If bullet hits left border
	{
		GfxSpriteDestroy(bullets[i].sprite);	// ... destroy it and reinitialize datas

		bullets[i].sprite = nullptr;

		bullets[i].x = 0;
		bullets[i].y = 0;

		bullets[i].right = false;

		bullets[i].exist = false;

		bulletsexisting--;		// Decreasing number of bullets
	}
}

void BulletCreate(bullet bullets[4], hero *Hero, TGfxTexture * bulletTexture)		// Create bullet if one is shooted
{
	if (!bullets[n].exist)		// If bullet n° n doesn't exist, create it and set attributes
	{
		bullets[n].sprite = GfxSpriteCreate(bulletTexture);

		if ((*Hero).dir.wasgoingright)		// If hero is looking right, bullet goes right
		{
			bullets[n].right = true;

			bullets[n].x = (*Hero).x + ((1) / TILE);				// Record x position
			bullets[n].y = (*Hero).y + (8 / TILE);		// Record y position

			GfxSpriteSetPosition(bullets[n].sprite, bullets[n].x * TILE, bullets[n].y * TILE);
		}

		else if ((*Hero).dir.wasgoingleft)	// If hero is looking left, bullet goes left
		{
			bullets[n].left = true;

			bullets[n].x = (*Hero).x - (10 / TILE);		// Record x position
			bullets[n].y = (*Hero).y + (8 / TILE);					// Record y position

			GfxSpriteSetPosition(bullets[n].sprite, bullets[n].x * TILE, bullets[n].y * TILE);
		}

		bullets[n].exist = true;		// Record that bullet n° n now exists

		n++;				// Move cursor on next bullet
		bulletsexisting++;	// Increasing number of bullets
	}

	else		// If bullet n° n already exists...
	{
		n++;	// Jump to next bullet structure

		if (n == BULLETSMAXAMMOUNT)		// Go to the first if we passed the last
		{
			n = 0;
		}

		if (!bullets[n].exist)		// Check if bullet n° n already exist, and if not, create it and set attributes
		{
			bullets[n].sprite = GfxLineSpriteCreate();		// Create a linesprite

			bullets[n].x = (*Hero).x - (8 / TILE);		// Record x position
			bullets[n].y = (*Hero).y;					// Record y position

			GfxSpriteSetPosition(bullets[n].sprite, bullets[n].x * TILE, bullets[n].y * TILE);	// Create it where the hero is

			if ((*Hero).dir.wasgoingright)		// If hero is looking right, bullet goes right
			{
				bullets[n].right = true;
			}

			else if ((*Hero).dir.wasgoingleft)	// If hero is looking left, bullet goes left
			{
				bullets[n].left = true;
			}

			bullets[n].exist = true;		// Record that bullet n° n now exists

			n++;				// Move cursor on next bullet
			bulletsexisting++;	// Increasing number of bullets
		}
	}

	if (n == BULLETSMAXAMMOUNT)		// Go to the first if we passed the last
	{
		n = 0;
	}
}

void GunShoot(bullet bullets[4], hero *Hero, TGfxTexture * bulletTexture, const float screensizex)		// Check if player tries to shoot at this frame or have already
{
	int i = 0;
	int o = 0;	// Number of bullets found when browsing them

	if (GfxInputIsPressed(EGfxInputID_KeyCharE) && delay == 0)	// If Z is pressed and delay is ok
	{
		BulletCreate(bullets, Hero, bulletTexture);		// Create bullet

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

	if (bulletsexisting > 0)
	{
		for (i = 0; i < BULLETSMAXAMMOUNT; i++)		// Browse bullet structures
		{
			if (bullets[i].exist)		// If a bullet exists, record it
			{
				BulletGesture(bullets, i, screensizex);

				o++;	// Increasing number of bullets found
			}

			if (o == bulletsexisting)
			{
				i = BULLETSMAXAMMOUNT;	// Forcing i to end the for
			}
		}
	}
}