
#ifndef HOUSE_H_INCLUDED
#define HOUSE_H_INCLUDED

#include "Building.h"

class THouse : public TBuilding
{
public:

	THouse();
	THouse(const TGfxVec2 & tPos);
	~THouse();


	static void S_Initialize();


	void SpecificUpdate();

	bool AssignVillager(TVillager *) { return false; };
	void UnassignVillager(TVillager *) {};

	static float S_GetSizeX();


	void SpecificRender() {};


private:

	static TGfxTexture * s_pTexture;

	int m_iLastSpawnTime;
};

#endif
