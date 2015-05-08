
#include "flib.h"
#include "flib_vec2.h"
#include "generics.h"
#include "Map.h"
#include "Entity.h"
#include "Dynamic.h"
#include "Villager.h"
#include "Profession.h"
#include "Building.h"
#include "House.h"
#include "Workshop.h"
#include "Floor.h"
#include "HUD.h"
#include "Control.h"
#include "Camera.h"
#include "Bird.h"



using namespace Generics;


namespace
{
	const char * BACKGROUND_TEXTURE = "Background.tga";

	const int VILLAGERS_MAX_COUNT = 2000;

	const int HOUSES_MAX_COUNT = 60;

	const float SIZE_BETWEEN_BUILDINGS_MIN = 64.0f;

	const int BIRDS_MAX_COUNT = 60;

	const float BIRDS_GENERATION_RATE = 30.f;
}


TGfxTexture * TMap::s_pBackGroundTexture = nullptr;
TGfxSprite * TMap::s_pBackGroundSprite = nullptr;

TVillager ** TMap::s_pVillagers = nullptr;
int TMap::s_iVillagersCount = 0;
TBuilding ** TMap::s_pBuildings = nullptr;
int TMap::s_iBuildingsCount = 0;
TBird ** TMap::s_pBirds = nullptr;
int TMap::s_iBirdsCount = 0;

TFloor * TMap::s_pFloor = nullptr;

int TMap::s_iLastTimeBirdGeneration = 0;


void TMap::S_Initialize()
{
	THUD::S_Initialize();

	s_pBackGroundTexture = GfxTextureLoad(BACKGROUND_TEXTURE);
	s_pBackGroundSprite = GfxSpriteCreate(s_pBackGroundTexture);
	GfxSpriteSetPosition(s_pBackGroundSprite, 0.0f, 0.0f);

	s_iLastTimeBirdGeneration = GfxTimeGetMilliseconds();

	TCamera::S_Initialize();
	s_pVillagers = new TVillager *[VILLAGERS_MAX_COUNT]{ 0 };
	s_pBuildings = new TBuilding *[HOUSES_MAX_COUNT]{ 0 };
	s_pBirds = new TBird *[BIRDS_MAX_COUNT]{ 0 };
	
	s_pFloor->S_Initialize();

	TVillager::S_Initialize();
	TProfession::S_InitializeProfessions();
	//S_CreateVillager(TFloor::GetPosition() - TGfxVec2(0.0f, 500.0f));
	S_CreateVillager(TFloor::GetPosition() - TGfxVec2(0.0f, 500.0f));
	S_CreateVillager(TFloor::GetPosition() - TGfxVec2(20.0f, 500.0f));

	TBuilding::S_InitializeBuildings();
	//S_CreateBuilding(EBuildingType_House, TFloor::GetPosition() + TGfxVec2(300.0f, 0.0f));
	//S_CreateBuilding(EBuildingType_House, TFloor::GetPosition() + TGfxVec2(0.0f, 0.0f));
	//S_CreateBuilding(EBuildingType_House, TFloor::GetPosition() + TGfxVec2(-300.0f, 0.0f));
	S_CreateBuilding(EBuildingType_Workshop, TFloor::GetPosition() + TGfxVec2(100.0f, 0.0f));

	TBird::S_Initialize();
	//S_CreateBird(TFloor::GetPosition() + TGfxVec2(-500, -500));
	


	//TFloor::S_AddExtension(false);
	//TFloor::S_AddExtension(false);
	//TFloor::S_AddExtension(true);
	//TFloor::S_AddExtension(true);
	//TFloor::S_AddExtension(true);
	//TFloor::S_AddExtension(true);
	//TFloor::S_AddExtension(true);
}

void TMap::S_CreateVillager(const TGfxVec2 & tPos)
{
	s_pVillagers[s_iVillagersCount] = new TVillager(tPos, s_iVillagersCount);
	s_iVillagersCount++;
}

