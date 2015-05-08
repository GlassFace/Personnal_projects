#include "flib.h"
#include "flib_vec2.h"
#include "generics.h"
#include "Control.h"
#include "Camera.h"
#include "Entity.h"
#include "Dynamic.h"
#include "Villager.h"
#include "Map.h"
#include "Bird.h"



using namespace Generics;

namespace
{
	const float SCROLL_SPEED = 9.0f;
}

TVillager * TControl::s_pDraggedVillager = nullptr;

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
	const TGfxVec2 tMousePosition = GetCurrentMouse();

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

		s_pDraggedVillager = nullptr;
	}
}