
#include "flib.h"
#include "structures.h"
#include "animations.h"
#include "levelgesture.h"
//#include "move.h"
//#include "gun.h"


const float TILE = 32;		// Tiles size

const int XSCREENLENGHT = 15;	// Number of tiles on x



					/* GROUND VARIABLES */

/* Ground sprites */

/*TGfxSprite * g_pGround1 = nullptr;
TGfxSprite * g_pGround2 = nullptr;
TGfxSprite * g_pGround3 = nullptr;
TGfxSprite * g_pGround4 = nullptr;
TGfxSprite * g_pGround5 = nullptr;
TGfxSprite * g_pGround6 = nullptr;
TGfxSprite * g_pGround7 = nullptr;
TGfxSprite * g_pGround8 = nullptr;
TGfxSprite * g_pGround9 = nullptr;
TGfxSprite * g_pGround10 = nullptr;
TGfxSprite * g_pGround11 = nullptr;
TGfxSprite * g_pGround12 = nullptr;
TGfxSprite * g_pGround13 = nullptr;
TGfxSprite * g_pGround14 = nullptr;
TGfxSprite * g_pGround15 = nullptr;*/


/* Store ground sprites into array */

TGfxSprite * g_groundcases[15] = { nullptr };



					/* END OF GROUND VARIABLES */



/* Bullets structures */

/*bullet g_pBullet1 = { nullptr, 0, 0, false, false, false };
bullet g_pBullet2 = { nullptr, 0, 0, false, false, false };
bullet g_pBullet3 = { nullptr, 0, 0, false, false, false };*/


/* Store bullets into array */

bullet g_Bullets[3] = { { nullptr, 0, 0, false, false, false }, { nullptr, 0, 0, false, false, false }, { nullptr, 0, 0, false, false, false } };




					/* HERO STRUCTURE */

hero g_Hero = { 0 };




					/* SCREEN VARIABLES	*/

char g_screengrid[10][15] = {{ 0 }, { 0 }};		// Screen grid array


float g_screensizex = 0;		// Screen x size
float g_screensizey = 0;		// Screen y size


					/* END OF SCREEN VARIABLES */




void Initialize()
{
	g_screensizex = float(GfxGetDisplaySizeX() / TILE);		// Getting screen size (+ downscaling)
	g_screensizey = float(GfxGetDisplaySizeY() / TILE);


	TGfxTexture * pHeroTexture = GfxTextureLoad("hero.tga");			// Loading hero texture
	g_Hero.sprite = GfxSpriteCreate(pHeroTexture);							// Putting texture into sprite
	GfxSpriteSetPosition(g_Hero.sprite, TILE, 0);		// Setting hero's first position
	g_Hero.x = TILE;
	g_Hero.y = 0;


	TGfxTexture * pGroundTexture = GfxTextureLoad("ground.tga");		// Loading ground tileset



	LoadLevel(g_screengrid);														//Load level from txt file to array
	CreateGround(pGroundTexture, g_screengrid, g_groundcases, g_screensizey);		// Create ground sprites from array
}




void Update()
{
	AnimateWater(g_screengrid, g_groundcases);		// Animate water

	MoveHero(g_Hero, g_screengrid, g_groundcases, g_screensizex, g_screensizey);	// Manage hero position

	GunShoot(g_Bullets, g_Hero);		// Check if bullets are shot and manage them
}





void Render()
{
	int i = 0;

	GfxClear(EGfxColor_White);

	for (i = 0; i < XSCREENLENGHT; i++)
	{
		if (g_groundcases[i] != nullptr)			// Render every ground sprite that aren't null
		{
			GfxSpriteRender(g_groundcases[i]);
		}
	}

	for (i = 0; i < 3; i++)
	{
		if (g_Bullets[i].sprite != nullptr)
		{
			GfxSpriteRender(g_Bullets[i].sprite);
		}
	}

	GfxSpriteRender(g_Hero.sprite);						// Render hero
}


void GfxMain(int, char *[])
{
	GfxCallbacks(Initialize, Update, Render);
}
