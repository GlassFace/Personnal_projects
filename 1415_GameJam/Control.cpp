#include "flib.h"
#include "flib_vec2.h"
#include "generics.h"
#include "Control.h"
#include "Camera.h"
#include "Entity.h"
#include "Dynamic.h"
#include "Villager.h"
#include "Background.h"
#include "Parallax.h"
#include "Map.h"
#include "Bird.h"



using namespace Generics;

namespace
{
	const float SCROLL_SPEED = 9.0f;

	const float DRAG_VECTOR_MAX_LENGHT = 24.0f;
	const float SPEED_DECREASE = 2.0f;				// Per millisecond
}

TVillager * TControl::s_pDraggedVillager = nullptr;

TControl::TControl()
{

}

TControl::~TControl()
{

}


void TControl::S_Update()
{
	S_CheckInput();
}

void TControl::S_CheckInput()
{
	const TGfxVec2 tMousePosition = GetCurrentMouse();
	const TGfxVec2 tMousePosScreen = TGfxVec2(float(GfxGetCurrentMouseX()), float(GfxGetCurrentMouseY()));

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
		for (int i = 0; i < TMap::S_GetBirdsCount(); i++)
		{
			TBird * pBird = TMap::S_GetBirds()[i];

			if (pBird->IsMouseOver(tMousePosition))
			{
				pBird->TakeHit();
				break;
			}
		}

		for (int i = 0; i < TMap::S_GetVillagerCount(); i++)
		{
			TVillager * pVillager = TMap::S_GetVillagers()[i];

			if (pVillager->IsMouseOver(tMousePosition))
			{
				s_pDraggedVillager = pVillager;

				break;
			}
		}
	}

	else if (GfxInputIsPressed(EGfxInputID_MouseLeft) &&
			 s_pDraggedVillager != nullptr)							// Drag villager
	{
		s_pDraggedVillager->SetPosition(tMousePosition);
		s_pDraggedVillager->SetFallVelocity(0.0f);
	}

	if (GfxInputIsJustReleased(EGfxInputID_MouseLeft) &&
		s_pDraggedVillager != nullptr)
	{
		TMap::S_AssignToBuilding(s_pDraggedVillager);


		TGfxVec2 tForce = tMousePosScreen - TGfxVec2(float(GfxGetPreviousMouseX()), float(GfxGetPreviousMouseY()));

		if (tForce.SquaredLength() > DRAG_VECTOR_MAX_LENGHT * DRAG_VECTOR_MAX_LENGHT)
		{
			tForce = tForce.Normalize() * DRAG_VECTOR_MAX_LENGHT;
		}

		s_pDraggedVillager->AddForce(tForce);

		s_pDraggedVillager = nullptr;
	}
}
