
#include "flib.h"
#include "flib_vec2.h"
#include "generics.h"
#include "Map.h"
#include "Entity.h"
#include "Dynamic.h"
#include "Anim.h"
#include "Villager.h"
#include "Building.h"
#include "Enclosure.h"



using namespace Generics;

namespace
{
	const char * const ENCLOSURE_TEXTURE_NAME = "Enclosure.tga";

	const TGfxVec2 ENCLOSURE_SIZE = TGfxVec2(176.0f, 72.0f);

	const int ASSIGNED_VILLAGERS_MAX = 3;

	const int MAX_TIME_IN = 6 * SECONDS;
}


TGfxTexture * TEnclosure::s_pEnclosureTexture = nullptr;

TEnclosure::TEnclosure() :
TBuilding(),
m_pResidentsEnteringTime(nullptr)
{
	m_pAssignedVillagers = new TVillager*[ASSIGNED_VILLAGERS_MAX];
	m_pResidentsEnteringTime = new int[ASSIGNED_VILLAGERS_MAX]{ 0 };

	m_eBuildingType = EBuildingType_Enclosure;

	m_pSprite = GfxSpriteCreate(s_pEnclosureTexture);
	GfxSpriteSetPivot(m_pSprite, (m_tSize.x / 2.0f), m_tSize.y);
	GfxSpriteSetPosition(m_pSprite, m_tPos.x, m_tPos.y);
}

TEnclosure::TEnclosure(const TGfxVec2 & tPos) :
TBuilding(tPos, ENCLOSURE_SIZE),
m_pResidentsEnteringTime(nullptr)
{
	m_pAssignedVillagers = new TVillager*[ASSIGNED_VILLAGERS_MAX];
	m_pResidentsEnteringTime = new int[ASSIGNED_VILLAGERS_MAX]{ 0 };

	m_eBuildingType = EBuildingType_Enclosure;

	m_pSprite = GfxSpriteCreate(s_pEnclosureTexture);
	GfxSpriteSetPivot(m_pSprite, (m_tSize.x / 2.0f), m_tSize.y);
	GfxSpriteSetPosition(m_pSprite, m_tPos.x, m_tPos.y);
}

TEnclosure::~TEnclosure()
{
	if (m_pResidentsEnteringTime != nullptr)
	{
		delete[] m_pResidentsEnteringTime;
		m_pResidentsEnteringTime = nullptr;
	}
}


void TEnclosure::S_Initialize()
{
	s_pEnclosureTexture = GfxTextureLoad(ENCLOSURE_TEXTURE_NAME);
}


void TEnclosure::SpecificUpdate()
{
	for (int i = 0; i < m_iAssignedVillagersCount; i++)
	{
		if (GfxTimeGetMilliseconds() - m_pResidentsEnteringTime[i] >= MAX_TIME_IN)
		{
			UnassignVillager(m_pAssignedVillagers[i]);
			i--;
		}
	}
}

bool TEnclosure::AssignVillager(TVillager * pVillager)
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
		m_pResidentsEnteringTime[m_iAssignedVillagersCount] = GfxTimeGetMilliseconds();
		m_iAssignedVillagersCount++;

		pVillager->SetProfession(nullptr, this);

		return true;
	}

	return false;
}

void TEnclosure::UnassignVillager(TVillager * pVillager)
{
	for (int i = 0; i < m_iAssignedVillagersCount; i++)
	{
		if (m_pAssignedVillagers[i] == pVillager)
		{
			m_pAssignedVillagers[i]->Unassign();
			m_pAssignedVillagers[i] = nullptr;
			m_pAssignedVillagers[i] = m_pAssignedVillagers[m_iAssignedVillagersCount - 1];
			m_pResidentsEnteringTime[i] = m_pResidentsEnteringTime[m_iAssignedVillagersCount - 1];
			m_pAssignedVillagers[m_iAssignedVillagersCount - 1] = nullptr;
			m_pResidentsEnteringTime[m_iAssignedVillagersCount - 1] = 0;
			m_iAssignedVillagersCount--;

			return;
		}
	}
}

float TEnclosure::S_GetSizeX()
{
	return ENCLOSURE_SIZE.x;
}
