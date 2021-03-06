
#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

enum EBuildingType : int
{
	EBuildingType_House,
	EBuildingType_Workshop,
	EBuildingType_Barricade,
	EBuildingType_Enclosure,
	EBuildingType_Garrison,
	EBuildingType_Church
};

const int BUILDINGS_TYPES_COUNT = 6;

class TBuilding;
class THouse;
class TFloor;
class TVillager;
class TBird;
class TMeteorite;

class TMap
{
public:
	
	/*		Update		*/

	static void S_Initialize();

	static void S_CreateVillager(const TGfxVec2 & tPos);
	static void S_CreateBuilding(EBuildingType eBuildingToCreate, const TGfxVec2 & tPos);
	static void S_CreateBird(const TGfxVec2 & tPos);
	static void S_CreateMeteorite(const TGfxVec2 & tPos);

	static void S_DeleteVillager(TVillager * pVillager);
	static void S_DeleteBuilding(TBuilding * pBuilding);
	static void S_DeleteBird(TBird * pBird);
	static void S_DeleteMeteorite(TMeteorite * pMeteorite);


	/*		Update		*/

	static void S_Update();

	static void S_AssignToBuilding(TVillager * pVillager);

	static bool S_EnoughRoomToConstruct(const TGfxVec2 & tPos, const float tBuildingSizeX);

	/*		Getters		*/

	static TVillager ** S_GetVillagers()
	{
		return s_pVillagers;
	}

	static TBuilding ** S_GetBuildings()
	{
		return s_pBuildings;
	}

	static TBird ** S_GetBirds()
	{
		return s_pBirds;
	}


	static int S_GetVillagerCount()
	{
		return s_iVillagersCount;
	}

	static int S_GetBuildingsCount()
	{
		return s_iBuildingsCount;
	}
	static int S_GetBirdsCount()
	{
		return s_iBirdsCount;
	}

	static void S_GenerateBird();
	
	static void S_GenerateMeteorites();

	static void S_Render();


private:

	static TParallax * s_pParallax;

	static TGfxTexture * s_pBackGroundTexture;
	static TGfxSprite * s_pBackGroundSprite;

	static TVillager ** s_pVillagers;
	static int s_iVillagersCount;

	static TBird ** s_pBirds;
	static int s_iBirdsCount;

	static TBuilding ** s_pBuildings;
	static int s_iBuildingsCount;

	static TFloor * s_pFloor;

	static TMeteorite ** s_pMeteorites;
	static int s_iMeteoritesCount;

	static int s_iLastTimeBirdGeneration;

	static int s_iLastTimeMeteoriteGeneration;
};

#endif
