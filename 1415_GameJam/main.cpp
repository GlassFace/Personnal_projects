#include "flib.h"
#include "HUD.h"




THUD * g_pHUD;
void Initialize()
{	

	g_pHUD = new THUD();
	THUD::S_Initialize();
}



void Update()
{
	THUD::S_Update();
}



void Render()
{
	GfxClear(EGfxColor_Black);
	THUD::S_Render();
}



void GfxMain(int, char *[])
{
	GfxDefaultResolution(1920, 1080);
	GfxCallbacks(Initialize, Update, Render);
}
