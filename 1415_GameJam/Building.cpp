
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
#include "Profession.h"
#include "Worker.h"
#include "House.h"
#include "Workshop.h"
#include "Enclosure.h"



using namespace Generics;


TBuilding::TBuilding() :
TEntity(),
m_pAssignedVillagers(nullptr),
m_iAssignedVillagersCount(0)
{

}

TBuilding::TBuilding(const TGfxVec2 & tPos, const TGfxVec2 & tSize) :
TEntity(tPos, tSize),
m_pAssignedVillagers(nullptr),
m_iAssignedVillagersCount(0)
{

}

TBuilding::~TBuilding()
{
	if (m_pAssignedVillagers != nullptr)
	{
		for (int i = 0; i < m_iAssignedVillagersCount; i++)
		{
			m_pAssignedVillagers[i]->Unassign();
			m_pAssignedVillagers[i] = nullptr;
		}

		delete[] m_pAssignedVillagers;
		m_pAssignedVillagers = nullptr;
	}
}


void TBuilding::S_InitializeBuildings()
{
	THouse::S_Initialize();
	TWorkshop::S_Initialize();
	TEnclosure::S_Initialize();
}


void TBuilding::Update()
{
	SpecificUpdate();
}

bool TBuilding::DropCivilian(TVillager * pVillager)
{
	const TGfxVec2 tCurrentMouse = GetCurrentMouse();

	const bool bCollisionX = tCurrentMouse.x >= m_tPos.x - (m_tSize.x / 2.0f) && tCurrentMouse.x <= m_tPos.x + (m_tSize.x / 2.0f);
	const bool bCollisionY = tCurrentMouse.y >= m_tPos.y - m_tSize.y && tCurrentMouse.y <= m_tPos.y;

	if (bCollisionX && bCollisionY)
	{
		if (pVillager->IsOldEnough(m_iRequiredAge))
		{
			AssignVillager(pVillager);
		}

		return true;
	}
	
	return false;
}
