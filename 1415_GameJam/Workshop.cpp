
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
	const int ASSIGNED_VILLAGERS_MAX = 3;

	const TGfxVec2 WORKSHOP_SIZE = TGfxVec2(96.0f, 96.0f);
}


TWorkshop::TWorkshop() :
TBuilding()
{

}

TWorkshop::TWorkshop(const TGfxVec2 & tPos) :
TBuilding(tPos, WORKSHOP_SIZE)
{
	m_pAssignedVillagers = new TVillager*[ASSIGNED_VILLAGERS_MAX];
}

TWorkshop::~TWorkshop()
{
	
}


void TWorkshop::SpecificUpdate()
{
	GetInput();
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
		m_eBuildingType = EBuildingType((m_eBuildingType + 1) % BUILDINGS_TYPES_COUNT);

		for (int i = 0; i < m_iAssignedVillagersCount; i++)
		{
			static_cast<TWorker*>(m_pAssignedVillagers[i])->SetBuildingsToCreate(m_eBuildingType);
		}
	}
}
