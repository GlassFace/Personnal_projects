
#include "flib.h"
#include "flib_vec2.h"
#include "generics.h"
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
	const char * const SPRITE_NAME = "Workshop.tga";

	const int ASSIGNED_VILLAGERS_MAX = 3;

	const TGfxVec2 WORKSHOP_SIZE = TGfxVec2(136.0f, 112.0f);
}


TGfxTexture * TWorkshop::s_pTexture = nullptr;

TWorkshop::TWorkshop() :
TBuilding(),
m_eBuildingToCreateType(EBuildingType_Workshop)
{
	m_eBuildingType = EBuildingType_Workshop;
}

TWorkshop::TWorkshop(const TGfxVec2 & tPos) :
TBuilding(tPos, WORKSHOP_SIZE),
m_eBuildingToCreateType(EBuildingType_Workshop)
{
	m_pAssignedVillagers = new TVillager*[ASSIGNED_VILLAGERS_MAX];

	m_eBuildingType = EBuildingType_Workshop;

	m_pSprite = GfxSpriteCreate(s_pTexture);
	GfxSpriteSetPivot(m_pSprite, (m_tSize.x / 2.0f), m_tSize.y);
	GfxSpriteSetPosition(m_pSprite, m_tPos.x, m_tPos.y);
}

TWorkshop::~TWorkshop()
{
	
}


void TWorkshop::S_Initialize()
{
	s_pTexture = GfxTextureLoad(SPRITE_NAME);
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
		m_pAssignedVillagers[m_iAssignedVillagersCount] = pVillager;
		m_iAssignedVillagersCount++;

		TWorker * pProfession = new TWorker(EBuildingType_Workshop);
		pVillager->SetProfession(pProfession, this);

		return true;
	}

	return false;
}

void TWorkshop::UnassignVillager(TVillager * pVillager)
{
	for (int i = 0;; i++)
	{
		if (m_pAssignedVillagers[i] == pVillager)
		{
			m_pAssignedVillagers[i]->Unassign();
			m_pAssignedVillagers[i] = m_pAssignedVillagers[m_iAssignedVillagersCount - 1];
			m_pAssignedVillagers[m_iAssignedVillagersCount - 1] = nullptr;
			m_iAssignedVillagersCount--;
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
		if (m_eBuildingToCreateType == EBuildingType_Tower)
		{
			m_eBuildingToCreateType = EBuildingType_House;
		}

		for (int i = 0; i < m_iAssignedVillagersCount; i++)
		{
			static_cast<TWorker*>(m_pAssignedVillagers[i]->GetProfession())->SetBuildingsToCreate(m_eBuildingToCreateType);
		}
	}
}

float TWorkshop::S_GetSizeX()
{
	return WORKSHOP_SIZE.x;
}
