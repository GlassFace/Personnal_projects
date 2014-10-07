
#ifndef GUN
#define GUN

#include "entities.h"

typedef struct bullet bullet;		// Bullet structure
struct bullet
{
TGfxSprite * sprite;		// Sprite

float x;		// X position
float y;		// Y position

bool right;		// Goind right
bool left;		// Goind left

bool exist;		// Have been created
};



/*		GUN HEADERS			*/

void GunShoot(bullet bullets[4], hero *Hero, TGfxTexture * bulletTexture, const float screensizex);		// Check if player tries to shoot at this frame or have already

void BulletCreate(bullet bullets[4], hero *Hero, TGfxTexture * bulletTexture);	// Create bullet if one is shooted

void BulletGesture(bullet bullets[4], const int i, const float screensizex);				// Move or destroy bullets



#endif