#include "flib.h"
#include "HUD.h"




THUD * g_pHUD;
void Initialize()
{	

	g_pHUD = new THUD();
	g_pHUD->Initialize();
}



void Update()
{
	g_pHUD->Update();
}



void Render()
{
	GfxClear(EGfxColor_Black);
	g_pHUD->Render();
}



void GfxMain(int, char *[])
{
	GfxDefaultResolution(1920, 1080);
	GfxCallbacks(Initialize, Update, Render);
}
