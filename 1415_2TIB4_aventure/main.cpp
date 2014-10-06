
#include "flib.h"
#include "entities.h"
#include "animations.h"
#include "levelgesture.h"
//#include "gun.h"


const float TILE = 32;		// Tiles size

const int XSCREENLENGHT = 15;	// Number of tiles on x



					/* GROUND VARIABLES */

/* Ground sprites array */

TGfxSprite * g_groundcases[15] = { nullptr };






/* Bullets structures array */

//bullet g_Bullets[3] = { { nullptr, 0, 0, false, false, false } };




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
	GfxSpriteSetPosition(g_Hero.sprite, TILE, (g_screensizey - 2) * TILE);		// Setting hero's first position
	g_Hero.x = TILE;
	g_Hero.y = 0;


	TGfxTexture * pGroundTexture = GfxTextureLoad("ground.tga");		// Loading ground tileset



	LoadLevel(g_screengrid);														//Load level from txt file to array
	CreateGround(pGroundTexture, g_screengrid, g_groundcases, g_screensizey);		// Create ground sprites from array
}




void Update()
{
	AnimateWater(g_screengrid, g_groundcases);		// Animate water

	MoveHero(&g_Hero, g_screengrid, g_groundcases, g_screensizex, g_screensizey);	// Manage hero position

	//GunShoot(g_Bullets, g_Hero);		// Check if bullets are shot and manage them
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

	/*for (i = 0; i < 3; i++)
	{
		if (g_Bullets[i].sprite != nullptr)
		{
			GfxSpriteRender(g_Bullets[i].sprite);
		}
	}*/

	GfxSpriteRender(g_Hero.sprite);						// Render hero
}


void GfxMain(int, char *[])
{
	GfxCallbacks(Initialize, Update, Render);
}
