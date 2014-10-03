#include "flib.h"
#include "animations.h"
#include "levelgesture.h"


const int TILE = 32;


TGfxSprite * g_pHero = nullptr;		// Sprite* for hero



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

/* Store ground sprites into pointers-array */
TGfxSprite * g_groundcases[15] = { g_pGround1, g_pGround2, g_pGround3, g_pGround4, g_pGround5, g_pGround6, g_pGround7, g_pGround8, g_pGround9, g_pGround10, g_pGround11, g_pGround12, g_pGround13, g_pGround14, g_pGround15 };


char g_screengrid[9][14] = {{ 0 }, { 0 }};

float groundx = 0;			// ground x position
float groundy = 0;			// ground y position

float waterx = 0;			// water x position
float watery = 0;			// water y position

int g_waterdelay = 0;


float screensizex = 0;		// Screen x size
float screensizey = 0;		// Screen y size


void Initialize()
{
	screensizex = float(GfxGetDisplaySizeX() / TILE);		// Getting screen size (+ downscaling)
	screensizey = float(GfxGetDisplaySizeY() / TILE);

	TGfxFile * levelfile = nullptr;


	TGfxTexture * pSolTexture = GfxTextureLoad("ground.tga");			// Loading ground tileset

	LoadLevel(g_screengrid, levelfile);
	CreateGround(pSolTexture, g_screengrid, g_groundcases, TILE, screensizey);
}

void Update()
{
	int i = 0;

	for (i = 0; i < 15; i++)
	{
		if (g_screengrid[8][i] == '2')								// If there is water at this ground tile...
		{
			AnimateWater(g_groundcases[i], g_waterdelay, TILE);	// ... animate water
		}
	}

	g_waterdelay++;
	if (g_waterdelay == 20)
	{
		g_waterdelay = 0;
	}
}


void Render()
{
	int i = 0;

	GfxClear(EGfxColor_White);

	for (i = 0; i < 15; i++)
	{
		if (g_groundcases[i] != nullptr)
		{
			GfxSpriteRender(g_groundcases[i]);
		}
	}
}


void GfxMain(int, char *[])
{
	GfxCallbacks(Initialize, Update, Render);
}
