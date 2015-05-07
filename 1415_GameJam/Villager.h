#pragma once
#include "Dynamic.h"
class TVillager : public TDynamic
{
public:

	TVillager();
	TVillager(const TGfxVec2 & tPos);
	~TVillager();


	static void S_Initialize();


	bool IsMouseOver(const TGfxVec2 & tMousePos) const;

protected:

	static TGfxTexture * s_pTexture;
};

