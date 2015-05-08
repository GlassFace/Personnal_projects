
#include "flib.h"
#include "flib_vec2.h"
#include "generics.h"
#include "Camera.h"




namespace Generics
{
	const TGfxVec2 GetCurrentMouse()
	{
		return TGfxVec2(float(GfxInputGetMousePositionX()), float(GfxInputGetMousePositionY())) + (TCamera::S_GetWorldPosition());
	}
}
