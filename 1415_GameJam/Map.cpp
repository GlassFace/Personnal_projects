
#include "flib.h"
#include "flib_vec2.h"
#include "generics.h"
#include "Map.h"
#include "Entity.h"
#include "Dynamic.h"
#include "Villager.h"
#include "Building.h"
#include "House.h"
#include "Floor.h"
#include "HUD.h"
#include "Control.h"
#include "Camera.h"
#include "Bird.h"



namespace
{
	const char * BACKGROUND_TEXTURE = "Background.tga";

	const int VILLAGERS_MAX_COUNT = 2000;

	const int HOUSES_MAX_COUNT = 60;

	const int BIRDS_MAX_COUNT = 60;
}


TGfxTexture * TMap::s_pBackGroundTexture = nullptr;
TGfxSprite * TMap::s_pBackGroundSprite = nullptr;

TVillager ** TMap::s_pVillagers = nullptr;
int TMap::s_iVillagersCount = 0;
THouse ** TMap::s_pHouses = nullptr;
int TMap::s_iHousesCount = 0;
TBird ** TMap::s_pBirds = nullptr;
int TMap::s_iBirdsCount = 0;

TFloor * TMap::s_pFloor = nullptr;


void TMap::S_Initialize()
{
	THUD::S_Initialize();

	s_pBackGroundTexture = GfxTextureLoad(BACKGROUND_TEXTURE);
	s_pBackGroundSprite = GfxSpriteCreate(s_pBackGroundTexture);
	GfxSpriteSetPosition(s_pBackGroundSprite, 0.0f, 0.0f);

	TCamera::S_Initialize();
	s_pVillagers = new TVillager *[VILLAGERS_MAX_COUNT]{ 0 };
	s_pHouses = new THouse *[HOUSES_MAX_COUNT]{ 0 };
	s_pBirds = new TBird *[BIRDS_MAX_COUNT]{ 0 };
	
	s_pFloor->S_Initialize();

	TVillager::S_Initialize();
	S_CreateVillager(TFloor::GetPosition() - TGfxVec2(0,500));
	S_CreateVillager(TFloor::GetPosition() - TGfxVec2(0, 500));
	S_CreateVillager(TFloor::GetPosition() - TGfxVec2(0, 500));

	THouse::S_Initialize();
	S_CreateHouse(TFloor::GetPosition() + TGfxVec2(300,0));
	S_CreateHouse(TFloor::GetPosition() + TGfxVec2(0, 0));
	S_CreateHouse(TFloor::GetPosition() + TGfxVec2(-300, 0));

	TBird::S_Initialize();
	S_CreateBird(TFloor::GetPosition() + TGfxVec2(-500, -500));
	


	TFloor::S_AddExtension(false);
	TFloor::S_AddExtension(false);
	TFloor::S_AddExtension(true);
	TFloor::S_AddExtension(true);
	TFloor::S_AddExtension(true);
	TFloor::S_AddExtension(true);
	TFloor::S_AddExtension(true);
}

void TMap::S_CreateVillager(const TGfxVec2 & tPos)
{
	s_pVillagers[s_iVillagersCount] = new TVillager(tPos);
	s_iVillagersCount++;
}

void TMap::S_CreateHouse(const TGfxVec2 & tPos)
{
	s_pHouses[s_iHousesCount] = new THouse(tPos);
	s_iHousesCount++;
}
void TMap::S_CreateBird(const TGfxVec2 & tPos)
{
	s_pBirds[s_iBirdsCount] = new TBird(tPos);
	s_pBirds[s_iBirdsCount]->Initialize();
	s_iBirdsCount++;
}

void TMap::S_DeleteVillager(TVillager * pVillager)
{
	for (int i = 0;; i++)
	{
		if (s_pVillagers[i] == pVillager)
		{
			delete s_pVillagers[i];
			s_pVillagers[i] = s_pVillagers[s_iVillagersCount - 1];
			s_pVillagers[s_iVillagersCount] = nullptr;

			s_iVillagersCount--;

			return;
		}
	}
}

void TMap::S_DeleteHouse(THouse * pHouse)
{
	for (int i = 0;; i++)
	{
		if (s_pHouses[i] == pHouse)
		{
			delete s_pHouses[i];
			s_pHouses[i] = s_pHouses[s_iHousesCount];
			s_pHouses[s_iHousesCount] = nullptr;

			s_iHousesCount--;

			return;
		}
	}
}
void TMap::S_DeleteBird(TBird * pBird)
{
	for (int i = 0;; i++)
	{
		if (s_pBirds[i] == pBird)
		{
			delete s_pBirds[i];
			s_pBirds[i] = s_pBirds[s_iBirdsCount];
			s_pBirds[s_iBirdsCount] = nullptr;

			s_iBirdsCount--;

			return;
		}
	}
}


void TMap::S_Update()
{
	THUD::S_Update();
	TControl::CheckInput();

	for (int i = 0; i < s_iVillagersCount; i++)
	{
		s_pVillagers[i]->Update();

		if (!s_pVillagers[i]->IsAlive())
		{
			S_DeleteVillager(s_pVillagers[i]);

			i--;
		}
	}

	for (int i = 0; i < s_iBirdsCount; i++)
	{
		s_pBirds[i]->Update();
	}

	TCamera::S_Update();

	for (int i = 0; i < s_iHousesCount; i++)
	{
		s_pHouses[i]->Update();
	}
}


void TMap::S_Render()
{
	GfxClear(EGfxColor_Black);
	
	if (s_pBackGroundSprite != nullptr)
	{
		GfxSpriteRender(s_pBackGroundSprite);
	}

	THUD::S_Render();
	TFloor::S_Render();

	for (int i = 0; i < s_iHousesCount; i++)
	{
		s_pHouses[i]->Render();
	}

	for (int i = 0; i < s_iVillagersCount; i++)
	{
		s_pVillagers[i]->Render();
	}

	for (int i = 0; i < s_iBirdsCount; i++)
	{
		s_pBirds[i]->Render();
	}
}
