
#include "flib.h"
#include "flib_vec2.h"
#include "generics.h"
#include "Anim.h"



using namespace Generics;


TAnim::TAnim() :
m_pSprite(nullptr),
m_iSizeX(0),
m_iSizeY(0),
m_iFrames(0),
m_iCurrentFrame(0),
m_iLastFrameChange(0),
m_iFPS(0)
{

}

TAnim::TAnim(const TGfxTexture * pTileset, int iFPS, int iSizeX, int iSizeY) :
m_pSprite(nullptr),
m_iSizeX(iSizeX),
m_iSizeY(iSizeY),
m_iFrames(0),
m_iCurrentFrame(0),
m_iLastFrameChange(0),
m_iFPS(iFPS)
{
	m_pSprite = GfxSpriteCreate(pTileset);
	GfxSpriteSetPivot(m_pSprite, (iSizeX / 2.0f), float(iSizeY));

	m_iFrames = GfxSpriteGetSizeX(m_pSprite) / iSizeX;

	GfxSpriteSetCutout(m_pSprite, 0, 0, iSizeX, iSizeY);
}

TAnim::~TAnim()
{
	if (m_pSprite != nullptr)
	{
		GfxSpriteDestroy(m_pSprite);
		m_pSprite = nullptr;
	}
}


TGfxSprite * TAnim::Play(const EDirection eDirectionFacing)
{
	if (GfxTimeGetMilliseconds() - m_iLastFrameChange >= SECONDS / m_iFPS)
	{
		m_iCurrentFrame++;
		
		if (m_iCurrentFrame >= m_iFrames)
		{
			m_iCurrentFrame = 0;
		}

		GfxSpriteSetCutout(m_pSprite, m_iCurrentFrame * m_iSizeX, 0, m_iSizeX, m_iSizeY);

		m_iLastFrameChange = GfxTimeGetMilliseconds();
	}

	if (eDirectionFacing == EDirection_Right)
	{
		GfxSpriteSetScale(m_pSprite, 1.0f, 1.0f);
	}

	else
	{
		GfxSpriteSetScale(m_pSprite, -1.0f, 1.0f);
	}

	return m_pSprite;
}
