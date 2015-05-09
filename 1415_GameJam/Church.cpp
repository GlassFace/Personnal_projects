
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
#include "Priest.h"
#include "Building.h"
#include "Church.h"



using namespace Generics;

namespace
{
	const char * const CHURCH_TEXTURE_NAME = "Church.tga";


	const TGfxVec2 CHURCH_SIZE = TGfxVec2(184.0f, 181.0f);

	const int ASSIGNED_VILLAGERS_MAX = 3;
}


TGfxTexture * TChurch::s_pChurchTexture = nullptr;

TChurch::TChurch() :
TBuilding()
{
	m_pAssignedVillagers = new TVillager*[ASSIGNED_VILLAGERS_MAX];

	m_eBuildingType = EBuildingType_Church;

	m_pSprite = GfxSpriteCreate(s_pChurchTexture);
	GfxSpriteSetPivot(m_pSprite, (m_tSize.x / 2.0f), m_tSize.y);
	GfxSpriteSetPosition(m_pSprite, m_tPos.x, m_tPos.y);
}

TChurch::TChurch(const TGfxVec2 & tPos) :
TBuilding(tPos, CHURCH_SIZE)
{
	m_pAssignedVillagers = new TVillager*[ASSIGNED_VILLAGERS_MAX];

	m_eBuildingType = EBuildingType_Church;

	m_pSprite = GfxSpriteCreate(s_pChurchTexture);
	GfxSpriteSetPivot(m_pSprite, (m_tSize.x / 2.0f), m_tSize.y);
	GfxSpriteSetPosition(m_pSprite, m_tPos.x, m_tPos.y);
}

TChurch::~TChurch()
{

}


void TChurch::S_Initialize()
{
	s_pChurchTexture = GfxTextureLoad(CHURCH_TEXTURE_NAME);
}


bool TChurch::AssignVillager(TVillager * pVillager)
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

		TPriest * pProfession = new TPriest(pVillager);
		pVillager->SetProfession(pProfession, this);

		return true;
	}

	return false;
}

void TChurch::UnassignVillager(TVillager * pVillager)
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

float TChurch::S_GetSizeX()
{
	return CHURCH_SIZE.x;
}


void TChurch::SpecificRender()
{
	if (m_pAssignedVillagersSprite != nullptr)
	{
		GfxSpriteRender(m_pAssignedVillagersSprite);
	}
}
