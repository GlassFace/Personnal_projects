
#include "flib.h"





void Initialize()
{
	GfxDbgPrintf("test");
}



void Update()
{

}



void Render()
{
	GfxClear(EGfxColor_Black);
}



void GfxMain(int, char *[])
{
	GfxCallbacks(Initialize, Update, Render);
}
