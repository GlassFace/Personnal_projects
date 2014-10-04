#include "flib.h"
#include "animations.h"
#include "levelgesture.h"
#include "move.h"


const int TILE = 32;		// Tiles size

const int XSCREENLENGHT = 15;	// Number of tiles on x



					/* GROUND VARIABLES */

/* Ground sprites */

TGfxSprite * g_pGround1 = nullptr;
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
TGfxSprite * g_pGround15 = nullptr;


/* Store ground sprites into array */

TGfxSprite * g_groundcases[15] = { g_pGround1, g_pGround2, g_pGround3, g_pGround4, g_pGround5, g_pGround6, g_pGround7, g_pGround8, g_pGround9, g_pGround10, g_pGround11, g_pGround12, g_pGround13, g_pGround14, g_pGround15 };



					/* END OF GROUND VARIABLES */




					/* HERO VARIABLES */

TGfxSprite * g_pHero = nullptr;		// Sprite* for hero

float g_herox = 0;				// Hero x position
float g_heroy = 0;				// Hero y position

float g_jumpmaxheight = 0;		// Hero max jump height
float g_fallequationx = 0;		// X value for falling and jumping equations


					/* END OF HERO VARIABLES */




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
	g_pHero = GfxSpriteCreate(pHeroTexture);							// Putting texture into sprite
	GfxSpriteSetPosition(g_pHero, float(TILE), 0);		// Setting hero's first position


	TGfxTexture * pGroundTexture = GfxTextureLoad("ground.tga");		// Loading ground tileset



	LoadLevel(g_screengrid);												//Load level from file to array
	CreateGround(pGroundTexture, g_screengrid, g_groundcases, g_screensizey);		// Create ground sprites from array
}




void Update()
{
	AnimateWater(g_screengrid, g_groundcases);		// Animate water

	MoveHero(g_pHero, &g_herox, &g_heroy, g_screengrid, g_groundcases, g_screensizex, g_screensizey);				// Manage hero position
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

	GfxSpriteRender(g_pHero);						// Render hero
}


void GfxMain(int, char *[])
{
	GfxCallbacks(Initialize, Update, Render);
}
