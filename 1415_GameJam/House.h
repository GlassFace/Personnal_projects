
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

	TGfxSprite * GetSprite() const
	{
		return m_pSprite;
	}

	const TGfxVec2 & GetPosition() const
	{
		return m_tPos;
	}

	void SpecificUpdate();


private:

	static TGfxTexture * s_pTexture;

	int m_iLastSpawnTime;
};

#endif
