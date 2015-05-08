
#include "flib.h"
#include "flib_vec2.h"
#include "Map.h"
#include "Entity.h"
#include "Dynamic.h"
#include "Villager.h"
#include "Building.h"
#include "House.h"
#include "Floor.h"
#include "HUD.h"
#include "Control.h"



namespace
{
	const int VILLAGERS_MAX_COUNT = 2000;

	const int HOUSES_MAX_COUNT = 60;
}


TVillager ** TMap::s_pVillagers = nullptr;
int TMap::s_iVillagersCount = 0;
THouse ** TMap::s_pHouses = nullptr;
int TMap::s_iHousesCount = 0;
TFloor * TMap::s_pFloor = nullptr;


void TMap::S_Initialize()
{
	THUD::S_Initialize();

	s_pVillagers = new TVillager *[VILLAGERS_MAX_COUNT]{ 0 };
	s_pHouses = new THouse *[HOUSES_MAX_COUNT]{ 0 };
	
	s_pFloor->S_Initialize();

	TVillager::S_Initialize();
	S_CreateVillager(TFloor::GetPosition() - TGfxVec2(0,500));
	S_CreateVillager(TFloor::GetPosition() - TGfxVec2(0, 500));
	S_CreateVillager(TFloor::GetPosition() - TGfxVec2(0, 500));

	THouse::S_Initialize();
	S_CreateHouse(TFloor::GetPosition() + TGfxVec2(300,0));

	TFloor::S_AddExtension(true);
	TFloor::S_AddExtension(false);
}

void TMap::S_CreateVillager(const TGfxVec2 & tPos)
{
	s_pVillagers[s_iVillagersCount] = new TVillager(tPos);
	s_iVillagersCount++;

	if (s_iVillagersCount == 4)
	{
		int yo = 0;
	}
}

void TMap::S_CreateHouse(const TGfxVec2 & tPos)
{
	s_pHouses[s_iHousesCount] = new THouse(tPos);
	s_iHousesCount++;
}


void TMap::S_Update()
{
	THUD::S_Update();
	TControl::CheckInput();

	for (int i = 0; i < s_iVillagersCount; i++)
	{
		s_pVillagers[i]->Update();

		if (i == 3)
		{
			int yo = 0;
		}
	}

	for (int i = 0; i < s_iHousesCount; i++)
	{
		s_pHouses[i]->Update();
	}
}


void TMap::S_Render()
{
	GfxClear(EGfxColor_Black);
	THUD::S_Render();
	TFloor::S_Render();

	for (int i = 0; i < s_iVillagersCount; i++)
	{
		s_pVillagers[i]->Render();
	}
	for (int i = 0; i < s_iHousesCount; i++)
	{
		s_pHouses[i]->Render();
	}
}
