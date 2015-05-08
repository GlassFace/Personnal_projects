
#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

class THouse;
class TFloor;
class TVillager;
class TBird;

class TMap
{
public:
	

	static void S_Initialize();

	static void S_CreateVillager(const TGfxVec2 & tPos);
	static void S_CreateHouse(const TGfxVec2 & tPos);
	static void S_CreateBird(const TGfxVec2 & tPos);

	static void S_DeleteVillager(TVillager * pVillager);
	static void S_DeleteHouse(THouse * pHouse);
	static void S_DeleteBird(TBird * pBird);


	static void S_Update();

	static TVillager ** S_GetVillagers()
	{
		return s_pVillagers;
	}

	static THouse ** S_GetHouses()
	{
		return s_pHouses;
	}

	static int S_GetVillagerCount()
	{
		return s_iVillagersCount;
	}

	static int S_GetHouseCount()
	{
		return s_iHousesCount;
	}


	static void S_Render();


private:

	static TGfxTexture * s_pBackGroundTexture;
	static TGfxSprite * s_pBackGroundSprite;

	static TVillager ** s_pVillagers;
	static int s_iVillagersCount;

	static TBird ** s_pBirds;
	static int s_iBirdsCount;

	static THouse ** s_pHouses;
	static int s_iHousesCount;

	static TFloor * s_pFloor;
};

#endif
