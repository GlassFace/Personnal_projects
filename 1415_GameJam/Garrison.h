
#ifndef GARRISON_H_INCLUDED
#define GARRISON_H_INCLUDED

class TGarrison : public TBuilding
{
public:

	TGarrison();
	TGarrison(const TGfxVec2 & tPos);
	~TGarrison();


	static void S_Initialize();


	void SpecificUpdate() {};

	static float S_GetSizeX();

	bool AssignVillager(TVillager * pVillager);
	void UnassignVillager(TVillager * pVillager);


	void SpecificRender() {};


private:

	static TGfxTexture * s_pGarrisonTexture;
};

#endif
