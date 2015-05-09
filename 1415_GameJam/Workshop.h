
#ifndef WORKSHOP_H_INCLUDED
#define WORKSHOP_H_INCLUDED

class TWorkshop : public TBuilding
{
public:

	TWorkshop();
	TWorkshop(const TGfxVec2 & tPos);
	~TWorkshop();


	static void S_Initialize();


	void SpecificUpdate();

	bool AssignVillager(TVillager * pVillager);
	void UnassignVillager(TVillager * pVillager);

	void GetInput();

	static float S_GetSizeX();

	TGfxSprite * GetIconSprite()
	{
		return m_pIconSprite;
	}


	void SpecificRender();


private:
	
	static TGfxTexture * s_pWorkshopTexture;

	TGfxSprite * m_pIconSprite;
	static TGfxTexture * s_pIconsTileSet;

	EBuildingType m_eBuildingToCreateType;
};

#endif
