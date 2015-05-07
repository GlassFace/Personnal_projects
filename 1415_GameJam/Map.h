
#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

class TMap
{
public:

	static void S_Initialize();

	static void S_CreateVillager(const TGfxVec2 & tPos);
	static void S_CreateHouse(const TGfxVec2 & tPos);


	static void S_Update();


	static void S_Render();


private:

	static TVillager ** s_pVillagers;
	static int s_iVillagersCount;

	static THouse ** s_pHouses;
	static int s_iHousesCount;
};

#endif