void TMap::S_CreateBuilding(EBuildingType eBuildingToCreate, const TGfxVec2 & tPos)
{
	switch (eBuildingToCreate)
	{
	case EBuildingType_House:

		s_pBuildings[s_iBuildingsCount] = new THouse(tPos);

		s_iBuildingsCount++;

		break;

	case EBuildingType_Workshop:

		s_pBuildings[s_iBuildingsCount] = new TWorkshop(tPos);

		s_iBuildingsCount++;

		break;

	/*case EBuildingType_Tower:

		break;*/
	}
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
			s_pVillagers[s_iVillagersCount - 1] = nullptr;

			s_iVillagersCount--;

			return;
		}
	}
}

void TMap::S_DeleteHouse(THouse * pHouse)
{
	for (int i = 0;; i++)
	{
		if (s_pBuildings[i] == pHouse)
		{
			delete s_pBuildings[i];
			s_pBuildings[i] = s_pBuildings[s_iBuildingsCount - 1];
			s_pBuildings[s_iBuildingsCount - 1] = nullptr;

			s_iBuildingsCount--;

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
			s_pBirds[i] = s_pBirds[s_iBirdsCount - 1];
			s_pBirds[s_iBirdsCount - 1] = nullptr;

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
		if (!s_pBirds[i]->IsAlive())
		{
			S_DeleteBird(s_pBirds[i]);
		}
		else
		{
			s_pBirds[i]->Update();
		}
	}

	TCamera::S_Update();

	for (int i = 0; i < s_iBuildingsCount; i++)
	{
		s_pBuildings[i]->Update();
	}

	S_GenerateBird();
}

void TMap::S_AssignToBuilding(TVillager * pVillager)
{
	for (int i = 0; i < s_iBuildingsCount; i++)
	{
		if (s_pBuildings[i]->DropCivilian(pVillager))
		{
			return;
		}
	}
}

bool TMap::S_EnoughRoomToConstruct(const TGfxVec2 & tPos, const float tBuildingSizeX)
{
	const float fConstructionLeftBorder = tPos.x - (tBuildingSizeX / 2.0f) - SIZE_BETWEEN_BUILDINGS_MIN;
	const float fConstructionRightBorder = tPos.x + (tBuildingSizeX / 2.0f) + SIZE_BETWEEN_BUILDINGS_MIN;

	for (int i = 0; i < s_iBuildingsCount; i++)
	{
		const float fBuildingLeftBorder = s_pBuildings[i]->GetPos().x - (s_pBuildings[i]->GetSize().x / 2.0f);
		const float fBuildingRightBorder = s_pBuildings[i]->GetPos().x + (s_pBuildings[i]->GetSize().x / 2.0f);

		const bool bLeftBorderInTheAir = fConstructionLeftBorder < TFloor::GetPosition().x - TFloor::GetLeftSize();
		const bool bRightBorderInTheAir = fConstructionRightBorder > TFloor::GetPosition().x + TFloor::GetRightSize();

		if (fConstructionLeftBorder <= fBuildingRightBorder &&
			fConstructionRightBorder >= fBuildingLeftBorder ||
			bLeftBorderInTheAir || bRightBorderInTheAir)
	{
			return false;
		}
	}

	return true;
}

void TMap::S_GenerateBird()
{
	if (BIRDS_GENERATION_RATE * 1000.f < (GfxTimeGetMilliseconds() - s_iLastTimeBirdGeneration))
	{
		S_CreateBird(TFloor::GetPosition() + TGfxVec2(-500, 500));
		s_iLastTimeBirdGeneration = GfxTimeGetMilliseconds();
	}
}

void TMap::S_Render()
{
	GfxClear(EGfxColor_Black);
	
	if (s_pBackGroundSprite != nullptr)
	{
		GfxSpriteRender(s_pBackGroundSprite);
	}

	TFloor::S_Render();

	for (int i = 0; i < s_iBuildingsCount; i++)
	{
		s_pBuildings[i]->Render();
	}

	for (int i = 0; i < s_iVillagersCount; i++)
	{
		s_pVillagers[i]->Render();
	}

	for (int i = 0; i < s_iBirdsCount; i++)
	{
		s_pBirds[i]->Render();
	}

	THUD::S_Render();
}
