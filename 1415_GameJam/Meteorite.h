
#ifndef METEORITE_H_INCLUDED
#define METEORITE_H_INCLUDED

class TMeteorite : public TDynamic
{
public:

	TMeteorite();
	TMeteorite(const TGfxVec2 & tPos);
	~TMeteorite();


	static void S_Initialize();

	void SpecificUpdate();

	void Die();


private:

	static TGfxTexture * s_pMeteoriteTileset;
	static TGfxTexture * s_pWarningTileSet;

	TAnim * m_pFall;
	TAnim * m_pWarning;
	TGfxSprite * m_pWarningSprite;

	TGfxVec2 m_tDestination;
	int m_iStartWarningTime;
};

#endif
