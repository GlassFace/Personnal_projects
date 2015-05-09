
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

	void Die();


	void Render() const;


private:

	static TGfxTexture * s_pMeteoriteTileset;
	static TGfxTexture * s_pWarningTileSet;

	TAnim * m_pFall;
	TGfxSprite * m_pMeteoriteSprite;

	TAnim * m_pWarning;
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
