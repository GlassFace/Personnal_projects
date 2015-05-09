
#ifndef METEORITE_H_INCLUDED
#define METEORITE_H_INCLUDED

class TAnim;

class TMeteorite
{
public:

	TMeteorite();
	TMeteorite(const TGfxVec2 & tPos);
	~TMeteorite();


	static void S_Initialize();

	void Update();

	bool IsDead();


	void Render() const;


private:

	static TGfxTexture * s_pMeteoriteTileset;
	static TGfxTexture * s_pWarningTileSet;
	static TGfxTexture * s_pDirtSprayTileSet;

	TAnim * m_pFall;
	TAnim * m_pWarning;
	TGfxSprite * m_pMeteoriteSprite;

	TAnim * m_pDirtSpray;
	TGfxSprite * m_pDirtSpraySprite;


	bool m_bWarning;

	TGfxVec2 m_tDestination;
	int m_iStartWarningTime;

	TGfxVec2 m_tPos;
	TGfxVec2 m_tSize;

	TGfxVec2 m_tVelocity;
	float m_fSpeed;
};

#endif
