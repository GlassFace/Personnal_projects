
#include "flib.h"
#include "flib_vec2.h"
#include "generics.h"
#include "Map.h"
#include "Entity.h"
#include "Dynamic.h"
#include "Anim.h"
#include "Villager.h"
#include "Building.h"
#include "Profession.h"
#include "Worker.h"


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


void TBuilding::Update()
{
	SpecificUpdate();
}

void TBuilding::DropCivilian(TVillager & tVillager)
{
	if (tVillager.IsOldEnough(m_iRequiredAge))
	{
		AssignVillager(&tVillager);
	}
}
