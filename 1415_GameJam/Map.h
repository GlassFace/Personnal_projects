
#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

enum EBuildingType
{
	EBuildingType_House,
	EBuildingType_Workshop,
	EBuildingType_Tower
};

class TBuilding;
class THouse;
class TFloor;
class TVillager;
class TBird;

class TMap
{
public:
	
	/*		Update		*/

	static void S_Initialize();

	static void S_CreateVillager(const TGfxVec2 & tPos);
	static void S_CreateBuilding(EBuildingType eBuildingToCreate, const TGfxVec2 & tPos);
	static void S_CreateBird(const TGfxVec2 & tPos);

	static void S_DeleteVillager(TVillager * pVillager);
	static void S_DeleteHouse(THouse * pHouse);
	static void S_DeleteBird(TBird * pBird);


	/*		Update		*/

	static void S_Update();

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

	/*		Render		*/

	static void S_Render();


private:

	static TGfxTexture * s_pBackGroundTexture;
	static TGfxSprite * s_pBackGroundSprite;

	static TVillager ** s_pVillagers;
	static int s_iVillagersCount;

	static TBird ** s_pBirds;
	static int s_iBirdsCount;

	static TBuilding ** s_pBuildings;
	static int s_iBuildingsCount;

	static TFloor * s_pFloor;
};

#endif
