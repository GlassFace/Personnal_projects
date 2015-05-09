#include "flib.h"
#include "flib_vec2.h"
#include "generics.h"
#include "Camera.h"
#include "Floor.h"
#include "Entity.h"
#include "Dynamic.h"
#include "Villager.h"
#include "Background.h"
#include "Parallax.h"
#include "Map.h"
#include "Building.h"
#include "House.h"
#include "Workshop.h"
#include "Bird.h"



TGfxVec2 TCamera::m_tWorldPosition;

TCamera::TCamera()
{

}

TCamera::~TCamera()
{

}


void TCamera::S_Initialize()
{
	m_tWorldPosition = TGfxVec2(GfxGetDisplaySizeX() / 2.f, 0);
}

void TCamera::S_Update()
{
	S_UpdateLocal();
}

void TCamera::S_UpdateLocal()
{
	TGfxVec2 tLocalPosition = TFloor::GetPosition() - m_tWorldPosition;
	tLocalPosition.x += GfxGetDisplaySizeX() / 2.f;
	GfxSpriteSetPosition(TFloor::GetPlatformSprite(), tLocalPosition.x, tLocalPosition.y);

	for (int i = 0; i < 30; i++)
	{
		TGfxSprite * pSprite = TFloor::GetExtensionSprite()[i];
		if (pSprite != 0)
		{
			TGfxVec2 * tWorldPosition = TFloor::GetExtensionsPositions()[i];
			TGfxVec2 tLocalPosition = *tWorldPosition - m_tWorldPosition;
			tLocalPosition.x += GfxGetDisplaySizeX() / 2.f;
			GfxSpriteSetPosition(pSprite, tLocalPosition.x, tLocalPosition.y);
		}
	}

	for (int i = 0; i < TMap::S_GetVillagerCount(); i++)
	{
		TVillager * pVillager = TMap::S_GetVillagers()[i];
		TGfxVec2 tLocalPosition = pVillager->GetPos() - m_tWorldPosition;
		tLocalPosition.x += GfxGetDisplaySizeX() / 2.f;
		GfxSpriteSetPosition(pVillager->GetSprite(), tLocalPosition.x, tLocalPosition.y);
		pVillager->SetLocalName(tLocalPosition);
	}

	for (int i = 0; i < TMap::S_GetBuildingsCount(); i++)
	{
		TBuilding * pBuilding = TMap::S_GetBuildings()[i];
		TGfxVec2 tLocalPosition = pBuilding->GetPos() - m_tWorldPosition;
		tLocalPosition.x += GfxGetDisplaySizeX() / 2.0f;
		GfxSpriteSetPosition(pBuilding->GetAssignedVillager(), tLocalPosition.x, GfxSpriteGetPositionY(pBuilding->GetAssignedVillager()));
		GfxSpriteSetPosition(pBuilding->GetSprite(), tLocalPosition.x, tLocalPosition.y);
		
		if (pBuilding->GetBuildingType() == EBuildingType_Workshop)
		{
			GfxSpriteSetPosition(static_cast<TWorkshop*>(pBuilding)->GetIconSprite(), tLocalPosition.x, tLocalPosition.y);
		}
	}

	for (int i = 0; i < TMap::S_GetBirdsCount(); i++)
	{
		TBird * pBird = TMap::S_GetBirds()[i];
		TGfxVec2 tLocalPosition = pBird->GetPosition() - m_tWorldPosition;
		tLocalPosition.x += GfxGetDisplaySizeX() / 2.f;
		for (int i = 0; i < NBR_BLOOD_SPRITE; i++)
		{
			GfxSpriteSetPosition(pBird->GetBloodSprite()[i]->m_pSprite, tLocalPosition.x, tLocalPosition.y);
		}
		GfxSpriteSetPosition(pBird->GetSprite(), tLocalPosition.x, tLocalPosition.y);
		
	}
}
void TCamera::S_Render()
{

}

void TCamera::S_Scroll(float fXVelocity)
{
	m_tWorldPosition.x += fXVelocity;
	
	if (m_tWorldPosition.x < (TFloor::GetPosition().x - TFloor::GetLeftSize())- 200.f)
	{
		m_tWorldPosition.x = TFloor::GetPosition().x - TFloor::GetLeftSize() - 200.f;
	}
	if (m_tWorldPosition.x >(TFloor::GetPosition().x + TFloor::GetRightSize()) )
	{
		m_tWorldPosition.x = TFloor::GetPosition().x + TFloor::GetRightSize();
	}
}