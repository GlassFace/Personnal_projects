
#include "flib.h"
#include "flib_vec2.h"
#include "generics.h"
#include "Background.h"
#include "Parallax.h"
#include "Map.h"
#include "Entity.h"
#include "Dynamic.h"
#include "Anim.h"
#include "Villager.h"
#include "Building.h"
#include "Workshop.h"
#include "Profession.h"
#include "Worker.h"



using namespace Generics;

namespace
{
	const char * const SPRITE_NAME = "Workshop\\Workshop.tga";
	const char * const ICONS_TILESET_NAME = "Workshop\\Workshop_icons.tga";

	const int ASSIGNED_VILLAGERS_MAX = 3;

	const TGfxVec2 WORKSHOP_SIZE = TGfxVec2(136.0f, 112.0f);
	const TGfxVec2 ICONS_SIZE = TGfxVec2(96.0f, 96.0f);
}


TGfxTexture * TWorkshop::s_pWorkshopTexture = nullptr;
TGfxTexture * TWorkshop::s_pIconsTileSet = nullptr;

TWorkshop::TWorkshop() :
TBuilding(),
m_eBuildingToCreateType(EBuildingType_Workshop)
{
	m_eBuildingType = EBuildingType_Workshop;
}

TWorkshop::TWorkshop(const TGfxVec2 & tPos) :
TBuilding(tPos, WORKSHOP_SIZE),
m_pIconSprite(nullptr),
m_eBuildingToCreateType(EBuildingType_Workshop)
{
	m_pAssignedVillagers = new TVillager*[ASSIGNED_VILLAGERS_MAX];


	m_pIconSprite = GfxSpriteCreate(s_pIconsTileSet);
	GfxSpriteSetCutout(m_pIconSprite, 0, 0, int(ICONS_SIZE.x), int(ICONS_SIZE.y));
	GfxSpriteSetPivot(m_pIconSprite, ICONS_SIZE.x / 2.0f, ICONS_SIZE.y + m_tSize.y);
	GfxSpriteSetPosition(m_pIconSprite, m_tPos.x, m_tPos.y - m_tSize.y);


	m_eBuildingType = EBuildingType_Workshop;

	m_pSprite = GfxSpriteCreate(s_pWorkshopTexture);
	GfxSpriteSetPivot(m_pSprite, (m_tSize.x / 2.0f), m_tSize.y);
	GfxSpriteSetPosition(m_pSprite, m_tPos.x, m_tPos.y);
}

TWorkshop::~TWorkshop()
{
	if (m_pIconSprite != nullptr)
	{
		GfxSpriteDestroy(m_pIconSprite);
		m_pIconSprite = nullptr;
	}
}


void TWorkshop::S_Initialize()
{
	s_pWorkshopTexture = GfxTextureLoad(SPRITE_NAME);
	s_pIconsTileSet = GfxTextureLoad(ICONS_TILESET_NAME);
}

void TWorkshop::SpecificUpdate()
{
	if (GfxInputIsJustPressed(EGfxInputID_MouseLeft))
	{
		GetInput();
	}
}

bool TWorkshop::AssignVillager(TVillager * pVillager)
{
	if (m_iAssignedVillagersCount < ASSIGNED_VILLAGERS_MAX)
	{
		for (int i = 0; i < m_iAssignedVillagersCount; i++)
		{
			if (m_pAssignedVillagers[i] == pVillager)
			{
				return false;
			}
		}

		m_pAssignedVillagers[m_iAssignedVillagersCount] = pVillager;
		m_iAssignedVillagersCount++;

		TWorker * pProfession = new TWorker(m_eBuildingToCreateType, pVillager);
		pVillager->SetProfession(pProfession, this);

		return true;
	}

	return false;
}

void TWorkshop::UnassignVillager(TVillager * pVillager)
{
	for (int i = 0; i < m_iAssignedVillagersCount; i++)
	{
		if (m_pAssignedVillagers[i] == pVillager)
		{
			m_pAssignedVillagers[i]->Unassign();
			m_pAssignedVillagers[i] = nullptr;
			m_pAssignedVillagers[i] = m_pAssignedVillagers[m_iAssignedVillagersCount - 1];
			m_pAssignedVillagers[m_iAssignedVillagersCount - 1] = nullptr;
			m_iAssignedVillagersCount--;

			return;
		}
	}
}

void TWorkshop::GetInput()
{
	const TGfxVec2 tCurrentMouse = GetCurrentMouse();

	const bool bCollisionX = tCurrentMouse.x >= m_tPos.x - (m_tSize.x / 2.0f) && tCurrentMouse.x <= m_tPos.x + (m_tSize.x / 2.0f);
	const bool bCollisionY = tCurrentMouse.y >= m_tPos.y - m_tSize.y && tCurrentMouse.y <= m_tPos.y;

	if (bCollisionX && bCollisionY)
	{
		m_eBuildingToCreateType = EBuildingType((m_eBuildingToCreateType + 1) % BUILDINGS_TYPES_COUNT);

		for (int i = 0; i < m_iAssignedVillagersCount; i++)
		{
			static_cast<TWorker*>(m_pAssignedVillagers[i]->GetProfession())->SetBuildingsToCreate(m_eBuildingToCreateType);
		}


		int iCutoutX = 0;

		switch (m_eBuildingToCreateType)
		{
		case EBuildingType_House:

			iCutoutX = 0;

			break;

		case EBuildingType_Workshop:

			iCutoutX = 1;

			break;

		case EBuildingType_Barricade:

			iCutoutX = 2;

			break;

		case EBuildingType_Enclosure:

			iCutoutX = 3;

			break;

		case EBuildingType_Garrison:

			iCutoutX = 4;

			break;

		case EBuildingType_Church:

			iCutoutX = 5;

			break;
		}

		GfxSpriteSetCutout(m_pIconSprite, iCutoutX * int(ICONS_SIZE.x), 0, int(ICONS_SIZE.x), int(ICONS_SIZE.y));
	}
}

float TWorkshop::S_GetSizeX()
{
	return WORKSHOP_SIZE.x;
}


void TWorkshop::SpecificRender()
{
	if (m_pIconSprite != nullptr)
	{
		GfxSpriteRender(m_pIconSprite);
		GfxSpriteRender(m_pAssignedVillagersSprite);
	}
}
