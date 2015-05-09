
#ifndef CHURCH_H_INCLUDED
#define CHURCH_H_INCLUDED

class TChurch : public TBuilding
{
public:

	TChurch();
	TChurch(const TGfxVec2 & tPos);
	~TChurch();


	static void S_Initialize();


	void SpecificUpdate() {};

	static float S_GetSizeX();

	bool AssignVillager(TVillager * pVillager);
	void UnassignVillager(TVillager * pVillager);


	void SpecificRender();


private:

	static TGfxTexture * s_pChurchTexture;
};

#endif
