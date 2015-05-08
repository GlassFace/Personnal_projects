#include "flib.h"
#include "flib_vec2.h"
#include "Control.h"
#include "Camera.h"
#include "Villager.h"
#include "Map.h"




namespace
{
	const float SCROLL_SPEED = 5.f;
}

TVillager * TControl::s_pDraggedVillager = nullptr;
bool TControl::s_bClicked = false;

TControl::TControl()
{

}

TControl::~TControl()
{

}

void TControl::Update()
{
	CheckInput();
}

void TControl::CheckInput()
{
	if (GfxInputIsPressed(EGfxInputID_KeyArrowLeft))
	{
		TCamera::S_Scroll(-SCROLL_SPEED);
	}
	if (GfxInputIsPressed(EGfxInputID_KeyArrowRight))
	{
		TCamera::S_Scroll(SCROLL_SPEED);
	}
	if (GfxInputIsJustPressed(EGfxInputID_MouseLeft))
	{
		TGfxVec2 tMousePosition(GfxInputGetMousePositionX(), GfxInputGetMousePositionY());
		for (int i = 0; i < TMap::S_GetVillagerCount(); i++)
		{
			TVillager * pVillager = TMap::S_GetVillagers()[i];
			if (pVillager->IsMouseOver(tMousePosition))
			{
				s_pDraggedVillager = pVillager;
				s_bClicked = true;
				break;

			}
		}
	}
	if (GfxInputIsPressed(EGfxInputID_MouseLeft))
	{
		if (s_bClicked == true)
		{
			TGfxVec2 tMousePosition(GfxInputGetMousePositionX(), GfxInputGetMousePositionY());
			s_pDraggedVillager->SetPosition(tMousePosition);
		}
	}
	if (GfxInputIsJustReleased(EGfxInputID_MouseLeft))
	{
		s_bClicked = false;
		s_pDraggedVillager = nullptr;
	}
}