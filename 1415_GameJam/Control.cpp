#include "flib.h"
#include "flib_vec2.h"
#include "generics.h"
#include "Control.h"
#include "Camera.h"
#include "Entity.h"
#include "Dynamic.h"
#include "Villager.h"
#include "Map.h"




namespace
{
	const float SCROLL_SPEED = 5.0f;
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

	if (GfxInputIsJustPressed(EGfxInputID_MouseLeft))				// Click on villager
	{
		const TGfxVec2 tMousePosition = TGfxVec2(float(GfxInputGetMousePositionX()), float(GfxInputGetMousePositionY())) + (TCamera::S_GetWorldPosition());

		for (int i = 0; i < TMap::S_GetVillagerCount(); i++)
		{
			TVillager * const pVillager = TMap::S_GetVillagers()[i];
			if (pVillager->IsMouseOver(tMousePosition))
			{
				s_pDraggedVillager = pVillager;
				s_bClicked = true;
				break;

			}
		}
	}

	else if (GfxInputIsPressed(EGfxInputID_MouseLeft))				// Drag villager
	{
		if (s_bClicked == true)
		{
			const TGfxVec2 tMousePosition = TGfxVec2(float(GfxInputGetMousePositionX()), float(GfxInputGetMousePositionY())) + (TCamera::S_GetWorldPosition());
			s_pDraggedVillager->SetPosition(tMousePosition);
			s_pDraggedVillager->SetFallVelocity(0.0f);
		}
	}

	if (GfxInputIsJustReleased(EGfxInputID_MouseLeft))
	{
		s_bClicked = false;
		s_pDraggedVillager = nullptr;
	}
}