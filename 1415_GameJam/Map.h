
#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

class THouse;
class TFloor;
class TVillager;

class TMap
{
public:
	

	static void S_Initialize();

	static void S_CreateVillager(const TGfxVec2 & tPos);
	static void S_CreateHouse(const TGfxVec2 & tPos);


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

	static TVillager ** s_pVillagers;
	static int s_iVillagersCount;

	static THouse ** s_pHouses;
	static int s_iHousesCount;

	static TFloor * s_pFloor;
};

#endif
