
#ifndef ENCLOSURE_H_INCLUDED
#define ENCLOSURE_H_INCLUDED

class TEnclosure : public TBuilding
{
public:

	TEnclosure();
	TEnclosure(const TGfxVec2 & tPos);
	~TEnclosure();


	static void S_Initialize();


	void SpecificUpdate();

	bool AssignVillager(TVillager * pVillager);
	void UnassignVillager(TVillager * pVillager);

	static float S_GetSizeX();


	void SpecificRender() {};


private:

	static TGfxTexture * s_pEnclosureTexture;

	int * m_pResidentsEnteringTime;
};

#endif
