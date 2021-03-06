
#include "flib.h"
#include "flib_vec2.h"
#include "generics.h"
#include "Background.h"
#include "Parallax.h"
#include "Map.h"
#include "Entity.h"
#include "Dynamic.h"
#include "Villager.h"
#include "Building.h"
#include "House.h"
#include "Meteorite.h"




void GfxMain(int, char *[])
{
	GfxDefaultResolution(1920, 1080);
	GfxCallbacks(TMap::S_Initialize, TMap::S_Update, TMap::S_Render);
}
