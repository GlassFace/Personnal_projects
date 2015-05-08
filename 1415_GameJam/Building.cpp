
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
TEntity()
{

}

TBuilding::TBuilding(const TGfxVec2 & tPos, const TGfxVec2 & tSize) :
TEntity(tPos, tSize)
{

}

TBuilding::~TBuilding()
{

}


void TBuilding::Update()
{
	SpecificUpdate();
}

void TBuilding::DropCivilian(TVillager & tVillager) const
{
	if (tVillager.IsOldEnough(m_iRequiredAge))
	{
		switch (m_eBuildingType)
		{
		case EBuildingType_Workshop:
		{
			TWorker * pProfession = new TWorker(EBuildingType_Workshop);
			tVillager.SetProfession(pProfession);

			break;
		}
		}
	}
}
