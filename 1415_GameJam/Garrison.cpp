
#include "flib.h"
#include "flib_vec2.h"
#include "generics.h"
#include "Background.h"
#include "Parallax.h"
#include "Map.h"
#include "Entity.h"
#include "Dynamic.h"
#include "Anim.h"
#include "Profession.h"
#include "Villager.h"
#include "Millitary.h"
#include "Building.h"
#include "Garrison.h"



using namespace Generics;

namespace
{
	const char * const GARRISON_TEXTURE_NAME = "Garrison.tga";

	const TGfxVec2 GARRISON_SIZE = TGfxVec2(136.0f, 80.0f);

	const int ASSIGNED_VILLAGERS_MAX = 2;
}


TGfxTexture * TGarrison::s_pGarrisonTexture = nullptr;

TGarrison::TGarrison() :
TBuilding()
{
	m_pAssignedVillagers = new TVillager*[ASSIGNED_VILLAGERS_MAX];

	m_eBuildingType = EBuildingType_Enclosure;

	m_pSprite = GfxSpriteCreate(s_pGarrisonTexture);
	GfxSpriteSetPivot(m_pSprite, (m_tSize.x / 2.0f), m_tSize.y);
	GfxSpriteSetPosition(m_pSprite, m_tPos.x, m_tPos.y);
}

TGarrison::TGarrison(const TGfxVec2 & tPos) :
TBuilding(tPos, GARRISON_SIZE)
{
	m_pAssignedVillagers = new TVillager*[ASSIGNED_VILLAGERS_MAX];

	m_eBuildingType = EBuildingType_Enclosure;

	m_pSprite = GfxSpriteCreate(s_pGarrisonTexture);
	GfxSpriteSetPivot(m_pSprite, (m_tSize.x / 2.0f), m_tSize.y);
	GfxSpriteSetPosition(m_pSprite, m_tPos.x, m_tPos.y);
}

TGarrison::~TGarrison()
{

}


void TGarrison::S_Initialize()
{
	s_pGarrisonTexture = GfxTextureLoad(GARRISON_TEXTURE_NAME);
}


bool TGarrison::AssignVillager(TVillager * pVillager)
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

		//TMillitary * pProfession = new TMillitary(pVillager);
		//pVillager->SetProfession(pProfession, this);

		return true;
	}

	return false;
}

void TGarrison::UnassignVillager(TVillager * pVillager)
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

float TGarrison::S_GetSizeX()
{
	return GARRISON_SIZE.x;
}
